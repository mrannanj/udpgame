#include <SDL.h>

#include "client/view/window.h"
#include "client/controller/input/input_reader.h"
#include "client/controller/screen_stack.h"
#include "client/controller/main_menu.h"

void InitVideo()
{
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL);
  SDL_WM_SetCaption("udpgame", 0);

  glewExperimental = GL_TRUE;
  glewInit();
}

int main(void)
{
  InitVideo();

  InputReader input_reader;
  Renderer renderer;

  input_reader.Init();
  renderer.Init();
  g_screen_stack.push_back(&g_main_menu);

  for (;;) {
    if (g_screen_stack.empty()) break;
    Screen* screen = g_screen_stack.back();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    screen->Update(input_reader, 1.0f);
    screen->Draw(renderer);
    SDL_GL_SwapBuffers();
  }

  SDL_Quit();
  return 0;
}

