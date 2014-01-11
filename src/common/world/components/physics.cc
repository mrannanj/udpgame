#include "common/world/components/physics.h"

void PhysicsC::update_bbs() {
  bb.max = position + dimensions;
  bb.min = position - dimensions;
}

void PhysicsC::update_next_bbs() {
  next_bb.max = next_position + dimensions;
  next_bb.min = next_position - dimensions;
}

EntityId PhysicsC::eid() const {
  return entityid;
}

glm::vec3 PhysicsC::eye_position() const {
  glm::vec3 eye_pos(position);
  eye_pos.y += 0.7f;
  return eye_pos;
}

glm::vec3 PhysicsC::look_direction() const {
  return glm::vec3(
          cos(vertical_angle) * sin(horizontal_angle),
          sin(vertical_angle),
          cos(vertical_angle) * cos(horizontal_angle));
}

PhysicsC::PhysicsC()
{
}

PhysicsC::PhysicsC(const PhysicsData& pd):
  entityid(pd.eid()),
  type(pd.type()),
  position(pd.pos().x(), pd.pos().y(), pd.pos().z()),
  velocity(pd.vel().x(), pd.vel().y(), pd.vel().z()),
  dimensions(pd.dim().x(), pd.dim().y(), pd.dim().z()),
  horizontal_angle(pd.horizontal_angle()),
  vertical_angle(pd.vertical_angle()),
  on_ground(pd.on_ground())
{
}

PhysicsC::operator PhysicsData() const {
  PhysicsData pd;
  pd.set_eid(entityid);
  pd.set_type(type);
  pd.mutable_pos()->set_x(position.x);
  pd.mutable_pos()->set_y(position.y);
  pd.mutable_pos()->set_z(position.z);
  pd.mutable_vel()->set_x(velocity.x);
  pd.mutable_vel()->set_y(velocity.y);
  pd.mutable_vel()->set_z(velocity.z);
  pd.mutable_dim()->set_x(dimensions.x);
  pd.mutable_dim()->set_y(dimensions.y);
  pd.mutable_dim()->set_z(dimensions.z);
  pd.set_horizontal_angle(horizontal_angle);
  pd.set_vertical_angle(vertical_angle);
  pd.set_on_ground(on_ground);
  return pd;
}
