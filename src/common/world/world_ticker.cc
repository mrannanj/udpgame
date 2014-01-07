#include <iostream>

#include "common/world/world_ticker.h"

using namespace std;

WorldTicker::WorldTicker(size_t numClients, unsigned frameNum):
  mNumClients(numClients),
  mFrameNum(frameNum),
  mFrameInputs()
{
  mFrameInputs.set_tick_number(mFrameNum);
}

bool WorldTicker::handleAMessage(const AMessage& a, int fd) {
  FrameInput* fi = mFrameInputs.add_frame_inputs();
  // FIXME: here be assert
  fi->CopyFrom(a.client_input().frame_input());
  fi->set_client(fd);
  return true;
}

// FIXME: lol
bool WorldTicker::ok() {
  return mNumClients == (size_t)mFrameInputs.frame_inputs_size();
}

void WorldTicker::nextWait(size_t numClients, unsigned frameNum) {
  mNumClients = numClients;
  mFrameNum = frameNum;
  mFrameInputs.clear_frame_inputs();
  mFrameInputs.set_tick_number(mFrameNum);
}

const FrameInputs& WorldTicker::frameInputs() {
  return mFrameInputs;
}
