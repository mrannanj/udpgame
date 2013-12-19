#include <SDL.h>
#include <iostream>

#include "common/config.h"
#include "client/view/window.h"
#include "client/controller/input/input_manager.h"
#include "client/controller/screen_stack.h"
#include "client/controller/main_menu.h"

#include "client/client.h"

Client::Client(unsigned ticks_per_sec, volatile int& quit):
  m_tick_timer(ns_per_tick(ticks_per_sec)),
  m_quit(quit)
{
}

void Client::run() {
  open_window();

  InputManager input_manager;
  Renderer renderer;

  g_screen_stack.push(&g_main_menu);

  while (!g_screen_stack.empty()) {
    m_tick_timer.start_tick();
    Screen* screen = g_screen_stack.back();
    if (g_screen_stack.check_dirty())
      screen->Activate();

    screen->Update(input_manager, 0.05f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    screen->Draw(renderer);
    SDL_GL_SwapBuffers();
    m_tick_timer.end_tick();
  }

  SDL_Quit();
}

