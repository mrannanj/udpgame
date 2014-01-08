#include <iostream>

#include "server/world_ticker.h"
#include "common/config.h"

using namespace std;

const FrameInputs& WorldTicker::inputsForFrame(unsigned tick) {
  return mInputMap[tick];
}

void WorldTicker::removeOldFrame(unsigned tick) {
  mInputMap.erase(tick);
}

bool WorldTicker::handleAMessage(const AMessage& a, int clientid) {
  unsigned tick = a.client_input().tick_number();
  if (getHash(tick) != a.client_input().previous_hash()) {
    cout << "hash expected: " << getHash(tick) << endl;
    cout << "hash was: " << a.client_input().previous_hash() << endl;
    return false;
  }
  FrameInputs& fis = mInputMap[tick];
  FrameInput* fi = fis.add_frame_inputs();
  fi->CopyFrom(a.client_input().frame_input());
  fi->set_client(clientid);
  return true;
}

unsigned WorldTicker::getHash(unsigned tick) {
  return mHashes[(tick-STATIC_FRAME_DELTA)%HASH_MAX];
}

void WorldTicker::setHash(unsigned tick, unsigned h) {
  mHashes[tick%HASH_MAX] = h;
}

void WorldTicker::setCurrentTick(unsigned tick) {
  mCurrentTick = tick;
}
