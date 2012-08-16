#ifndef CLIENT_CONTROLLER_CAMERA_H
#define CLIENT_CONTROLLER_CAMERA_H

#include <glm/glm.hpp>

#include "common/google.h"

struct Input;

class Camera
{
public:
  Camera();
  DISALLOW_COPY_AND_ASSIGN(Camera);

  void handle_input(const Input&);
  void update();
  const glm::mat4& get_view_projection_matrix() const;

private:
  float m_vertical_angle;
  float m_horizontal_angle;
  glm::vec3 m_position;
  glm::vec3 m_direction;
  glm::vec3 m_center;
  glm::vec3 m_up;
  glm::mat4 m_view;
  glm::mat4 m_projection;
  glm::mat4 m_view_projection;
};

#endif
