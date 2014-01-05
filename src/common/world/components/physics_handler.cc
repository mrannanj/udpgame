#include "common/world/components/physics_handler.h"
#include "common/world/components/grid_handler.h"
#include "common/world/world.h"

#include <cassert>
#include <algorithm>

void* PhysicsHandler::get(EntityId id) {
  for (PhysicsC& p : m_physics_components)
    if (p.id == id)
      return &p;
  return NULL;
}

void PhysicsHandler::add(void* p) {
  m_physics_components.push_back(*(PhysicsC*)p);
}

void PhysicsHandler::remove(EntityId eid) {
  m_physics_components.erase(std::remove_if(std::begin(m_physics_components),
        std::end(m_physics_components),
        [&](PhysicsC& p) { return p.id == eid; }),
      std::end(m_physics_components));
}

void PhysicsHandler::tick(float dt, World& w) {
  mRemoveList.clear();
  for (PhysicsC& p : m_physics_components) {
    p.velocity.y -= GRAVITY * dt;
    p.velocity.x *= FRICTION;
    p.velocity.z *= FRICTION;
    if (!w.grid().check_collision(p, dt))
      mRemoveList.insert(p.id);
  }
}

const std::vector<PhysicsC>& PhysicsHandler::physics_components() const {
  return m_physics_components;
}

void PhysicsHandler::getObjects(WorldState& w) const {
  for (const PhysicsC& p : m_physics_components) {
    Object* o = w.add_object();
    o->set_id(p.id);
    o->set_x(p.position.x);
    o->set_y(p.position.y);
    o->set_z(p.position.z);
    o->set_vertical_angle(p.vertical_angle);
    o->set_horizontal_angle(p.horizontal_angle);
  }
}

void PhysicsHandler::setObjects(const WorldState& w) {
  m_physics_components.clear();
  for (int i = 0; i < w.object_size(); ++i) {
    const Object& o = w.object(i);
    PhysicsC p;
    p.id = o.id();
    p.position.x = o.x();
    p.position.y = o.y();
    p.position.z = o.z();
    p.vertical_angle = o.vertical_angle();
    p.horizontal_angle = o.horizontal_angle();
    p.dimensions = glm::vec3(0.4f, 0.9f, 0.4f);
    p.update_bbs();
    m_physics_components.push_back(p);
  }
}

PhysicsHandler g_physics_system;
