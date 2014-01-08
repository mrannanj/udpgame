#pragma once

#include "common/net/connection.h"
#include "common/world/world.h"
#include "client/controller/input/input.h"
#include "client/controller/perspective.h"
#include "client/view/renderer.h"

#include <string>

struct GameSession {
  GameSession();
  GameSession(const std::string&);

  bool tick(float, Input&);
  void sendFrameInput(Input&);
  bool handleAMessage(const AMessage&, int);
  void draw(const Renderer&);

  int mClientId;
  bool mInit;
  bool mDraw;
  Connection mConnection;
  Perspective mPerspective;
  World mWorld;
  Input mInput;
};

