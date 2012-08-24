#include <iostream>
#include "client/view/window.h"
#include "client/controller/main_menu.h"
#include "client/controller/connect_menu.h"
#include "client/controller/input/input.h"
#include "client/controller/screen_stack.h"
#include "client/controller/game_screen.h"

MainMenu::MainMenu():
  m_quit(-0.2f, 0.3f, 0.1f, "quit"),
  m_connect(-0.2f, 0.5f, 0.1f, "connect")
{
}

void MainMenu::Update(InputManager& input_manager, float)
{
  Input input;
  input_manager.read_input(input);

  if (input.consume_discrete_action(DiscreteAction::ESCAPE)) {
    g_screen_stack.pop();
  }

  if (m_quit.Update(input)) {
    g_screen_stack.clear();
  }

  if (m_connect.Update(input)) {
    g_screen_stack.push(&g_connect_menu);
  }
}

void MainMenu::Draw(const Renderer& r)
{
  m_quit.Draw(r);
  m_connect.Draw(r);
  r.text_renderer.On();
  r.text_renderer.DrawText(-1.0f, -0.9f, 0.1f, "UDP Game!", Blue);
}

void MainMenu::Activate()
{
  release_mouse();
}

MainMenu g_main_menu;
