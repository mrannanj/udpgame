#pragma once

#include "common/proto/udpgame.pb.h"
#include "common/net/connection.h"

#include <vector>
#include <map>
#include <array>

struct WorldTicker {
  WorldTicker();

  bool handleAMessage(const AMessage&, int);
  const FrameInputs& inputsForFrame(unsigned);
  void fillMissingInputs(unsigned, std::vector<Connection>&);
  void removeOldFrame(unsigned);
  void setHashes(unsigned, const uint32_t*);
  void setCurrentTick(unsigned);
  bool compareHashes(unsigned,
      const google::protobuf::RepeatedField<uint32_t>&);

  unsigned mCurrentTick;
  std::map<unsigned, std::array<uint32_t, HANDLER_COUNT>> mHashes;
  std::map<unsigned, FrameInputs> mInputMap;
};
