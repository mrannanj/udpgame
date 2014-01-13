#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "client/view/shader.h"

class CubeRenderer : public Shader {
public:
  CubeRenderer();

  void DrawCube(const glm::mat4&, const glm::mat4&, const glm::mat4&) const;
  void SetTexture(GLuint) const;
  GLint lightPositions() const;
  GLint activeLights() const;

private:
  void Init();

  GLint m_p_uniform;
  GLint m_v_uniform;
  GLint m_m_uniform;
  GLint m_texture_uniform;
  GLint m_light_positions;
  GLint m_active_lights;
};
