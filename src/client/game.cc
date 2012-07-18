
#include <SDL.h>
#include <GL/glew.h>
#include <stdlib.h>

#include "client/game.h"

Game::Game() {
}

void Game::Init() {
  area_.units_[0].pos_[0] = 0.2f;
  area_.units_[0].pos_[1] = 0.2f;

  area_.units_[1].pos_[0] = -0.2f;
  area_.units_[1].pos_[1] = -0.2f;

  graphics_.Init();
}

void Game::UpdateVertices() {
  for (size_t i = 0; i < 12; ++i) {
    vertices_[i] = (random()/(float)RAND_MAX)*2.0f - 1.0f;
  }
}

void Game::Run()
{
  SDL_Event windowEvent;
  while (true)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (SDL_PollEvent(&windowEvent ))
    {
      if (windowEvent.type == SDL_QUIT) break;
    }
    UpdateVertices();
    graphics_.DrawTriangles(vertices_, 12);

    SDL_GL_SwapBuffers();
  }

}
