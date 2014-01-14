#pragma once

#include "client/view/shader.h"

class QuadRenderer : public Shader
{
public:
  QuadRenderer(const ResourceLocator&);

  void draw_quad(float*) const;
  GLint color_uni() const;
  void On() const;

private:
  GLint m_color_uni;
  GLuint m_element_buffer;
};
