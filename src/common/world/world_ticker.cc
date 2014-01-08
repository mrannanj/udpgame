#include <iostream>

#include "common/world/world_ticker.h"

using namespace std;

WorldTicker::WorldTicker(size_t numClients, unsigned frameNum, unsigned hash):
  mNumClients(numClients),
  mPreviousHash(hash),
  mFrameNum(frameNum),
  mFrameInputs()
{
  mFrameInputs.set_tick_number(mFrameNum);
}

bool WorldTicker::handleAMessage(const AMessage& a, int clientid) {
  if (a.client_input().previous_hash() != mPreviousHash) {
    cout << "last hash differs for " << clientid << endl;
    cout << "expected: " << mPreviousHash << endl;
    cout << "was: " << a.client_input().previous_hash() << endl;
    return false;
  }
  FrameInput* fi = mFrameInputs.add_frame_inputs();
  fi->CopyFrom(a.client_input().frame_input());
  fi->set_client(clientid);
  return true;
}

// FIXME: lol
bool WorldTicker::ok() {
  return mNumClients == (size_t)mFrameInputs.frame_inputs_size();
}

void WorldTicker::nextWait(size_t numClients, unsigned frameNum,
    unsigned hash)
{
  mNumClients = numClients;
  mFrameNum = frameNum;
  mPreviousHash = hash;
  mFrameInputs.clear_frame_inputs();
  mFrameInputs.set_tick_number(mFrameNum);
}

const FrameInputs& WorldTicker::frameInputs() {
  return mFrameInputs;
}
