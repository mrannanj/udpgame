#pragma once

#include "common/net/connection.h"
#include "common/world/world.h"
#include "client/controller/perspective.h"

#include <string>

struct GameSession {
  GameSession();
  GameSession(const std::string&);

  void tick(float, Input&);
  void sendFrameInput(Input&);
  bool handleAMessage(const AMessage&, int);

  int mClientId;
  bool mInit;
  Connection mConnection;
  Perspective mPerspective;
  World mWorld;
};

