#include <signal.h>
#include <cstring>
#include <unistd.h>
#include <SDL.h>
#include <iostream>
#include <string>

#include "common/config.h"
#include "client/view/window.h"
#include "client/controller/input/input_manager.h"
#include "client/controller/screen_stack.h"
#include "client/controller/main_menu.h"
#include "client/controller/game_session.h"
#include "client/controller/game_screen.h"

using namespace std;

int main(int argc, char** argv) {
  if (strcmp(argv[0], "/usr/bin/udpgame_client"))
    chdir("/usr/share/udpgame");
  open_window();

  string server_address;
  if (argc >= 2)
    server_address = string(argv[1]);

  GameSession gameSession(server_address);
  InputManager input_manager;
  Renderer renderer;

  g_screen_stack.push(&g_main_menu);
  if (argc >= 2)
    g_screen_stack.push(&g_game_screen);

  while (!g_screen_stack.empty()) {
    Screen* screen = g_screen_stack.back();
    if (g_screen_stack.check_dirty())
      screen->Activate();

    screen->Update(gameSession, input_manager, secs_per_tick);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    screen->Draw(gameSession, renderer);
    SDL_GL_SwapBuffers();
  }

  SDL_Quit();
}

