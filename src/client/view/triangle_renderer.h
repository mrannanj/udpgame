#ifndef CLIENT_VIEW_TRIANGLE_RENDERER_H
#define CLIENT_VIEW_TRIANGLE_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "common/google.h"
#include "client/view/shader_program.h"


class TriangleRenderer {
public:
  TriangleRenderer();
  DISALLOW_COPY_AND_ASSIGN(TriangleRenderer);

  void Init();
  void DrawTriangles(float*, size_t, const glm::mat4&) const;
  void SetColor(float, float, float) const;
  void On() const;
  void Off() const;

private:
  ShaderProgram sp_;
  GLint color_uniform_;
  GLint mvp_uniform_;
};

#endif
