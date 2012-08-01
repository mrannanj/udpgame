#ifndef CLIENT_VIEW_GRAPHICS_H
#define CLIENT_VIEW_GRAPHICS_H

#include <GL/glew.h>
#include "common/google.h"
#include "client/view/texture_manager.h"
#include "client/view/text_renderer.h"

class World;

class Graphics {
  public:
  Graphics();

  void Init();
  void Destroy();

  void DrawWorld(const World&);

  private:
  DISALLOW_COPY_AND_ASSIGN(Graphics);

  void InitVideo();

  TextureManager texture_manager_;
  TextRenderer text_renderer_;
};

#endif

