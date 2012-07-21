#ifndef CLIENT_VIEW_SHADER_PROGRAM_H
#define CLIENT_VIEW_SHADER_PROGRAM_H

#include <GL/glew.h>
#include "common/google.h"

class ShaderProgram {
public:
  ShaderProgram();

  void Init(const char*, const char*);
  void Destroy();

  private:
  DISALLOW_COPY_AND_ASSIGN(ShaderProgram);

  GLuint vertex_array;
  GLuint vertex_buffer;
  GLuint vertex_shader;
  GLuint fragment_shader;
  GLuint shader_program;
};

#endif
