#pragma once

#include "client/controller/screen.h"
#include "client/view/button.h"

class MainMenu: public Screen {
public:
  MainMenu();
  void Update(InputManager&, float);
  void Draw(const Renderer&);
  void Activate();

private:
  Button m_quit;
  Button m_connect;
};

extern MainMenu g_main_menu;
