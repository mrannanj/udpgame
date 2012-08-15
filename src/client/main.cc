#include <SDL.h>

#include "client/view/window.h"
#include "client/controller/input/input_reader.h"
#include "client/controller/screen_stack.h"
#include "client/controller/main_menu.h"

int main(void)
{
  open_window();

  InputReader input_reader;
  Renderer renderer;

  input_reader.Init();
  g_screen_stack.push_back(&g_main_menu);

  while(!g_screen_stack.empty())
  {
    Screen* screen = g_screen_stack.back();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    screen->Update(input_reader, 1.0f);
    screen->Draw(renderer);
    SDL_GL_SwapBuffers();
  }

  SDL_Quit();
  return 0;
}
