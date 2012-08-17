#ifndef CLIENT_CONTROLLER_PERSPECTIVE_H
#define CLIENT_CONTROLLER_PERSPECTIVE_H

#include <string>
#include <glm/glm.hpp>

#include "common/world/entity_id.h"
#include "common/google.h"

struct Input;

class Perspective
{
public:
  Perspective();
  DISALLOW_COPY_AND_ASSIGN(Perspective);

  void handle_input(const Input&);
  void tick();
  const glm::mat4& get_view_projection_matrix() const;
  std::string pos_string() const;
  void jump_to_next_unit();
  void handle_freelook_input(const Input&);
  void switch_camera_mode();

  bool m_freelook;
  EntityId m_follow_id;

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
