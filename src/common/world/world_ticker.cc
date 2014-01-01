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
  if (a.type() != Type::CLIENT_INPUT) {
    cout << "wrong message type" << endl;
    return false;
  }
  if (a.input().tick_number() != mFrameNum) {
    cout << "wrong tick number" << endl;
    cout << "expected: " << mFrameNum << endl;
    cout << "was: " << a.input().tick_number() << endl;
    return false;
  }
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
