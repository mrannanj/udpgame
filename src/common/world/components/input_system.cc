#include "common/world/components/input_system.h"

void InputSystem::add_input(EntityId id, const Input& input)
{
  InputC input_comp;
  input_comp.id = id;
  input_comp.actions = input.actions_;
  input_comp.vertical_angle_delta = (float)input.mouse_delta_y * 0.01f;
  input_comp.horizontal_angle_delta = (float)input.mouse_delta_x * 0.01f;
  m_inputs.push_back(input_comp);
}

void InputSystem::tick(float)
{
  float move_speed = 1.5f;

  for (InputC& i : m_inputs)
  {
    PhysicsC* p = g_physics_system.get(i.id);
    p->horizontal_angle -= i.horizontal_angle_delta;
    p->vertical_angle -= i.vertical_angle_delta;

    glm::vec3 direction = glm::vec3(
      cos(p->vertical_angle) * sin(p->horizontal_angle),
      sin(p->vertical_angle),
      cos(p->vertical_angle) * cos(p->horizontal_angle)
    );

    glm::vec3 right = glm::vec3(
      sin(p->horizontal_angle - 3.14f/2.0f),
      0,
      cos(p->horizontal_angle - 3.14f/2.0f)
    );

    if (i.actions & Action::MOVE_FORWARD)
    {
      p->velocity += direction * move_speed;
    }
    else if (i.actions & Action::MOVE_BACK)
    {
      p->velocity -= direction * move_speed;
    }
    if (i.actions & Action::MOVE_RIGHT)
    {
      p->velocity += right * move_speed;
    }
    else if (i.actions & Action::MOVE_LEFT)
    {
      p->velocity -= right * move_speed;
    }
    if (i.actions & Action::JUMP && p->on_ground)
    {
      p->velocity.y += 10.0f;
      p->on_ground = false;
    }
  }
  m_inputs.clear();
}

InputSystem g_input_system;

