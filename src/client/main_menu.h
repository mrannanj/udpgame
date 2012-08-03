#ifndef CLIENT_MAIN_MENU_H
#define CLIENT_MAIN_MENU_H

#include "client/screen.h"

class MainMenu: public Screen
{
public:
  bool Update(InputReader*, Real);
  void Draw(const Renderer&);
};

#endif
