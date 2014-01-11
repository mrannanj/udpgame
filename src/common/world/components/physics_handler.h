#pragma once

#include "common/world/components/world_handler.h"
#include "common/world/components/physics.h"
#include "common/world/entity_id.h"
#include "common/proto/udpgame.pb.h"

#include <vector>
#include <set>
#include <glm/glm.hpp>

class World;

class PhysicsHandler : public WorldHandler<PhysicsC, PhysicsData> {
public:
  void tick(float, World&);
  unsigned hash();
private:
  void handleInput(PhysicsC& p, World& w);
};
