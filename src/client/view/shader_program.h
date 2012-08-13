#ifndef CLIENT_VIEW_SHADER_PROGRAM_H
#define CLIENT_VIEW_SHADER_PROGRAM_H

#include <GL/glew.h>
#include "common/google.h"

class ShaderProgram {
public:
  ShaderProgram(const char*, const char*);
  DISALLOW_COPY_AND_ASSIGN(ShaderProgram);

  void Destroy();

  GLuint vertex_array;
  GLuint vertex_buffer;
  GLuint vertex_shader;
  GLuint fragment_shader;
  GLuint shader_program;
};

#endif
