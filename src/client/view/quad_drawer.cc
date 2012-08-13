#include "client/view/quad_drawer.h"

QuadDrawer::QuadDrawer():
  sp_("resources/shaders/simple.vert", "resources/shaders/quad.frag")
{
}

void QuadDrawer::Init() {
  GLint pos_attrib = glGetAttribLocation(sp_.shader_program, "position");
  glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(pos_attrib);

  color_uniform_ = glGetUniformLocation(sp_.shader_program, "quadColor");
}

void QuadDrawer::SetColor(float r, float g, float b) {
  glUniform3f(color_uniform_, r, g, b);
}

void QuadDrawer::DrawQuads(float* vertices, size_t n) {
  glUseProgram(sp_.shader_program);
  glBindVertexArray(sp_.vertex_array);
  glBindBuffer(GL_ARRAY_BUFFER, sp_.vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8*n, vertices, GL_STREAM_DRAW);
  glDrawArrays(GL_QUADS, 0, 4*(GLsizei)n);
}

