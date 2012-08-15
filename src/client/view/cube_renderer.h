#ifndef CLIENT_VIEW_CUBE_RENDERER_H
#define CLIENT_VIEW_CUBE_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "common/google.h"
#include "client/view/shader.h"

class CubeRenderer : public Shader {
public:
  CubeRenderer();
  DISALLOW_COPY_AND_ASSIGN(CubeRenderer);

  void DrawCube(const glm::mat4&) const;
  void SetTexture(GLuint) const;

private:
  void Init();

  GLint m_mvp_uniform;
  GLint m_texture_uniform;
};

#endif
