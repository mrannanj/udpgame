#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>

#include "client/view/window.h"
#include "client/controller/input/input.h"
#include "client/controller/perspective.h"

#include "common/world/components/input_system.h"
#include "common/world/components/physics_system.h"

Perspective::Perspective():
  m_freelook(true),
  m_follow_id(0),
  m_vertical_angle(0.0f),
  m_horizontal_angle(0.0f),
  m_position(10.0f, 2.0f, 10.0f),
  m_center(0.0f, 0.0f, 0.0f),
  m_up(0.0f, 1.0f, 0.0f)
{
}

void Perspective::jump_to_next_unit()
{
#if 0
  m_follow_id = g_physics_system.next_id(m_follow_id);
  std::cout << "Jumped to unit " << m_follow_id << std::endl;
#endif
}

void Perspective::switch_camera_mode()
{
  m_freelook = !m_freelook;
  std::cout << "Freelook: " << m_freelook << std::endl;
}

void Perspective::handle_input(Input& i)
{
  if (i.consume_discrete_action(DiscreteAction::SWITCH_CAMERA_MODE))
  {
    switch_camera_mode();
  }
  if (i.consume_discrete_action(DiscreteAction::SWITCH_UNIT))
  {
    jump_to_next_unit();
  }

  if (!m_freelook)
  {
    if (g_physics_system.get(m_follow_id))
    {
      g_input_system.add_input(m_follow_id, i);
    }
    return;
  }
  handle_freelook_input(i);
}

void Perspective::handle_freelook_input(const Input& input)
{
  float move_speed = 0.1f;
  m_vertical_angle -= (float)input.mouse_delta_y * 0.01f;
  m_horizontal_angle -= (float)input.mouse_delta_x * 0.01f;

  m_direction = glm::vec3(
    cos(m_vertical_angle) * sin(m_horizontal_angle),
    sin(m_vertical_angle),
    cos(m_vertical_angle) * cos(m_horizontal_angle)
  );

  glm::vec3 right = glm::vec3(
    sin(m_horizontal_angle - 3.14f/2.0f),
    0,
    cos(m_horizontal_angle - 3.14f/2.0f)
  );
  m_up = glm::cross(right, m_direction);

  if (input.continous_actions & ContinousAction::MOVE_FORWARD)
  {
    m_position += m_direction * move_speed;
  }
  else if (input.continous_actions & ContinousAction::MOVE_BACK)
  {
    m_position -= m_direction * move_speed;
  }
  if (input.continous_actions & ContinousAction::MOVE_RIGHT)
  {
    m_position += right * move_speed;
  }
  else if (input.continous_actions & ContinousAction::MOVE_LEFT)
  {
    m_position -= right * move_speed;
  }
  if (input.continous_actions & ContinousAction::JUMP)
  {
    m_position.y += move_speed;
  }
}

void Perspective::tick()
{
  m_projection = glm::perspective(45.0f, (float)WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 100.0f);
  if (!m_freelook)
  {
    PhysicsC* p = g_physics_system.get(m_follow_id);
    if (p)
    {
      m_position = p->position;
      m_position.y += 0.7f;
      m_vertical_angle = p->vertical_angle;
      m_horizontal_angle = p->horizontal_angle;
      m_direction = glm::vec3(
        cos(m_vertical_angle) * sin(m_horizontal_angle),
        sin(m_vertical_angle),
        cos(m_vertical_angle) * cos(m_horizontal_angle)
      );
      glm::vec3 right = glm::vec3(
        sin(m_horizontal_angle - 3.14f/2.0f),
        0,
        cos(m_horizontal_angle - 3.14f/2.0f)
      );
      m_up = glm::cross(right, m_direction);
    }
    else
    {
      switch_camera_mode();
    }
  }
  m_view = glm::lookAt(m_position, m_position+m_direction, m_up);
  m_view_projection = m_projection * m_view;
}

const glm::mat4& Perspective::get_view_projection_matrix() const
{
  return m_view_projection;
}

std::string Perspective::pos_string() const
{
  std::stringstream ss;
  ss << "(" << (int)m_position.x << ","
    << (int)m_position.y << "," << (int)m_position.z << ")";
  return ss.str();
}

