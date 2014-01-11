#pragma once

#include <glm/glm.hpp>

#include "common/world/components/AABB.h"
#include "common/world/entity_id.h"
#include "common/proto/udpgame.pb.h"

struct PhysicsC {
  PhysicsC();
  PhysicsC(const PhysicsData&);
  operator PhysicsData() const;

  EntityId entityid;
  ObjectType type;
  glm::vec3 position;
  glm::vec3 velocity;
  glm::vec3 dimensions;
  float horizontal_angle;
  float vertical_angle;
  bool on_ground;

  // these are calculated, need not serialize
  AABB bb;
  AABB next_bb;
  glm::vec3 next_position;

  void update_bbs();
  void update_next_bbs();

  EntityId eid() const;
  glm::vec3 eye_position() const;
  glm::vec3 look_direction() const;
};
