#pragma once

#include <GL/glew.h>
#include <string>

class Shader {
public:
  Shader(const std::string&, const std::string&);
  ~Shader();

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
