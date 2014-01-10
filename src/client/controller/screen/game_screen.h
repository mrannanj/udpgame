#pragma once

#include <string>
#include <netinet/in.h>

#include "client/controller/screen/screen.h"
#include "client/controller/perspective.h"
#include "client/controller/game_session.h"
#include "common/world/world.h"
#include "common/config.h"

struct GameScreen : public Screen {
  GameScreen();
  void Update(GameSession&, Input&);
  void Draw(GameSession&, const Renderer&);
  void Activate();
  bool redraw(GameSession&);

  bool mDraw;
};

extern GameScreen g_game_screen;
