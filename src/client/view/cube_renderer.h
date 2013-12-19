#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "client/view/shader.h"

class CubeRenderer : public Shader {
public:
  CubeRenderer();

  void DrawCube(const glm::mat4&) const;
  void SetTexture(GLuint) const;

private:
  void Init();

  GLint m_mvp_uniform;
  GLint m_texture_uniform;
};
