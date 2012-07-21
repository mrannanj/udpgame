#ifndef CLIENT_VIEW_QUAD_DRAWER_H
#define CLIENT_VIEW_QUAD_DRAWER_H

#include <GL/glew.h>
#include "common/google.h"
#include "client/view/shader_program.h"

class QuadDrawer {
public:
  QuadDrawer();

  void Init();
  void Destroy();
  void DrawQuads(float*, size_t);

  private:
  DISALLOW_COPY_AND_ASSIGN(QuadDrawer);

  ShaderProgram sp;
};

#endif
