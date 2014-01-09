#pragma once

#include <glm/glm.hpp>

#include "common/proto/udpgame.pb.h"
#include "common/world/components/physics.h"
#include "common/world/components/grid_array.h"

constexpr float BLOCK_SIZE = 1.0f;
constexpr float BOTTOM = -20.0f;

struct GridHandler {
  GridHandler();
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
  void overlapping_indices(const PhysicsC&, int[3][2]) const;
  bool correct_one_hit(PhysicsC& p) const;

  void range_indices(const glm::vec3&, int[3][2]) const;
  bool raycast(const glm::vec3&, const glm::vec3&, float&, char**, char**);
  bool ray_block_collision(int, int, int,
      const glm::vec3&, const glm::vec3&, float&, int&, int&) const;

  bool belowBottom(const glm::vec3&) const;

  void serialize(InitialState&) const;
  void deserialize(const InitialState&);

  GridArray mArr;
};
