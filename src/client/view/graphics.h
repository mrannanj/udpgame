#ifndef CLIENT_VIEW_GRAPHICS_H
#define CLIENT_VIEW_GRAPHICS_H

#include <GL/glew.h>
#include "common/google.h"

class World;

class Graphics {
  public:
  Graphics();

  void Init();
  void InitTriangles();
  void DrawTriangles(float[], size_t);
  void DrawWorld(const World&);

  private:
  DISALLOW_COPY_AND_ASSIGN(Graphics);
  GLuint vao_units_;
  GLuint vbo_units_;
};

#endif

