#include "common/proto/udpgame.pb.h"
#include "common/world/components/damage_handler.h"
#include "common/world/components/physics.h"
#include "common/world/components/collision.h"
#include "common/world/world.h"

void DamageHandler::tick(float, World& w) {
  for (size_t i = 0; i < mComponents.size(); ++i) {
    EntityId eid1 = mComponents[i].eid();
    Damage& d = mComponents[i];
    Physics* p1 = w.physics().get(eid1);
    if (!p1) continue;

    for (size_t j = 0; j < w.health().components().size(); ++ j) {
      Health& h = w.health().components()[j];
      EntityId eid2 = mComponents[i].eid();
      if (eid1 == eid2) continue;

      Physics* p2 = w.physics().get(eid2);
      if (!p2) continue;
      if (!AABBvsAABB(p1->bb, p2->bb)) continue;
      h.set_cur_hp(h.cur_hp() - d.damage());
    }
  }
}
