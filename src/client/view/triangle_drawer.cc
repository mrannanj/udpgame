#include "client/view/triangle_drawer.h"

TriangleDrawer::TriangleDrawer():
  sp()
{
}

void TriangleDrawer::Init() {
  sp.Init("resources/shaders/simple.vert", "resources/shaders/simple.frag");
}

void TriangleDrawer::DrawTriangles(float* vertices, size_t n) {
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6*n, vertices, GL_STREAM_DRAW);
  glDrawArrays(GL_TRIANGLES, 0, 3*(GLsizei)n);
}

