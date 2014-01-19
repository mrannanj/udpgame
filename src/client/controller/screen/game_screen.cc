#include "client/view/window.h"
#include "client/view/world_renderer.h"
#include "client/controller/screen/game_screen.h"
#include "client/controller/screen/screen_stack.h"
#include "client/controller/screen/main_menu.h"
#include "client/controller/input/input.h"
#include "common/world/components/grid_handler.h"
#include "common/proto/udpgame.pb.h"

#include "common/include/glm.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <fcntl.h>

using namespace std;

GameScreen::GameScreen() {
}

void GameScreen::Activate() {
  grab_mouse();
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void GameScreen::Update(GameSession&, Input& input) {
  if (input.consume_discrete_action(DiscreteAction::TOGGLE_MOUSEGRAB)) {
    toggle_mousegrab();
  }
  if (input.consume_discrete_action(DiscreteAction::ESCAPE)) {
    g_screen_stack.switch_state(&g_main_menu);
    return;
  }
}

void GameScreen::Draw(GameSession& gs, const Renderer& r) {
  if (gs.mInit and gs.mRedraw) gs.draw(r);
}

bool GameScreen::redraw(GameSession& gs) {
  return gs.mRedraw;
}

GameScreen g_game_screen;
