#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>

#include "client/view/window.h"
#include "client/controller/input/input.h"
#include "client/controller/camera.h"


Camera::Camera():
  m_vertical_angle(0.0f),
  m_horizontal_angle(-3.14f/2.0f),
  m_position(5.0f, 0.0f, 0.0f),
  m_center(0.0f, 0.0f, 0.0f),
  m_up(0.0f, 1.0f, 0.0f)
{
}

void Camera::handle_input(const Input& input)
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

  if (input.actions_ & Action::MOVE_FORWARD)
  {
    m_position += m_direction * move_speed;
  }
  else if (input.actions_ & Action::MOVE_BACK)
  {
    m_position -= m_direction * move_speed;
  }

  if (input.actions_ & Action::MOVE_RIGHT)
  {
    m_position += right * move_speed;
  }
  else if (input.actions_ & Action::MOVE_LEFT)
  {
    m_position -= right * move_speed;
  }

  if (input.actions_ & Action::JUMP)
  {
    m_position.y += move_speed;
  }
  else if (input.actions_ & Action::CROUCH)
  {
    m_position.y -= move_speed;
  }

  std::cout << pos_and_angle() << std::endl;
}

void Camera::update()
{
  m_projection = glm::perspective(45.0f, (float)WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 100.0f);
  m_view = glm::lookAt(m_position, m_position+m_direction, m_up);
  m_view_projection = m_projection * m_view;
}

const glm::mat4& Camera::get_view_projection_matrix() const
{
  return m_view_projection;
}

std::string Camera::pos_and_angle() const
{
  std::stringstream ss;
  ss.precision(2);
  ss << "(" << m_position.x <<
    "," << m_position.y <<
    "," << m_position.z <<
    "|" << m_horizontal_angle <<
    "," << m_vertical_angle << ")";
  return ss.str();
}
