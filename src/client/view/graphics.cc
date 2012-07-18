#include "client/view/graphics.h"
#include "client/view/video.h"

Graphics::Graphics() {
}

void Graphics::Init() {
  InitTriangles();
}

void Graphics::InitTriangles() {
  glGenVertexArrays(1, &vao_units_);
  glBindVertexArray(vao_units_);

  glGenBuffers(1, &vbo_units_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_units_);

  GLuint prog = LoadShaders("resources/shaders/first.vert",
    "resources/shaders/first.frag");

  GLint posAttrib = glGetAttribLocation(prog, "position");
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(posAttrib);
}

void Graphics::DrawTriangles(float vertices[], size_t n) {
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*n, vertices, GL_STREAM_DRAW);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
