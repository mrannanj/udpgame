#include <signal.h>
#include <cstring>
#include <SDL.h>
#include <iostream>
#include <string>

#ifndef _WIN32
#include <unistd.h>
#endif

#include "common/config.h"
#include "common/resource_locator.h"
#include "client/view/window.h"
#include "client/controller/input/input_manager.h"
#include "client/controller/screen/screen_stack.h"
#include "client/controller/screen/main_menu.h"
#include "client/controller/screen/game_screen.h"
#include "client/controller/game_session.h"

using namespace std;

int main(int argc, char** argv) {
  bool fullscreen = false;
  string server_address = "";
#ifndef _WIN32
  int opt;
  while ((opt = getopt(argc, argv, "fs:")) != -1) {
    switch (opt) {
      case 'f':
        fullscreen = true;
        break;
      case 's':
        server_address = optarg;
        break;
      default:
        cerr << "usage: " << argv[0] << " [-fs server_address]" << endl;
        return EXIT_SUCCESS;
    }
  }
#endif
  open_window(fullscreen);

  GameSession gameSession(server_address);
  InputManager input_manager;
  Renderer renderer;

  g_screen_stack.push(&g_main_menu);
  if (gameSession.mInit)
    g_screen_stack.push(&g_game_screen);

  while (!g_screen_stack.empty()) {
    Input input;
    input_manager.read_input(input);

    Screen* screen = g_screen_stack.back();
    if (g_screen_stack.check_dirty())
      screen->Activate();

    gameSession.tick(input, screen == &g_game_screen);
    screen->Update(gameSession, input);

    if (screen->redraw(gameSession)) {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      screen->Draw(gameSession, renderer);
      SDL_GL_SwapBuffers();
    }
  }

  SDL_Quit();
  exit(0);
}

