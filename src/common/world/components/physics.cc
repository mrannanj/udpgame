#include "common/world/components/physics.h"

void PhysicsC::update_bbs() {
  bb.max = position + dimensions;
  bb.min = position - dimensions;
}

void PhysicsC::update_next_bbs() {
  next_bb.max = next_position + dimensions;
  next_bb.min = next_position - dimensions;
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
