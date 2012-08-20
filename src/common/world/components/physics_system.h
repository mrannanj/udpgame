#ifndef COMMON_WORLD_COMPONENTS_PHYSICS_SYSTEM_H
#define COMMON_WORLD_COMPONENTS_PHYSICS_SYSTEM_H

#include <vector>
#include <glm/glm.hpp>
#include "common/world/entity_id.h"
#include "common/world/components/physics.h"

#define FRICTION 0.8f
#define GRAVITY 10.0f

class PhysicsSystem
{
public:
  PhysicsC* get(EntityId);
  void add(PhysicsC&);
  void tick(float);
  EntityId next_id(EntityId);
  const std::vector<PhysicsC>& physics_components() const;
private:
  std::vector<PhysicsC> m_physics_components;
};

extern PhysicsSystem g_physics_system;

#endif
