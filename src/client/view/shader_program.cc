#include "client/view/shader_program.h"
#include "client/view/shader_loader.h"

ShaderProgram::ShaderProgram() {}

void ShaderProgram::Init(
  const char* vertex_file, const char* fragment_file)
{
  glGenVertexArrays(1, &vertex_array);
  glBindVertexArray(vertex_array);

  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

  shader_program = LoadShaders(vertex_file, fragment_file,
    &vertex_shader, &fragment_shader);

  GLint pos_attrib = glGetAttribLocation(shader_program, "position");
  glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(pos_attrib);
}

void ShaderProgram::Destroy() {
  glDeleteProgram(shader_program);
  glDeleteShader(fragment_shader);
  glDeleteShader(vertex_shader);
  glDeleteBuffers(1, &vertex_buffer);
  glDeleteVertexArrays(1, &vertex_array);
}
