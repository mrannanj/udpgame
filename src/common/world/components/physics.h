#ifndef COMMON_WORLD_COMPONENTS_PHYSICS_H
#define COMMON_WORLD_COMPONENTS_PHYSICS_H

#include <glm/glm.hpp>
#include "common/world/entity_id.h"

struct PhysicsC
{
  EntityId id;
  glm::vec3 position;
  glm::vec3 velocity;
  float horizontal_angle;
  float vertical_angle;
  bool on_ground;
};

#endif
