#include <SDL.h>

#include "client/input/input_reader.h"
#include "client/screen_stack.h"
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
  ScreenStack screen_stack;
  MainMenu main_menu;

  input_reader.Init();
  renderer.Init();
  screen_stack.PushScreen(&main_menu);

  for (;;) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (screen_stack.Update(&input_reader, 1.0f)) break;
    screen_stack.Draw(renderer);
    SDL_GL_SwapBuffers();
  }

  SDL_Quit();
  return 0;
}
