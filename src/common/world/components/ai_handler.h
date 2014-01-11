#pragma once

#include "common/world/components/world_handler.h"
#include "common/proto/udpgame.pb.h"

class AiHandler : public WorldHandler<Ai, Ai> {
public:
  void tick(float, World&);
};
