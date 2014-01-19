#include "common/world/components/health_handler.h"
#include "common/world/world.h"

void HealthHandler::tick(float, World& w) {
  for (Health& h : mComponents) {
    if (h.cur_hp() <= 0)
      w.mDeleteList.insert(h.eid());
  }
}
