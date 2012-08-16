#include "client/view/window.h"
#include "client/controller/game_screen.h"
#include "client/controller/screen_stack.h"
#include "client/controller/input/input.h"

#include <glm/glm.hpp>

GameScreen::GameScreen()
{
}

void GameScreen::Activate()
{
  grab_mouse();
}

void GameScreen::Update(InputManager& input_reader, Real)
{
  Input input;
  input_reader.ReadInput(input);
  if (input.escape) {
    g_screen_stack.pop();
  }
  m_camera.handle_input(input);
  m_camera.update();
}

void GameScreen::Draw(const Renderer& r)
{
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 mvp = m_camera.get_view_projection_matrix() * model;
  r.cube_renderer.On();
  r.cube_renderer.SetTexture(r.texture_manager[Texture::GRASS]);
  r.cube_renderer.DrawCube(mvp);
}

GameScreen g_game_screen;
