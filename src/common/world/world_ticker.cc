#include "common/world/world_ticker.h"

void WorldTicker::handleAMessage(const AMessage& a, int fd) {
  if (a.type() == Type::CLIENT_INPUT) {
    mCi = a.input();
    mFd = fd;
    mInputSet = true;
  }
}

bool WorldTicker::canTick() {
  if (mInputSet) {
    mInputSet = false;
    return true;
  }
  return false;
}
