#ifndef CLIENT_VIEW_GRAPHICS_H
#define CLIENT_VIEW_GRAPHICS_H

#include <GL/glew.h>
#include "common/google.h"
#include "client/view/quad_drawer.h"
#include "client/view/triangle_drawer.h"
#include "client/view/texture_manager.h"

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
  QuadDrawer quad_drawer_;
  TriangleDrawer triangle_drawer_;
};

#endif

