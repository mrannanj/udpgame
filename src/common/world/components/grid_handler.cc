#include "common/world/components/grid_handler.h"
#include <iostream>

using namespace std;
using namespace glm;

GridHandler::GridHandler()
{
}

void GridHandler::defaultGrid() {
  mGrid.makeFloor();
}

void GridHandler::overlapping_indices(const PhysicsC& p, int ind[3][2]) const {
  for (unsigned a = 0; a < 3; ++a) {
    if (p.velocity[a] < 0.0f) {
      ind[a][0] = (int)(p.next_bb_min[a]);
      ind[a][1] = (int)(p.bb_max[a]);
    } else {
      ind[a][0] = (int)(p.bb_min[a]);
      ind[a][1] = (int)(p.next_bb_max[a]);
    }
  }
}

bool GridHandler::correct_one_hit(PhysicsC& p) const {
  int ind[3][2];
  overlapping_indices(p, ind);
  for (int x = ind[0][0]; x <= ind[0][1]; ++x) {
    for (int y = ind[1][0]; y <= ind[1][1]; ++y) {
      for (int z = ind[2][0]; z <= ind[2][1]; ++z) {
        if (mGrid.get(x,y,z)) {
          correct_position(p, x, y, z);
          return true;
        }
      }
    }
  }
  return false;
}

bool GridHandler::handle_grid_collisions(PhysicsC& p, float dt) const {
  p.next_position = p.position + p.velocity * dt;
  p.update_bbs();
  p.update_next_bbs();

  for (int i = 0; correct_one_hit(p); ++i)
    if (i > 8) return false;
  return true;
}

void GridHandler::correct_position(PhysicsC& p, int x, int y, int z) const {
  glm::vec3 block_min;
  glm::vec3 block_max;
  bb_min(x, y, z, block_min);
  bb_max(x, y, z, block_max);

  unsigned axis = 4;
  float smallest_overlap = FLT_MAX;
  float smallest_overlap_abs = FLT_MAX;
  for (unsigned a = 0; a < 3; ++a) {
    float overlap = block_max[a] - p.next_bb_min[a];
    float overlap_abs = fabsf(overlap);
    if (overlap_abs > 0.0f && smallest_overlap_abs > overlap_abs) {
      smallest_overlap = overlap;
      smallest_overlap_abs = overlap_abs;
      axis = a;
    }

    overlap = block_min[a] - p.next_bb_max[a];
    overlap_abs = fabsf(overlap);
    if (overlap_abs > 0.0f && smallest_overlap_abs > overlap_abs) {
      smallest_overlap = overlap;
      smallest_overlap_abs = overlap_abs;
      axis = a;
    }
  }
  assert(axis != 4);

  p.next_position[axis] += smallest_overlap * 1.1f;
  p.velocity[axis] = 0.0f;
  if (axis == 1) p.on_ground = true;

  p.position = p.next_position;
  p.update_bbs();
  p.update_next_bbs();
}

void GridHandler::bb_min(int x, int y, int z, glm::vec3& bb) const {
  bb = glm::vec3((float)x, (float)y, (float)z);
}

void GridHandler::bb_max(int x, int y, int z, glm::vec3& bb) const {
  bb = glm::vec3((float)x + BLOCK_SIZE, (float)y + BLOCK_SIZE,
    (float)z + BLOCK_SIZE);
}

void GridHandler::mind_world_limits(PhysicsC& p) const {
  for (unsigned a = 0; a < 3; ++a) {
    if (p.next_bb_min[a] < grid_bot[a])
      p.next_position[a] = grid_bot[a] + p.dimensions[a];
    else if (p.next_bb_max[a] > grid_top[a])
      p.next_position[a] = grid_top[a] - p.dimensions[a];
  }
  p.update_bbs();
  p.update_next_bbs();
}

bool GridHandler::check_collision(PhysicsC& p, float dt) const {
  bool ret = handle_grid_collisions(p, dt);
  p.position = p.next_position;
  p.update_bbs();
  p.update_next_bbs();
  return ret;
}

bool GridHandler::ray_block_collision(
    int x, int y, int z,
    const vec3& p, const vec3& d, float& t, int& axis, int& dir) const
{
  glm::vec3 block_min;
  glm::vec3 block_max;
  bb_min(x, y, z, block_min);
  bb_max(x, y, z, block_max);
  float tmin = 0.0f;
  float tmax = 5.0f;
  axis = 4;
  for (int i = 0; i < 3; i++) {
    int swapped = 1;
    if (fabs(d[i]) < EPSILON) {
      if (p[i] < block_min[i] || p[i] > block_max[i]) {
        return false;
      }
    } else {
      float d1 = (block_min[i] - p[i]);
      float d2 = (block_max[i] - p[i]);
      float t1 = d1/d[i];
      float t2 = d2/d[i];

      if (t1 < 0.0f or t2 < 0.0f) {
        return false;
      }
      if (t1 > t2) {
        swapped = -1;
        swap(t1, t2);
      }
      if (t1 > tmin) {
        tmin = t1;
        axis = i;
        dir = -1 * swapped;
      }
      if (t2 > tmax) {
        tmax = t2;
      }
      if (tmin > tmax) {
        return false;
      }
    }
  }
  if (tmin > 5.0f) return false;
  t = tmin;
  return true;
}

void GridHandler::raycast(const vec3& s, const vec3& d, bool take) {
  glm::vec3 dn = normalize(d);
  int b[3];
  float tmin = FLT_MAX;
  int baxis = 4;
  int dir = 0;
  bool hit = false;
  for (int x = 0; x < GRID_SIZE_X; ++x) {
    for (int y = 0; y < GRID_SIZE_Y; ++y) {
      for (int z = 0; z < GRID_SIZE_Z; ++z) {
        float t;
        int a;
        int d;
        if (mGrid.get(x,y,z) and
            ray_block_collision(x, y, z, s, dn, t, a, d)) {
          if (tmin > t) {
            b[0] = x;
            b[1] = y;
            b[2] = z;
            tmin = t;
            hit = true;
            baxis = a;
            dir = d;
          }
        }
      }
    }
  }
  if (hit) {
    if (take) {
      mGrid.set(b[0], b[1], b[2], 0);
    } else {
      b[baxis] += dir;
      mGrid.set(b[0], b[1], b[2], 1);
    }
  }
}

GridHandler g_grid;

