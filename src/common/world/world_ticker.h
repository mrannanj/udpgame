#pragma once

#include "common/proto/udpgame.pb.h"

struct WorldTicker {
  void handleAMessage(const AMessage& a, int fd);
  bool canTick();

  ClientInput mCi;
  int mFd;
  bool mInputSet;
};
