#include "common/world/components/grid_handler.h"
#include "common/world/components/AABB.h"
#include "common/world/components/collision.h"

#include <iostream>
#include <cassert>

using namespace std;
using glm::vec3;

static constexpr size_t DRAW_RANGE = 12;
static constexpr float RAYCAST_RANGE = 6.0f;
static constexpr float BOTTOM = -20.0f;

void GridHandler::defaultGrid() {
  mArr.makeFloor();
}

vec3 GridHandler::spawn_pos() const {
  return vec3(10.0f, mArr.heightFunction(10,10) + 3.0f, 10.0f);
}

void GridHandler::range_indices(const vec3& p, int ind[3][2]) const {
  for (unsigned a = 0; a < 3; ++a) {
    ind[a][0] = max(0, (int)(p[a] - DRAW_RANGE));
    ind[a][1] = min(GRID_SIZE[a] - 1, (int)(p[a] + DRAW_RANGE));
  }
}

void GridHandler::overlapping_indices(const Physics& p, int ind[3][2]) const {
  for (unsigned a = 0; a < 3; ++a) {
    ind[a][0] = (int)(p.bb.min[a]);
    ind[a][1] = (int)(p.bb.max[a]);
  }
}

void GridHandler::raycast_range(const vec3& p, const vec3& d, int ind[3][2])
  const
{
  const glm::vec3 k = p + d * RAYCAST_RANGE;

  for (unsigned a = 0; a < 3; ++a) {
    ind[a][0] = max(0.0f, min(p[a], k[a]));
    ind[a][1] = min((float)GRID_SIZE[a]-1, max(p[a], k[a]));
  }
}

bool GridHandler::correct_one_hit(Physics& p) const {
  int ind[3][2];
  overlapping_indices(p, ind);

  float max_overlap = FLT_MIN;
  unsigned max_axis = 4;
  bool hit = false;

  for (int y = ind[1][0]; y <= ind[1][1]; ++y) {
    for (int x = ind[0][0]; x <= ind[0][1]; ++x) {
      for (int z = ind[2][0]; z <= ind[2][1]; ++z) {
        if (mArr.get(x,y,z)) {
          AABB block(x,y,z);
          unsigned axis;
          float overlap = AABBvsAABB_overlap(block, p.bb, axis);
          if (fabsf(overlap) > fabsf(max_overlap)) {
            max_overlap = overlap;
            max_axis = axis;
            hit = true;
          }
        }
      }
    }
  }
  if (hit) {
    p.position[max_axis] += max_overlap * 1.1f;
    p.velocity[max_axis] = 0.0f;
    if (max_axis == 1) p.on_ground = true;
    p.update_bb();
  }
  return hit;
}

bool GridHandler::handle_grid_collisions(Physics& p) const {
  for (int i = 0; correct_one_hit(p); ++i)
    if (i >= 8) return false;
  return true;
}

bool GridHandler::check_collision(Physics& p, float dt) const {
  p.position = p.position + p.velocity * dt;
  p.update_bb();
  bool ret = handle_grid_collisions(p);
  if (belowBottom(p.position)) return false;
  return ret;
}

bool GridHandler::raycast(const vec3& s, const vec3& d, float& distance,
    char** hitBlock, char** faceBlock, int b[3], int f[3])
{
  distance = FLT_MAX;
  int baxis = 4;
  int dir = 0;
  bool hit = false;

  int ind[3][2];
  raycast_range(s, d, ind);

  for (int x = ind[0][0]; x <= ind[0][1]; ++x) {
    for (int y = ind[1][0]; y <= ind[1][1]; ++y) {
      for (int z = ind[2][0]; z <= ind[2][1]; ++z) {
        AABB box(x, y, z);
        float t;
        int tmp_axis, tmp_dir;
        char& block = mArr.getRef(x,y,z);
        if (block and AABBvsRay(box, s, d, t, tmp_axis, tmp_dir)) {
          if (distance > t) {
            distance = t;
            hit = true;
            baxis = tmp_axis;
            dir = tmp_dir;
            *hitBlock = &block;
            b[0] = f[0] = x;
            b[1] = f[1] = y;
            b[2] = f[2] = z;
            f[baxis] += dir;
            if (!mArr.outsideGrid(f[0], f[1], f[2])) {
              *faceBlock = &mArr.getRef(f[0], f[1], f[2]);
            } else {
              *faceBlock = nullptr;
            }
          }
        }
      }
    }
  }
  return hit;
}

void GridHandler::deserialize(const InitialState& i) {
  memcpy(mArr.mData, i.grid().c_str(), mArr.size());
}

void GridHandler::serialize(InitialState& i) const {
  i.set_grid(mArr.mData, mArr.size());
}

bool GridHandler::belowBottom(const glm::vec3& p) const {
  return p.y < BOTTOM;
}
