#pragma once

#include "common/proto/udpgame.pb.h"
#include "common/net/connection.h"

#include <vector>
#include <map>

#define HASH_MAX 10

struct WorldTicker {
  bool handleAMessage(const AMessage&, int);
  const FrameInputs& inputsForFrame(unsigned);
  void fillMissingInputs(unsigned, const std::vector<Connection>&);
  void removeOldFrame(unsigned);
  void setHash(unsigned, unsigned);
  void setCurrentTick(unsigned);
  unsigned getHash(unsigned);

  unsigned mCurrentTick;
  unsigned mHashes[HASH_MAX];
  std::map<unsigned, FrameInputs> mInputMap;
};
