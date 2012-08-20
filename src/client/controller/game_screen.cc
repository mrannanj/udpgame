#include <iostream>

#include "client/view/window.h"
#include "client/controller/game_screen.h"
#include "client/controller/screen_stack.h"
#include "client/controller/input/input.h"
#include "client/view/world_renderer.h"
#include "common/world/components/grid.h"

#include <glm/glm.hpp>

GameScreen::GameScreen()
{
}

void GameScreen::Activate()
{
  grab_mouse();
}

void GameScreen::Update(InputManager& input_reader, float dt)
{
  Input input;
  input_reader.ReadInput(input);
  if (input.actions_ & Action::ESCAPE)
  {
    g_screen_stack.pop();
    return;
  }
  if (input.actions_ & Action::SPAWN_UNIT)
  {
    m_entity_manager.spawn_entity();
  }

  m_perspective.handle_input(input);
  m_entity_manager.tick(dt);
  m_perspective.tick();
}

void GameScreen::Draw(const Renderer& r)
{
  r.text_renderer.On();
  r.text_renderer.DrawText(-1.0f, -0.9f, 0.1f, m_perspective.pos_string(), Green);

  glm::mat4 vp = m_perspective.get_view_projection_matrix();

  draw_grid(r, g_grid, vp);
  draw_units(r, g_physics_system, vp);
}

GameScreen g_game_screen;
