#pragma once

#include "common/world/components/world_handler.h"
#include "common/proto/udpgame.pb.h"

struct DamageHandler : public WorldHandler<Damage, Damage> {
  void tick(float, World&);
};

template<>
uint32_t inline thash<Damage>(const Damage& d) {
  return thash(d.eid()) ^ thash(d.damage());
}
