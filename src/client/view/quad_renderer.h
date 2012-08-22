#ifndef CLIENT_VIEW_QUAD_RENDERER_H
#define CLIENT_VIEW_QUAD_RENDERER_H

#include "client/view/shader.h"

class QuadRenderer : public Shader
{
public:
  QuadRenderer();
  DISALLOW_COPY_AND_ASSIGN(QuadRenderer);

  void draw_quad(float*) const;
  GLint color_uni() const;
  void On() const;

private:
  GLint m_color_uni;
  GLuint m_element_buffer;
};

#endif
