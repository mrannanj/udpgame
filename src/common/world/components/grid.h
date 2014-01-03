#pragma once

#include <glm/glm.hpp>

#include "common/world/components/physics.h"
#include "common/world/components/grid_array.h"

constexpr float MAX_X = (float)(GRID_SIZE_X - 1);
constexpr float MAX_Y = (float)(GRID_SIZE_Y - 1);
constexpr float MAX_Z = (float)(GRID_SIZE_Z - 1);

constexpr float BLOCK_SIZE = 1.0f;

const glm::vec3 grid_top(MAX_X, MAX_Y, MAX_Z);
const glm::vec3 grid_bot(0.0f, 0.0f, 0.0f);

struct Grid {
  Grid();
  void defaultGrid();

  bool handle_grid_collisions(PhysicsC&, float) const;
  bool check_collision(PhysicsC&, float) const;
  void correct_position(PhysicsC&, int, int, int) const;
  void obey_lower_limits(PhysicsC&, const glm::vec3&) const;
  void obey_upper_limits(PhysicsC&, const glm::vec3&) const;
  void bb_min(int, int, int, glm::vec3&) const;
  void bb_max(int, int, int, glm::vec3&) const;
  void block_center(int, int, int, glm::vec3&) const;
  char block(int, int, int) const;
  void mind_world_limits(PhysicsC&) const;
  void overlapping_indices(const PhysicsC&, int[3][2]) const;
  bool correct_one_hit(PhysicsC& p) const;

  void raycast(const glm::vec3&, const glm::vec3&, bool);
  bool ray_block_collision(int, int, int,
      const glm::vec3&, const glm::vec3&, float&, int&, int&) const;

  GridArray mGrid;
};

extern Grid g_grid;

