#pragma once

#include "common/platform.h"
#include "client/view/shader.h"

#include "common/include/glm.h"

class CubeRenderer : public Shader {
public:
  CubeRenderer(const ResourceLocator&);

  void DrawCube(const glm::mat4&, const glm::mat4&, const glm::mat4&) const;
  void SetTexture(GLuint) const;
  GLint lightPositions() const;
  GLint activeLights() const;
  void On() const;

private:
  GLint m_p_uniform;
  GLint m_v_uniform;
  GLint m_m_uniform;
  GLint m_texture_uniform;
  GLint m_light_positions;
  GLint m_active_lights;
};
