#pragma once

#include <string>
#include "common/include/glm.h"

#include "common/world/entity_id.h"
#include "common/proto/udpgame.pb.h"

struct Input;
class World;

class Perspective {
public:
  Perspective();

  void handle_input(Input&);
  void tick(World&);
  const glm::mat4& get_view_projection_matrix() const;
  const glm::mat4& view() const;
  const glm::mat4& projection() const;
  std::string pos_string() const;
  void handle_freelook_input(const Input&);

  ClientMode mClientMode;
  EntityId m_follow_id;

  float m_vertical_angle;
  float m_horizontal_angle;
  glm::vec3 m_position;
  glm::vec3 m_direction;
  glm::vec3 m_up;
  glm::mat4 m_view;
  glm::mat4 m_projection;
  glm::mat4 m_view_projection;
};
