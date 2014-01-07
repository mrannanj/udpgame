#pragma once

#include <map>
#include <set>
#include <vector>

#include "common/world/components/inputc.h"
#include "common/world/components/physics_handler.h"
#include "common/world/components/input_handler.h"
#include "common/world/components/grid_handler.h"
#include "common/world/components/inventory_handler.h"
#include "common/world/components/client_handler.h"
#include "common/world/id_generator.h"
#include "common/proto/udpgame.pb.h"

const glm::vec3 spawn_position(5.0f, 8.0f, 5.0f);

class World {
public:
  World();

  int tick(float, const std::vector<InputC>&);
  void spawn_player(int);
  void spawn_monster();

  void removeDead();
  void defaultWorld();
  void connected(int);
  void disconnected(int);

  WorldState getState();
  void setState(const WorldState&);
  InitialState getInitialState();
  void setInitialState(const InitialState&);

  bool mInit;
  unsigned mTickNumber;

  InputHandler& input();
  PhysicsHandler& physics();
  GridHandler& grid();
  InventoryHandler& inventory();
  ClientHandler& client();

  std::set<EntityId> mDeleteList;

private:
  IdGenerator m_idgen;
  InputHandler mInputHandler;
  PhysicsHandler mPhysicsHandler;
  InventoryHandler mInventory;
  ClientHandler mClient;
  GridHandler mGrid;
};
