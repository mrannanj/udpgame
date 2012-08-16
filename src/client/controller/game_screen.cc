#include "client/view/window.h"
#include "client/controller/game_screen.h"
#include "client/controller/screen_stack.h"
#include "client/controller/input/input.h"

#include <glm/glm.hpp>

GameScreen::GameScreen()
{
}

void GameScreen::On()
{
  grab_mouse();
}

void GameScreen::Update(InputManager& input_reader, Real)
{
  Input input;
  input_reader.ReadInput(input);
  if (input.actions_ & Action::ESCAPE) {
    g_screen_stack.pop_back();
  }
  m_camera.handle_input(input);
  m_camera.update();
}

void GameScreen::Draw(const Renderer& r)
{
  glm::mat4 model = glm::mat4(1.0f);  // Changes for each model !
  // Our ModelViewProjection : multiplication of our 3 matrices
  glm::mat4 mvp = m_camera.get_view_projection_matrix() * model;
  r.text_renderer.On();
  r.text_renderer.DrawText(-0.5f, -0.9f, 0.1f, "game", Red);
  r.cube_renderer.On();
  r.cube_renderer.SetTexture(r.texture_manager[Texture::GRASS]);
  r.cube_renderer.DrawCube(mvp);
}

GameScreen g_game_screen;
