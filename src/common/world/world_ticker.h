#pragma once

#include "common/proto/udpgame.pb.h"
#include "common/world/components/inputc.h"
#include <vector>

struct WorldTicker {
  WorldTicker();
  void handleAMessage(const AMessage& a, int fd);
  bool ok();
  void nextWait(size_t);

  size_t mNumClients;
  std::vector<InputC> mInputs;
};
