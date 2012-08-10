#ifndef CLIENT_CONTROLLER_GAME_SCREEN_H
#define CLIENT_CONTROLLER_GAME_SCREEN_H

#include "client/controller/screen.h"

struct GameScreen : public Screen {
public:
  GameScreen();
  void Update(InputReader&, Real);
  void Draw(const Renderer&);
};

extern GameScreen g_game_screen;

#endif
