#include "client/controller/game_screen.h"
#include "client/controller/screen_stack.h"
#include "client/controller/input/input.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

GameScreen::GameScreen()
{
}

void GameScreen::Update(InputReader& input_reader, Real)
{
  Input input;
  input_reader.ReadInput(input);
  if (input.actions_ & Action::ESCAPE) {
    g_screen_stack.pop_back();
  }
}

void GameScreen::Draw(const Renderer& r)
{
  glm::mat4 projection = glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
  // Camera matrix
  glm::mat4 view = glm::lookAt(
    glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
    glm::vec3(0,0,0), // and looks at the origin
    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
  // Model matrix : an identity matrix (model will be at the origin)
  glm::mat4 model = glm::mat4(1.0f);  // Changes for each model !
  // Our ModelViewProjection : multiplication of our 3 matrices
  glm::mat4 mvp = projection * view * model;
  float v[] = { 0.0f, 0.5f, 0.5f, 0.0f, -0.5f, 0.0f };
  float v2[] = { -0.0f, -0.5f, -0.5f, -0.0f, 0.5f, -0.0f };
  r.text_renderer.DrawText(-0.5f, -0.9f, 0.1f, "game", Red);
  r.triangle_renderer.On();
  r.triangle_renderer.SetColor(1.0f, 0.5f, 0.2f);
  r.triangle_renderer.DrawTriangles(v, 1, mvp);
  r.triangle_renderer.SetColor(0.0f, 0.5f, 0.2f);
  r.triangle_renderer.DrawTriangles(v2, 1, mvp);
  r.triangle_renderer.Off();
  r.cube_renderer.On();
  r.cube_renderer.SetTexture(r.face_texture);
  r.cube_renderer.DrawCube(mvp);
  r.cube_renderer.Off();
}

GameScreen g_game_screen;
