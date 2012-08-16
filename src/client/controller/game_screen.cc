#include "client/view/window.h"
#include "client/controller/game_screen.h"
#include "client/controller/screen_stack.h"
#include "client/controller/input/input.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
  glm::mat4 vp_matrix = m_camera.get_view_projection_matrix();

  r.cube_renderer.On();
  r.cube_renderer.SetTexture(r.texture_manager[Texture::GRASS]);

  for (unsigned x = 0; x < WORLD_MAX_X; ++x) {
    for (unsigned y = 0; y < WORLD_MAX_Y; ++y) {
      for (unsigned z = 0; z < WORLD_MAX_Z; ++z) {
        char block = m_world.block(x,y,z);
        if (block > 8)
        {
          glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3((float)x,(float)y,(float)z));
          r.cube_renderer.DrawCube(vp_matrix * model);
        }
      }
    }
  }
}

GameScreen g_game_screen;
