#pragma once

#include <glm/glm.hpp>
#include "common/world/entity_id.h"
#include "common/proto/udpgame.pb.h"

struct PhysicsC {
  EntityId entityid;

  Texture texture;
  glm::vec3 position;
  glm::vec3 velocity;
  float horizontal_angle;
  float vertical_angle;
  bool on_ground;

  glm::vec3 next_position;
  glm::vec3 next_bb_min;
  glm::vec3 next_bb_max;

  glm::vec3 dimensions;
  glm::vec3 bb_min;
  glm::vec3 bb_max;

  void update_bbs();
  void update_next_bbs();

  glm::vec3 eye_position() const;
  glm::vec3 look_direction() const;

  EntityId eid() { return entityid; }
};
