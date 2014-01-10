#pragma once

#include "client/controller/screen/screen.h"
#include "client/view/button.h"
#include "client/view/text_field.h"

class ConnectMenu : public Screen {
public:
  ConnectMenu();
  void Update(GameSession&, Input&);
  void Draw(GameSession&, const Renderer&);
  void Activate();
  bool redraw(GameSession&);

private:
  TextField m_address;
  Button m_go;
  Button m_cancel;
};

extern ConnectMenu g_connect_menu;
