#pragma once

#include "common/world/components/world_handler.h"
#include "common/proto/udpgame.pb.h"
#include "common/util/hash.h"

class LifetimeHandler : public WorldHandler<Lifetime, Lifetime> {
public:
  void tick(float, World&);
};

template<>
uint32_t inline thash<Lifetime>(const Lifetime& l) {
  return thash(l.eid()) ^ thash(l.ttl());
}
