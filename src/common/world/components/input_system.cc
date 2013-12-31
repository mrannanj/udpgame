#include "common/world/components/input_system.h"
#include <iostream>

constexpr float HALF_PI = (float)M_PI/2.0f;
constexpr float PI = (float)M_PI;

void InputSystem::add_input(EntityId id, const Input& input) {
  InputC input_comp;
  input_comp.id = id;
  input_comp.actions = input.continous_actions;
  input_comp.vertical_angle_delta = (float)input.mouse_delta_y * 0.01f;
  input_comp.horizontal_angle_delta = (float)input.mouse_delta_x * 0.01f;
  m_inputs.push_back(input_comp);
}

void InputSystem::add_inputc(const InputC& ic) {
  m_inputs.push_back(ic);
}

void InputSystem::tick(float, World& w) {
  float move_speed = 1.5f;
  float jump_velocity = 5.0f;

  for (InputC& i : m_inputs)
  {
    if (i.actions & ContinousAction::SPAWN_UNIT) {
      w.spawn_entity(i.id);
    }
    auto it = w.mClient2Entity.find(i.id);
    if (it == w.mClient2Entity.end())
      continue;
    EntityId id = it->second;

    PhysicsC* p = g_physics_system.get(id);
    if (p == nullptr) continue;
    p->horizontal_angle -= i.horizontal_angle_delta;
    p->vertical_angle -= i.vertical_angle_delta;
    if (p->vertical_angle < -HALF_PI)
      p->vertical_angle = -HALF_PI;
    else if (p->vertical_angle > HALF_PI)
      p->vertical_angle = HALF_PI;

    glm::vec3 forward = glm::vec3(
      sin(p->horizontal_angle), 0.0f, cos(p->horizontal_angle));

    glm::vec3 right = glm::vec3(
      sin(p->horizontal_angle - HALF_PI),
      0.0f,
      cos(p->horizontal_angle - HALF_PI)
    );

    if (i.actions & ContinousAction::MOVE_FORWARD)
    {
      p->velocity += forward * move_speed;
    }
    else if (i.actions & ContinousAction::MOVE_BACK)
    {
      p->velocity -= forward * move_speed;
    }
    if (i.actions & ContinousAction::MOVE_RIGHT)
    {
      p->velocity += right * move_speed;
    }
    else if (i.actions & ContinousAction::MOVE_LEFT)
    {
      p->velocity -= right * move_speed;
    }
    if (i.actions & ContinousAction::JUMP && p->on_ground)
    {
      p->velocity.y += jump_velocity;
      p->on_ground = false;
    }
  }
  m_inputs.clear();
}

InputSystem g_input_system;

