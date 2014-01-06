#include "common/world/components/physics_handler.h"
#include "common/world/components/grid_handler.h"
#include "common/world/world.h"

#include <cassert>
#include <algorithm>

constexpr float HALF_PI = (float)M_PI/2.0f;
constexpr float PI = (float)M_PI;
constexpr float move_speed = 1.5f;
constexpr float jump_velocity = 5.0f;

void PhysicsHandler::tick(float dt, World& w) {
  for (PhysicsC& p : mComponents) {
    InputC* i = w.input().get(p.id);
    if (i != nullptr) {
      p.horizontal_angle -= i->horizontal_angle_delta;
      p.vertical_angle -= i->vertical_angle_delta;
      if (p.vertical_angle < -HALF_PI)
        p.vertical_angle = -HALF_PI;
      else if (p.vertical_angle > HALF_PI)
        p.vertical_angle = HALF_PI;

      glm::vec3 forward = glm::vec3(
        sin(p.horizontal_angle), 0.0f, cos(p.horizontal_angle));

      glm::vec3 right = glm::vec3(
        sin(p.horizontal_angle - HALF_PI),
        0.0f,
        cos(p.horizontal_angle - HALF_PI)
      );

      if (i->actions & ContinousAction::MOVE_FORWARD)
        p.velocity += forward * move_speed;
      else if (i->actions & ContinousAction::MOVE_BACK)
        p.velocity -= forward * move_speed;

      if (i->actions & ContinousAction::MOVE_RIGHT)
        p.velocity += right * move_speed;
      else if (i->actions & ContinousAction::MOVE_LEFT)
        p.velocity -= right * move_speed;

      if (i->actions & ContinousAction::JUMP && p.on_ground) {
        p.velocity.y += jump_velocity;
        p.on_ground = false;
      }
    }

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
