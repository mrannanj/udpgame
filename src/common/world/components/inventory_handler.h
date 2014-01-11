#pragma once

#include "common/world/components/world_handler.h"
#include "common/world/components/inventory.h"
#include "common/proto/udpgame.pb.h"

class InventoryHandler : public WorldHandler<Inventory, InventoryData> {
public:
  void tick(float, World&);
private:
  void pickupItems(World&);
};
