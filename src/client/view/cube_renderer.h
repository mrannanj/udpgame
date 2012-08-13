#ifndef CLIENT_VIEW_CUBE_RENDERER_H
#define CLIENT_VIEW_CUBE_RENDERER_H

#include "client/view/shader_program.h"

class CubeRenderer {
public:
  CubeRenderer();
private:
  ShaderProgram sp_;
};

#endif
