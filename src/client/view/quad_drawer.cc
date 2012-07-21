#include "client/view/quad_drawer.h"

QuadDrawer::QuadDrawer():
  sp()
{
}

void QuadDrawer::Init() {
  sp.Init("resources/shaders/simple.vert", "resources/shaders/simple.frag");
}

void QuadDrawer::DrawQuads(float* vertices, size_t n) {
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8*n, vertices, GL_STREAM_DRAW);
  glDrawArrays(GL_QUADS, 0, 4*(GLsizei)n);
}

