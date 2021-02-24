#include <iostream>
#include "client/view/window.h"
#include "client/controller/input/input.h"
#include "client/controller/screen/main_menu.h"
#include "client/controller/screen/connect_menu.h"
#include "client/controller/screen/screen_stack.h"
#include "client/controller/screen/game_screen.h"

MainMenu::MainMenu():
  m_quit(-0.2f, 0.3f, 0.1f, "quit"),
  m_connect(-0.2f, 0.5f, 0.1f, "connect")
{
}

void MainMenu::Update(GameSession&, Input& input) {
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

void MainMenu::Draw(GameSession&, const Renderer& r) {
  m_quit.Draw(r);
  m_connect.Draw(r);
  r.ft_renderer.On();
  r.ft_renderer.DrawText(-0.95f, -0.95f, 0.002f, "UDP game", Blue);
}

void MainMenu::Activate() {
  release_mouse();
}

bool MainMenu::redraw(GameSession&) {
  return true;
}

MainMenu g_main_menu;
