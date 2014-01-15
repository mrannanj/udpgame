#pragma once

#include "common/world/components/world_handler.h"
#include "common/proto/udpgame.pb.h"

class ClientHandler : public WorldHandler<ClientData, ClientData> {
public:
  void tick(float, World&);
  void handleDead(const std::set<EntityId>&);
  void markDead(EntityId);
  void remove(EntityId);
  ClientData* getByClient(int);
  void removeByClient(int);
};

template<>
uint32_t inline thash<ClientData>(const ClientData& cd) {
  return thash(cd.client())
    ^ thash(cd.mode())
    ^ thash(cd.eid())
    ^ thash(cd.dead());
}
