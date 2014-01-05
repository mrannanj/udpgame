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

class PhysicsHandler : public WorldHandler {
public:
  void* get(EntityId);
  void add(void*);
  void tick(float, World&);

  void remove(EntityId);
  const std::vector<PhysicsC>& physics_components() const;
  std::set<EntityId> mRemoveList;

  void getObjects(WorldState&) const;
  void setObjects(const WorldState&);
private:
  std::vector<PhysicsC> m_physics_components;
};
