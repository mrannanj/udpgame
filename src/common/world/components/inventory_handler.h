#pragma once

#include "common/world/components/world_handler.h"
#include "common/world/components/inventory.h"

struct InventoryHandler : public WorldHandler<Inventory> {
  void tick(float, World&);
};
