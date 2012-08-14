#include <glm/glm.hpp>
#include "client/view/triangle_renderer.h"

TriangleRenderer::TriangleRenderer():
  Shader("resources/shaders/triangle.vert", "resources/shaders/triangle.frag")
{
  Init();
}

void TriangleRenderer::Init()
{
  glUseProgram(shader_program);
  glBindFragDataLocation(shader_program, 0, "frag_color");

  GLint position = glGetAttribLocation(shader_program, "position");
  glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(position);

  color_uniform_ = glGetUniformLocation(shader_program, "color");
  mvp_uniform_ = glGetUniformLocation(shader_program, "mvp");
  glUseProgram(0);
}

void TriangleRenderer::On() const {
  glUseProgram(shader_program);
  glBindVertexArray(vertex_array);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
}

void TriangleRenderer::Off() const {
  glUseProgram(0);
}

void TriangleRenderer::SetColor(float r, float g, float b) const {
  glUniform3f(color_uniform_, r, g, b);
}

void TriangleRenderer::DrawTriangles(
  float* vertices,
  size_t n,
  const glm::mat4& mvp) const
{
  glUniformMatrix4fv(mvp_uniform_, 1, GL_FALSE, (float*)&mvp);

  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6*n, vertices, GL_STREAM_DRAW);
  glDrawArrays(GL_TRIANGLES, 0, 3*(GLsizei)n);
}

