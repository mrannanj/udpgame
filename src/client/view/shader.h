#ifndef CLIENT_VIEW_SHADER_H
#define CLIENT_VIEW_SHADER_H

#include <GL/glew.h>
#include "common/google.h"

class Shader {
public:
  Shader(const char*, const char*);
  ~Shader();
  DISALLOW_COPY_AND_ASSIGN(Shader);

  void On() const;

protected:
  GLuint vertex_array;
  GLuint vertex_buffer;
  GLuint vertex_shader;
  GLuint fragment_shader;
  GLuint shader_program;

private:
  void LoadShader(const char*, const char*);
  GLuint AddShaderSource(const char*, int);
  size_t MmapFile(const char*, int*, void**);
  void UnmmapFile(size_t, int, void*);
};

#endif
