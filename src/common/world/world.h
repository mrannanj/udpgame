#pragma once

#include <map>
#include <set>
#include "common/world/components/physics_system.h"
#include "common/world/id_generator.h"
#include "common/proto/udpgame.pb.h"

class World {
public:
  World();

  void tick(float, const ClientInput&);
  void spawn_entity();
  WorldState getState();
  void setInput(const ClientInput&);
  void setState(const WorldState&);
  void handleAMessage(const AMessage&);
  void removeDead();
  void defaultWorld();

private:
  IdGenerator m_idgen;
  std::set<EntityId> mDeleteList;
};
