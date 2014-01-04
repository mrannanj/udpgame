#include "common/world/components/physics_handler.h"
#include "common/world/components/grid_handler.h"

#include <cassert>
#include <algorithm>

PhysicsC* PhysicsHandler::get(EntityId id) {
  for (PhysicsC& p : m_physics_components)
    if (p.id == id)
      return &p;
  return NULL;
}

void PhysicsHandler::clear() {
  m_physics_components.clear();
}

EntityId PhysicsHandler::next_id(EntityId id) {
  size_t n = m_physics_components.size();
  unsigned i = 0;
  for (; i < n; ++i) {
    if (m_physics_components[i].id == id)
      break;
  }
  if (i+1 < n)
    return m_physics_components[i+1].id;
  else
    return m_physics_components[0].id;
}

void PhysicsHandler::add(PhysicsC& p) {
  m_physics_components.push_back(p);
}

void PhysicsHandler::remove(EntityId eid) {
  m_physics_components.erase(std::remove_if(std::begin(m_physics_components),
        std::end(m_physics_components),
        [&](PhysicsC& p) { return p.id == eid; }),
      std::end(m_physics_components));
}

void PhysicsHandler::tick(float dt) {
  mRemoveList.clear();
  for (PhysicsC& p : m_physics_components) {
    p.velocity.y -= GRAVITY * dt;
    p.velocity.x *= FRICTION;
    p.velocity.z *= FRICTION;
    if (!g_grid.check_collision(p, dt))
      mRemoveList.insert(p.id);
  }
}

const std::vector<PhysicsC>& PhysicsHandler::physics_components() const {
  return m_physics_components;
}

PhysicsHandler g_physics_system;
