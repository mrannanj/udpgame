#ifndef CLIENT_MAIN_MENU_H
#define CLIENT_MAIN_MENU_H

#include "client/screen.h"
#include "client/view/button.h"

class MainMenu: public Screen
{
public:
  MainMenu();
  bool Update(InputReader*, Real);
  void Draw(const Renderer&);
private:
  Button quit_;
  Button start_;
};

#endif
