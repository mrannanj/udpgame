#pragma once

#include "common/proto/udpgame.pb.h"
#include "common/world/components/inputc.h"
#include <vector>

struct WorldTicker {
  WorldTicker(size_t, unsigned);
  bool handleAMessage(const AMessage&, int);
  bool ok();
  void nextWait(size_t, unsigned);

  size_t mNumClients;
  unsigned mFrameNum;
  std::vector<InputC> mInputs;
};
