#include "common/world/components/client_handler.h"
#include "common/world/world.h"

#include <algorithm>

using namespace std;

void ClientHandler::tick(float, World& w) {
  for (auto it = mComponents.begin(); it != mComponents.end();) {
    ClientData& c = *it;
    if (!c.connected) {
      w.mDeleteList.insert(c.id);
      it = mComponents.erase(it);
      continue;
    }

    InputC* ic = w.input().getByClient(c.client);
    if (ic != nullptr) {
      ic->id = c.id;
      if (ic->actions & ContinousAction::SPAWN_MONSTER)
        w.spawn_monster();
      if (ic->actions & ContinousAction::PLAYER_MODE)
        c.mode = (c.mode == OBSERVER_MODE ? PLAYER_MODE : OBSERVER_MODE);
    }

    if (c.mode == PLAYER_MODE and c.dead) {
      w.spawn_player(c.client);
    } else if (c.mode == OBSERVER_MODE and !c.dead) {
      w.mDeleteList.insert(c.id);
    }
    ++it;
  }
}

void ClientHandler::handleDead(const std::set<EntityId>& ids) {
  for (EntityId eid : ids)
    markDead(eid);
}

void ClientHandler::markDead(EntityId eid) {
  auto r = find_if(mComponents.begin(), mComponents.end(),
      [&](ClientData& c) { return c.id == eid; });
  if (r != mComponents.end())
    r->dead = true;
}

ClientData* ClientHandler::getByClient(int cid) {
  for (ClientData& c : mComponents)
    if (c.client == cid)
      return &c;
  return nullptr;
}

void ClientHandler::removeByClient(int cid) {
  mComponents.erase(std::remove_if(std::begin(mComponents),
    std::end(mComponents), [&](ClientData& c) { return c.client == cid; }),
    std::end(mComponents));
}

void ClientHandler::remove(EntityId) {}
