#pragma once

#include "common/proto/udpgame.pb.h"

struct WorldTicker {
  void handleAMessage(const AMessage& a);
  bool canTick();

  ClientInput mCi;
  bool mInputSet;
};
