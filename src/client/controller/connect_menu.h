#ifndef CLIENT_CONTROLLER_CONNECT_MENU_H
#define CLIENT_CONTROLLER_CONNECT_MENU_H

#include "client/controller/screen.h"
#include "client/view/button.h"

class ConnectMenu : public Screen
{
public:
  ConnectMenu();
  void Update(InputManager&, float);
  void Draw(const Renderer&);
  void Activate();

private:
  Button m_go;
  Button m_cancel;
};

extern ConnectMenu g_connect_menu;

#endif
