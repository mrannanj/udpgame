#ifndef CLIENT_CONTROLLER_MAIN_MENU_H
#define CLIENT_CONTROLLER_MAIN_MENU_H

#include "client/controller/screen.h"
#include "client/view/button.h"

class MainMenu: public Screen
{
public:
  MainMenu();
  void Update(InputReader&, Real);
  void Draw(const Renderer&);
private:
  Button quit_;
  Button start_;
};

extern MainMenu g_main_menu;

#endif
