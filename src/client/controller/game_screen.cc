#include <iostream>

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
  glm::mat4 vp_matrix = m_perspective.get_view_projection_matrix();

  r.text_renderer.On();
  r.text_renderer.DrawText(-0.9f, -0.8f, 0.1f, m_perspective.pos_string(), Green);

  r.cube_renderer.On();
  r.cube_renderer.SetTexture(r.texture_manager[Texture::GRASS]);

  for (unsigned x = 0; x < WORLD_MAX_X; ++x) {
    for (unsigned y = 0; y < WORLD_MAX_Y; ++y) {
      for (unsigned z = 0; z < WORLD_MAX_Z; ++z) {
        char block = m_entity_manager.m_blocks[x][y][z];
        if (block)
        {
          glm::mat4 model = glm::translate(
            glm::mat4(1.0f),
            glm::vec3((float)x,(float)y,(float)z)
          );
          r.cube_renderer.DrawCube(vp_matrix * model);
        }
      }
    }
  }
}

GameScreen g_game_screen;
