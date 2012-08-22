#ifndef COMMON_WORLD_COMPONENTS_GRID_H
#define COMMON_WORLD_COMPONENTS_GRID_H

#include <glm/glm.hpp>

#include "common/world/components/physics.h"

constexpr unsigned GRID_SIZE_X = 25;
constexpr unsigned GRID_SIZE_Y = 25;
constexpr unsigned GRID_SIZE_Z = 25;

constexpr float MAX_X = (float)(GRID_SIZE_X - 1);
constexpr float MAX_Y = (float)(GRID_SIZE_Y - 1);
constexpr float MAX_Z = (float)(GRID_SIZE_Z - 1);

constexpr float BLOCK_SIZE = 1.0f;

const glm::vec3 grid_top(MAX_X, MAX_Y, MAX_Z);
const glm::vec3 grid_bot(0.0f, 0.0f, 0.0f);

class Grid
{
public:
  Grid();

  void handle_grid_collisions(PhysicsC&, float) const;
  void check_collision(PhysicsC&, float) const;
  void correct_position(PhysicsC&, unsigned, unsigned, unsigned) const;
  void obey_lower_limits(PhysicsC&, const glm::vec3&) const;
  void obey_upper_limits(PhysicsC&, const glm::vec3&) const;
  void bb_min(unsigned, unsigned, unsigned, glm::vec3&) const;
  void bb_max(unsigned, unsigned, unsigned, glm::vec3&) const;
  void block_center(int, int, int, glm::vec3&) const;
  char block(unsigned, unsigned, unsigned) const;
  void mind_world_limits(PhysicsC&) const;
  void overlapping_indices(const PhysicsC&, unsigned[3][2]) const;

  char m_grid[GRID_SIZE_X][GRID_SIZE_Y][GRID_SIZE_Z];
};

extern Grid g_grid;

#endif
