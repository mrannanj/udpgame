#include <iostream>

#include "client/view/quad_renderer.h"

static GLuint elements[] = {
  0, 1, 2,
  0, 3, 1
};

QuadRenderer::QuadRenderer(const ResourceLocator& rl):
  Shader(rl, "resources/shaders/quad.vert", "resources/shaders/quad.frag"),
  m_color_uni(),
  m_element_buffer()
{
  glUseProgram(shader_program);
  glBindFragDataLocation(shader_program, 0, "frag_color");
  m_color_uni = glGetUniformLocation(shader_program, "color");

  GLint position = glGetAttribLocation(shader_program, "position");
  glEnableVertexAttribArray(position);
  glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

  glGenBuffers(1, &m_element_buffer);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    sizeof(elements), elements, GL_STATIC_DRAW);
}

GLint QuadRenderer::color_uni() const
{
  return m_color_uni;
}

void QuadRenderer::On() const
{
  Shader::On();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer);
}

void QuadRenderer::draw_quad(float* v) const
{
  glBufferData(GL_ARRAY_BUFFER, 4*2*sizeof(float), v, GL_STREAM_DRAW);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

