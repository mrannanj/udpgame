#include <iostream>
#include "client/view/window.h"
#include "client/controller/main_menu.h"
#include "client/controller/input/input.h"
#include "client/controller/screen_stack.h"
#include "client/controller/game_screen.h"

MainMenu::MainMenu():
  quit_(-0.2f, 0.3f, 0.1f, "quit"),
  start_(-0.2f, 0.5f, 0.1f, "start")
{
}

void MainMenu::Update(InputReader& input_reader, Real)
{
  Input input;
  input_reader.ReadInput(input);

  if (input.actions_ & Action::ESCAPE) {
    g_screen_stack.pop_back();
  }

  if (quit_.Update(input)) {
    g_screen_stack.clear();
  }

  if (start_.Update(input)) {
    g_screen_stack.push_back(&g_game_screen);
  }
}

void MainMenu::Draw(const Renderer& r)
{
  quit_.Draw(r);
  start_.Draw(r);
  r.text_renderer.DrawText(-1.0f, -0.9f, 0.1f, "UDP Game!", Blue);
}

MainMenu g_main_menu;
