#include "common/world/components/physics_handler.h"
#include "common/world/components/grid_handler.h"
#include "common/world/world.h"

#include <cassert>
#include <algorithm>

void PhysicsHandler::tick(float dt, World& w) {
  for (PhysicsC& p : mComponents) {
    p.velocity.y -= GRAVITY * dt;
    p.velocity.x *= FRICTION;
    p.velocity.z *= FRICTION;
    if (!w.grid().check_collision(p, dt))
      w.mDeleteList.insert(p.id);
  }
}

void PhysicsHandler::getObjects(WorldState& w) const {
  for (const PhysicsC& p : mComponents) {
    Object* o = w.add_object();
    o->set_id(p.id);
    o->set_x(p.position.x);
    o->set_y(p.position.y);
    o->set_z(p.position.z);
    o->set_vertical_angle(p.vertical_angle);
    o->set_horizontal_angle(p.horizontal_angle);
    o->set_dim_x(p.dimensions.x);
    o->set_dim_y(p.dimensions.y);
    o->set_dim_z(p.dimensions.z);
  }
}

void PhysicsHandler::setObjects(const WorldState& w) {
  mComponents.clear();
  for (int i = 0; i < w.object_size(); ++i) {
    const Object& o = w.object(i);
    PhysicsC p;
    p.id = o.id();
    p.position.x = o.x();
    p.position.y = o.y();
    p.position.z = o.z();
    p.vertical_angle = o.vertical_angle();
    p.horizontal_angle = o.horizontal_angle();
    p.dimensions.x = o.dim_x();
    p.dimensions.y = o.dim_y();
    p.dimensions.z = o.dim_z();
    p.update_bbs();
    add(p);
  }
}
