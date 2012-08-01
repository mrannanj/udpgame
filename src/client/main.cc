#include <SDL.h>

#include "client/input/input_reader.h"
#include "client/state_stack.h"
#include "client/main_menu.h"

int main(void)
{
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL);
  SDL_WM_SetCaption("udpgame", 0);

  glewExperimental = GL_TRUE;
  glewInit();

  InputReader input_reader;
  Renderer renderer;
  StateStack state_stack;
  MainMenu main_menu;

  input_reader.Init();
  renderer.Init();
  state_stack.PushState(&main_menu);

  for (;;) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (state_stack.Update(&input_reader, 1.0f)) break;
    state_stack.Draw(renderer);
    SDL_GL_SwapBuffers();
  }

  SDL_Quit();
  return 0;
}
