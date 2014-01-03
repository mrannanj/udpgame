#include <string.h>
#include "common/world/components/grid.h"
#include <iostream>

using namespace std;

Grid::Grid()
{
}

void Grid::defaultGrid() {
  mGrid.makeFloor();
}

void Grid::overlapping_indices(const PhysicsC& p, int ind[3][2]) const {
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

bool Grid::correct_one_hit(PhysicsC& p) const {
  int ind[3][2];
  overlapping_indices(p, ind);
  for (int x = ind[0][0]; x <= ind[0][1]; ++x) {
    for (int y = ind[1][0]; y <= ind[1][1]; ++y) {
      for (int z = ind[2][0]; z <= ind[2][1]; ++z) {
        if (mGrid.get(x,y,z)) {
          correct_position(p,x,y,z);
          return true;
        }
      }
    }
  }
  return false;
}

bool Grid::handle_grid_collisions(PhysicsC& p, float dt) const {
  p.next_position = p.position + p.velocity * dt;
  p.update_bbs();
  p.update_next_bbs();

  for (int i = 0; correct_one_hit(p); ++i)
    if (i > 8) return false;
  return true;
}

void Grid::correct_position(PhysicsC& p, int x, int y, int z) const {
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

void Grid::bb_min(int x, int y, int z, glm::vec3& bb) const {
  bb = glm::vec3((float)x, (float)y, (float)z);
}

void Grid::bb_max(int x, int y, int z, glm::vec3& bb) const {
  bb = glm::vec3((float)x + BLOCK_SIZE, (float)y + BLOCK_SIZE,
    (float)z + BLOCK_SIZE);
}

void Grid::mind_world_limits(PhysicsC& p) const {
  for (unsigned a = 0; a < 3; ++a) {
    if (p.next_bb_min[a] < grid_bot[a])
      p.next_position[a] = grid_bot[a] + p.dimensions[a];
    else if (p.next_bb_max[a] > grid_top[a])
      p.next_position[a] = grid_top[a] - p.dimensions[a];
  }
  p.update_bbs();
  p.update_next_bbs();
}

bool Grid::check_collision(PhysicsC& p, float dt) const {
  bool ret = handle_grid_collisions(p, dt);
  p.position = p.next_position;
  p.update_bbs();
  p.update_next_bbs();
  return ret;
}

Grid g_grid;

