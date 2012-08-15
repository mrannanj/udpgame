#ifndef CLIENT_VIEW_RENDERER_H
#define CLIENT_VIEW_RENDERER_H

#include "client/view/text_renderer.h"
#include "client/view/cube_renderer.h"
#include "client/view/triangle_renderer.h"
#include "client/view/texture_manager.h"

class Renderer {
public:
  Renderer();
  DISALLOW_COPY_AND_ASSIGN(Renderer);

  TextureManager texture_manager;
  TextRenderer text_renderer;
  TriangleRenderer triangle_renderer;
  CubeRenderer cube_renderer;

  GLuint face_texture;
};

#endif
