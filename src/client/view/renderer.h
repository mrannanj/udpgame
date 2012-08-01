#ifndef CLIENT_VIEW_RENDERER_H
#define CLIENT_VIEW_RENDERER_H

#include "client/view/text_renderer.h"
#include "client/view/texture_manager.h"

class Renderer {
public:
  Renderer();
  void Init();
  void Destroy();

  TextureManager texture_manager;
  TextRenderer text_renderer;
};

#endif
