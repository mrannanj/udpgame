#include <SDL.h>
#include <iostream>

#include "client/view/window.h"
#include "client/controller/input/input_manager.h"
#include "client/controller/screen_stack.h"
#include "client/controller/main_menu.h"

constexpr float fps = 60.0f;
constexpr float frame_time = 1.0f/fps;

int main(void)
{
  open_window();

  InputManager input_manager;
  Renderer renderer;

  g_screen_stack.push(&g_main_menu);

  while(!g_screen_stack.empty())
  {
    Screen* screen = g_screen_stack.back();
    if (g_screen_stack.check_dirty())
      screen->Activate();

    screen->Update(input_manager, frame_time);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    screen->Draw(renderer);
    SDL_GL_SwapBuffers();
  }

  SDL_Quit();
  return 0;
}
