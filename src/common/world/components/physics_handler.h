#pragma once

#include "common/world/components/world_handler.h"
#include "common/world/components/physics.h"
#include "common/world/entity_id.h"
#include "common/proto/udpgame.pb.h"

#include <vector>
#include <set>
#include <glm/glm.hpp>

#define FRICTION 0.8f
#define GRAVITY 10.0f

class World;

class PhysicsHandler : public WorldHandler<PhysicsC> {
public:
  void tick(float, World&);

  void getObjects(WorldState&) const;
  void setObjects(const WorldState&);
};
