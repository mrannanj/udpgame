#pragma once

#include <string>
#include <netinet/in.h>

#include "client/controller/screen.h"
#include "client/controller/perspective.h"
#include "client/controller/game_session.h"
#include "common/world/world.h"
#include "common/config.h"

struct GameScreen : public Screen {
  GameScreen();
  void Update(InputManager&, float);
  void Draw(const Renderer&);
  void Activate();
};

extern GameScreen g_game_screen;
