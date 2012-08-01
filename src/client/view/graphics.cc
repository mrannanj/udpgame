#include <alloca.h>
#include <iostream>
#include <math.h>
#include <SDL.h>

#include "client/view/graphics.h"
#include "client/view/shader_loader.h"
#include "common/world/world.h"

Graphics::Graphics() {
}

void Graphics::Init() {
  InitVideo();
  GLuint font_texture = texture_manager_.LoadImage("resources/images/font.bmp");
  text_renderer_.Init(font_texture);
}

void Graphics::InitVideo() {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL);
  SDL_WM_SetCaption("udpgame", 0);

  glewExperimental = GL_TRUE;
  glewInit();
}

void Graphics::Destroy() {
  texture_manager_.FreeTextures();
}

void Graphics::DrawWorld(const World& /*w*/) {
  text_renderer_.DrawText(-1.0f, -0.9f, 0.1f, "udpgame");

#if 0
  float q[] = {-0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f};
  quad_drawer_.DrawQuads(q, 1);
  float t[] = {0.0f, 1.0f, 0.5f, 0.5f, -0.5f, 0.5f};
  triangle_drawer_.DrawTriangles(t, 1);
  const std::map<EntityId, Entity>& entities = w.entities();
  float* vs = (float*) alloca(sizeof(float) * entities.size() * 6);
  float* p = vs;
  float size = 0.2f;
  for (const auto& kv : entities) {
    const Entity& e = kv.second;
    vs[0] = e.x_;
    vs[1] = e.y_ + size;
    vs[2] = e.x_ + size;
    vs[3] = e.y_;
    vs[4] = e.x_ - size;
    vs[5] = e.y_;
    p += 6;
  }
  DrawTriangles(vs, entities.size());
#endif
}

