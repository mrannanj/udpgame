#pragma once

#include "common/proto/udpgame.pb.h"
#include <vector>

struct WorldTicker {
  WorldTicker(size_t, unsigned, unsigned);
  bool handleAMessage(const AMessage&, int);
  bool ok();
  void nextWait(size_t, unsigned, unsigned);
  const FrameInputs& frameInputs();

  size_t mNumClients;
  unsigned mPreviousHash;
  unsigned mFrameNum;
  FrameInputs mFrameInputs;
};
