#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "client/view/window.h"
#include "client/controller/input/input.h"
#include "client/controller/camera.h"


Camera::Camera():
  m_position(4.0f, 3.0f, 3.0f),
  m_center(0.0f, 0.0f, 0.0f),
  m_up(0.0f, 1.0f, 0.0f)
{
}

void Camera::handle_input(const Input& input)
{
  if (input.actions_ & Action::MOVE_FORWARD)
  {
    m_position.x += 0.1f;
  }
  else if (input.actions_ & Action::MOVE_BACK)
  {
    m_position.x -= 0.1f;
  }

  if (input.actions_ & Action::MOVE_RIGHT)
  {
    m_position.z -= 0.1f;
  }
  else if (input.actions_ & Action::MOVE_LEFT)
  {
    m_position.z += 0.1f;
  }
}

void Camera::update()
{
  m_projection = glm::perspective(45.0f, (float)WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 100.0f);
  m_view = glm::lookAt(m_position, m_center, m_up);
  m_view_projection = m_projection * m_view;
}

const glm::mat4& Camera::get_view_projection_matrix() const
{
  return m_view_projection;
}
