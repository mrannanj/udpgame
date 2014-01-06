#include <iostream>

#include "common/world/world_ticker.h"

using namespace std;

WorldTicker::WorldTicker(size_t numClients, unsigned frameNum):
  mNumClients(numClients),
  mFrameNum(frameNum),
  mInputs()
{
}

bool WorldTicker::handleAMessage(const AMessage& a, int fd) {
  assert(a.type() == Type::CLIENT_INPUT);
  assert(a.input().tick_number() == mFrameNum);
  InputC ic(a.input());
  ic.mClient = fd;
  mInputs.push_back(ic);
  return true;
}

bool WorldTicker::ok() {
  return mNumClients == mInputs.size();
}

void WorldTicker::nextWait(size_t numClients, unsigned frameNum) {
  mNumClients = numClients;
  mFrameNum = frameNum;
  mInputs.clear();
}
