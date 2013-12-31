#include "common/world/world_ticker.h"

WorldTicker::WorldTicker():
  mNumClients(0)
{
}

void WorldTicker::handleAMessage(const AMessage& a, int fd) {
  if (a.type() == Type::CLIENT_INPUT) {
    InputC ic(a.input());
    ic.mClient = fd;
    mInputs.push_back(ic);
  }
}

bool WorldTicker::ok() {
  return mNumClients == mInputs.size();
}

void WorldTicker::nextWait(size_t numClients) {
  mNumClients = numClients;
  mInputs.clear();
}
