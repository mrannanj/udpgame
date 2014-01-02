#pragma once

#include <map>
#include <set>
#include <vector>
#include "common/world/components/inputc.h"
#include "common/world/components/physics_system.h"
#include "common/world/id_generator.h"
#include "common/proto/udpgame.pb.h"

class World {
public:
  World();

  int tick(float, const std::vector<InputC>&);
  EntityId spawn_entity(int);
  WorldState getState();
  void setInputs(const std::vector<InputC>&);
  void setState(const WorldState&);
  void removeDead();
  void defaultWorld();

  bool mInit;
  unsigned mTickNumber;
  std::map<int, EntityId> mClient2Entity;
private:
  IdGenerator m_idgen;
  std::set<EntityId> mDeleteList;
};
