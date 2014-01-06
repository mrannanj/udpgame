#include "client/view/window.h"
#include "client/view/world_renderer.h"
#include "client/controller/game_screen.h"
#include "client/controller/screen_stack.h"
#include "client/controller/input/input.h"
#include "client/controller/main_menu.h"
#include "common/world/components/grid_handler.h"
#include "common/proto/udpgame.pb.h"

#include <glm/glm.hpp>
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

void GameScreen::Update(GameSession& gs, InputManager& input_reader, float dt) {
  Input input;
  input_reader.read_input(input);
  if (input.consume_discrete_action(DiscreteAction::TOGGLE_MOUSEGRAB)) {
    toggle_mousegrab();
  }
  if (input.consume_discrete_action(DiscreteAction::ESCAPE)) {
    g_screen_stack.switch_state(&g_main_menu);
    return;
  }
  if (gs.mInit) {
    gs.tick(input);
  }
}

void GameScreen::Draw(GameSession& gs, const Renderer& r) {
  r.text_renderer.On();
  if (gs.mInit) {
    r.text_renderer.DrawText(-1.0f, -0.9f, 0.1f,
      gs.mPerspective.pos_string(), Green);
    glm::mat4 vp = gs.mPerspective.get_view_projection_matrix();
    draw_grid(r, gs.mWorld.grid(), vp);
    draw_units(r, gs.mWorld.physics(), vp);
  }

  float q[] = {
    -0.005f, -0.005f, 0.005f, 0.005f,
    -0.005f, 0.005f, 0.005f, -0.005f
  };
  r.quad_renderer.On();
  r.quad_renderer.draw_quad(q);
}

GameScreen g_game_screen;
