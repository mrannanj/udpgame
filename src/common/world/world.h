#pragma once

#include <map>
#include <set>
#include <vector>

#include "common/world/components/physics_handler.h"
#include "common/world/components/input_handler.h"
#include "common/world/components/grid_handler.h"
#include "common/world/components/inventory_handler.h"
#include "common/world/components/client_handler.h"
#include "common/world/components/lifetime_handler.h"
#include "common/world/components/id_generator.h"
#include "common/proto/udpgame.pb.h"

class World {
public:
  World(bool);

  void tick(const FrameInputs&);
  void spawn_player(int);
  void throw_object(const Physics&, ObjectType);
  void onBlockDestruction(int, int, int);

  void removeDead();

  InitialState getInitialState();
  void setInitialState(const InitialState&);

  unsigned hash() const;

  bool mInit;
  unsigned mTickNumber;

  InputHandler& input();
  PhysicsHandler& physics();
  GridHandler& grid();
  InventoryHandler& inventory();
  ClientHandler& client();

  std::set<EntityId> mDeleteList;

private:
  void updateHash();

  unsigned mHash;

  IdGenerator m_idgen;
  InputHandler mInputHandler;
  PhysicsHandler mPhysicsHandler;
  InventoryHandler mInventory;
  ClientHandler mClient;
  GridHandler mGrid;
  LifetimeHandler mLifetime;
};
