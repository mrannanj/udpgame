#include "client/controller/connect_menu.h"
#include "client/controller/input/input.h"
#include "client/controller/input/input_manager.h"
#include "client/controller/screen_stack.h"
#include "client/controller/game_screen.h"
#include "client/view/window.h"

ConnectMenu::ConnectMenu():
  m_address(-0.9f, 0.7f, 0.9f, 0.08f, "address here"),
  m_go(-0.2f, 0.5f, 0.1f, "go"),
  m_cancel(-0.2f, 0.3f, 0.1f, "cancel")
{
}

void ConnectMenu::Update(InputManager& input_manager, float)
{
  Input input;
  input_manager.read_input(input);

  if (input.consume_discrete_action(DiscreteAction::ESCAPE)) {
    g_screen_stack.pop();
  }

  if (m_cancel.Update(input)) {
    g_screen_stack.pop();
  }

  if (m_go.Update(input)) {
    g_screen_stack.push(&g_game_screen);
  }

  m_address.Update(input);
}

void ConnectMenu::Draw(const Renderer& r)
{
  m_go.Draw(r);
  m_cancel.Draw(r);
  m_address.Draw(r);
  r.text_renderer.On();
  r.text_renderer.DrawText(-1.0f, -0.9f, 0.1f, "UDP Game", Blue);
}

void ConnectMenu::Activate()
{
  release_mouse();
  glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
}

ConnectMenu g_connect_menu;
