#pragma once

#include <glm/glm.hpp>

#include "common/world/components/AABB.h"
#include "common/world/entity_id.h"
#include "common/proto/udpgame.pb.h"

struct PhysicsC {
  EntityId entityid;

  ObjectType type;
  glm::vec3 position;
  glm::vec3 velocity;
  float horizontal_angle;
  float vertical_angle;
  bool on_ground;

  glm::vec3 dimensions;
  AABB bb;

  glm::vec3 next_position;
  AABB next_bb;

  void update_bbs();
  void update_next_bbs();

  glm::vec3 eye_position() const;
  glm::vec3 look_direction() const;

  EntityId eid() { return entityid; }
};
