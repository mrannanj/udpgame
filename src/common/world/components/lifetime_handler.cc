#include "common/world/components/lifetime_handler.h"
#include "common/world/world.h"

void LifetimeHandler::tick(float dt, World& w) {
  for (Lifetime &l : mComponents) {
    l.set_ttl(l.ttl()-dt);
    if (l.ttl() < 0.0f)
      w.mDeleteList.insert(l.eid());
  }
}
