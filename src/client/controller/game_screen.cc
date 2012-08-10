#include "client/controller/game_screen.h"
#include "client/controller/screen_stack.h"
#include "client/controller/input/input.h"

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
  r.text_renderer.DrawText(-0.5f, 0.0f, 0.1f, "game here", Red);
}

GameScreen g_game_screen;
