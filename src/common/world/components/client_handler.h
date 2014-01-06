#pragma once

#include "common/world/components/world_handler.h"
#include "common/world/components/client_data.h"

class ClientHandler : public WorldHandler<ClientData> {
public:
  void tick(float, World&);
  void handleDead(const std::set<EntityId>&);
  void markDead(EntityId);
  void remove(EntityId);
  ClientData* getByClient(int);
};

