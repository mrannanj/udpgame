#ifndef CLIENT_VIEW_GRAPHICS_H
#define CLIENT_VIEW_GRAPHICS_H

#include <GL/glew.h>
#include "common/google.h"

class World;

class Graphics {
  public:
  Graphics();

  void Init();
  void Destroy();

  void DrawWorld(const World&);

  private:
  DISALLOW_COPY_AND_ASSIGN(Graphics);

  void InitTriangles();
  void DestroyTriangles();
  void DrawTriangles(float[], size_t);

  GLuint vao_units_;
  GLuint vbo_units_;
  GLuint triangle_program_;
};

#endif

