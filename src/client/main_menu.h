#ifndef CLIENT_MAIN_MENU_H
#define CLIENT_MAIN_MENU_H

#include "client/game_state.h"

class MainMenu: public GameState
{
public:
  bool Update(InputReader*, Real);
  void Draw(const Renderer&);
};

#endif
