#pragma once

#include "common/net/connection.h"
#include "common/world/world.h"
#include "client/controller/perspective.h"

#include <string>

struct GameSession {
  GameSession();
  GameSession(const std::string&);

  void tick(Input&);
  void sendFrameInput(Input&);
  bool handleAMessage(const AMessage&, int);

  bool mInit;
  Connection mConnection;
  Perspective mPerspective;
  World mWorld;
};

