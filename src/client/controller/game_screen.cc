#include "client/view/window.h"
#include "client/controller/game_screen.h"
#include "client/controller/screen_stack.h"
#include "client/controller/input/input.h"
#include "client/view/world_renderer.h"
#include "client/controller/main_menu.h"
#include "common/world/components/grid.h"
#include "common/util/die.h"
#include "common/proto/udpgame.pb.h"

#include <glm/glm.hpp>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <fcntl.h>

using namespace std;

GameScreen::GameScreen()
{
}

void GameScreen::Activate() {
  grab_mouse();
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void GameScreen::Update(InputManager& input_reader, float dt) {
  Input input;
  input_reader.read_input(input);
  if (input.consume_discrete_action(DiscreteAction::ESCAPE)) {
    g_screen_stack.switch_state(&g_main_menu);
    return;
  }
  if (g_game_session) {
    g_game_session->tick(input);
  }
}

void GameScreen::Draw(const Renderer& r) {
  r.text_renderer.On();
  if (g_game_session) {
    r.text_renderer.DrawText(-1.0f, -0.9f, 0.1f,
      g_game_session->mPerspective.pos_string(), Green);
    glm::mat4 vp = g_game_session->mPerspective.get_view_projection_matrix();
    draw_grid(r, g_grid, vp);
    draw_units(r, g_physics_system, vp);
  }
}

GameScreen g_game_screen;
