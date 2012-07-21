#ifndef CLIENT_VIEW_TRIANGLE_DRAWER_H
#define CLIENT_VIEW_TRIANGLE_DRAWER_H

#include <GL/glew.h>
#include "common/google.h"
#include "client/view/shader_program.h"

class TriangleDrawer {
public:
  TriangleDrawer();
  DISALLOW_COPY_AND_ASSIGN(TriangleDrawer);

  void Init();
  void Destroy();
  void DrawTriangles(float*, size_t);
  void SetColor(float, float, float);

private:
  ShaderProgram sp_;
  GLint color_uniform_;
};

#endif
