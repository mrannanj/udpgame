#pragma once

#include "common/world/components/world_handler.h"
#include "common/proto/udpgame.pb.h"

class LifetimeHandler : public WorldHandler<Lifetime, Lifetime> {
public:
  void tick(float, World& w);
};
