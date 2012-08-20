#include <string.h>
#include "common/world/components/grid.h"
#include <iostream>

constexpr unsigned first = 0;
constexpr unsigned last = 1;

Grid::Grid()
{
  memset(m_grid, 0, GRID_SIZE_X * GRID_SIZE_Y * GRID_SIZE_Z);
  for (unsigned x = 0; x < GRID_SIZE_X; ++x)
    for (unsigned z = 0; z < GRID_SIZE_Z; ++z)
      m_grid[x][0][z] = 1;

  for (unsigned x = 0; x < GRID_SIZE_X; ++x)
    for (unsigned y = 0; y < x && y < GRID_SIZE_Y; ++y)
       m_grid[x][y][0] = 1;

  for (unsigned x = 0; x < GRID_SIZE_X; ++x)
    for (unsigned y = 0; y < x && y < GRID_SIZE_Y; ++y)
       m_grid[x][y][5] = 1;

  for (unsigned x = 0; x < GRID_SIZE_X; ++x)
    for (unsigned y = 0; y < 2 && x+y < GRID_SIZE_Y; ++y)
       m_grid[x][x+y][9] = 1;
 }

char Grid::block(unsigned x, unsigned y, unsigned z) const
{
  assert(x < GRID_SIZE_X && y < GRID_SIZE_Y && z < GRID_SIZE_Z);
  return m_grid[x][y][z];
}

void inline go_towards(unsigned to, unsigned& x)
{
  if (x != to)
    x < to ? ++x: --x;
}

void Grid::overlapping_indices(const PhysicsC& p, unsigned* ind) const
{
  unsigned* pi = ind;
  for (unsigned a = 0; a < 3; ++a)
  {
    pi = ind + a*2;
    if (p.velocity[a] < 0.0f) {
      pi[first] = (unsigned)(p.next_bb_min[a]);
      pi[last] = (unsigned)(p.bb_max[a]);
    } else {
      pi[first] = (unsigned)(p.bb_min[a]);
      pi[last] = (unsigned)(p.next_bb_max[a]);
    }
  }
}

void Grid::cubes_passed_through(PhysicsC& p, float dt) const
{
  p.next_position = p.position + p.velocity * dt;
  mind_world_limits(p);
  p.update_bbs();
  p.update_next_bbs();

  unsigned ind[6];
  overlapping_indices(p, ind);

  for (unsigned x = ind[first]; x <= ind[last]; ++x) {
    for (unsigned y = ind[2+first]; y <= ind[2+last]; ++y) {
      for (unsigned z = ind[4+first]; z <= ind[4+last]; ++z) {
        if (m_grid[x][y][z])
        {
          correct_position(p,x,y,z);
        }
      }
    }
  }
}

float inline min(float a, float b)
{
  return (a < b) ? a : b;
}

float inline max(float a, float b)
{
  return (a > b) ? a : b;
}

#if 0
//ugly
float Grid::time_to_hit(const PhysicsC& p, unsigned* c) const
{
  float t = -1.0f;
  for (unsigned a = 0; a < 3; ++a)
  {
    if ((unsigned)p.position[a] == c[a])
      return FLT_MAX;
    if ((unsigned)p.velocity[a] == 0.0f)
      return 0.0f;
    float v = p.velocity[a];
    float s = p.position[a];
    float point = (float)c[a];
    float t1 = (point-s)/v;
    float t2 = ((point-s) + BLOCK_SIZE)/v;
    if (t1 > 0.0f)
      t = min(t1, t);
    if (t2 > 0.0f)
      t = min(t2, t);
    assert(t1 > 0.0f && t2 > 0.0f);
  }
  assert(t > 0.0f);
  return t;
}
#endif

void Grid::correct_position(PhysicsC& p, unsigned x, unsigned y, unsigned z) const
{
  glm::vec3 block_min;
  glm::vec3 block_max;
  bb_min(x, y, z, block_min);
  bb_max(x, y, z, block_max);

  unsigned axis = 4;
  float smallest_overlap = FLT_MAX;
  float smallest_overlap_abs = FLT_MAX;
  for (unsigned a = 0; a < 3; ++a)
  {
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

  p.next_position[axis] += smallest_overlap;
  p.velocity[axis] = 0.0f;
  if (axis == 1) p.on_ground = true;
}

void Grid::bb_min(unsigned x, unsigned y, unsigned z, glm::vec3& bb) const
{
  bb = glm::vec3((float)x, (float)y, (float)z);
}

void Grid::bb_max(unsigned x, unsigned y, unsigned z, glm::vec3& bb) const
{
  bb = glm::vec3((float)x + BLOCK_SIZE, (float)y + BLOCK_SIZE,
    (float)z + BLOCK_SIZE);
}

void Grid::mind_world_limits(PhysicsC& p) const
{
  for (unsigned a = 0; a < 3; ++a)
  {
    if (p.next_bb_min[a] < grid_bot[a])
      p.next_position[a] = grid_bot[a] + p.dimensions[a];
    else if (p.next_bb_min[a] > grid_top[a])
      p.next_position[a] = grid_top[a] - p.dimensions[a];
  }
}

void Grid::check_collision(PhysicsC& p, float dt) const
{
  cubes_passed_through(p, dt);
  p.position = p.next_position;
  p.update_bbs();
  p.update_next_bbs();
}

Grid g_grid;

