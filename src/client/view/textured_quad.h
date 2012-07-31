#ifndef CLIENT_VIEW_TEXTURED_QUAD_H
#define CLIENT_VIEW_TEXTURED_QUAD_H

#include <GL/glew.h>
#include "common/google.h"
#include "client/view/shader_program.h"

class TexturedQuad {
public:
  TexturedQuad();

  void Init(GLuint);
  void Destroy();
  void Draw();

  private:
  DISALLOW_COPY_AND_ASSIGN(TexturedQuad);

  ShaderProgram sp_;
};

#endif
