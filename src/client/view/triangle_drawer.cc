#include "client/view/triangle_drawer.h"

TriangleDrawer::TriangleDrawer():
  sp_()
{
}

void TriangleDrawer::Init() {
  sp_.Init("resources/shaders/simple.vert", "resources/shaders/triangle.frag");
  color_uniform_ = glGetUniformLocation(sp_.shader_program, "triangleColor");
}

void TriangleDrawer::SetColor(float r, float g, float b) {
  glUniform3f(color_uniform_, r, g, b);
}

void TriangleDrawer::DrawTriangles(float* vertices, size_t n) {
  glUseProgram(sp_.shader_program);
  glBindVertexArray(sp_.vertex_array);
  glBindBuffer(GL_ARRAY_BUFFER, sp_.vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6*n, vertices, GL_STREAM_DRAW);
  glDrawArrays(GL_TRIANGLES, 0, 3*(GLsizei)n);
}

