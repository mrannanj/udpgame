#include <SDL.h>

#include "client/view/window.h"
#include "client/controller/input/input_manager.h"
#include "client/controller/screen_stack.h"
#include "client/controller/main_menu.h"

int main(void)
{
  open_window();

  InputManager input_manager;
  Renderer renderer;

  g_screen_stack.push_back(&g_main_menu);

  while(!g_screen_stack.empty())
  {
    Screen* screen = g_screen_stack.back();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    screen->On();
    screen->Update(input_manager, 1.0f);
    screen->Draw(renderer);
    SDL_GL_SwapBuffers();
  }

  SDL_Quit();
  return 0;
}
