#include "common/world/components/inventory_handler.h"
#include "common/world/components/collision.h"
#include "common/world/world.h"
#include "client/controller/input/input.h"

using google::protobuf::RepeatedPtrField;

void InventoryHandler::tick(float, World& w) {
  for (Inventory& inv : mComponents) {
    FrameInput* ic = w.input().get(inv.eid());
    if (ic == nullptr) continue;

    if (ic->actions() & ContinousAction::ITEM_1)
      inv.wielding = ObjectType::GRASS;
    if (ic->actions() & ContinousAction::ITEM_2)
      inv.wielding = ObjectType::SAND;
    if (ic->actions() & ContinousAction::ITEM_3)
      inv.wielding = ObjectType::ROCK;
    if (ic->actions() & ContinousAction::ITEM_4)
      inv.wielding = ObjectType::BW;
    if (ic->actions() & ContinousAction::ITEM_5)
      inv.wielding = ObjectType::FONT;
#if 0
    if (ic->actions() & ContinousAction::ITEM_6)
      inv.set_wielding(6);
    if (ic->actions() & ContinousAction::ITEM_7)
      inv.set_wielding(3);
    if (ic->actions() & ContinousAction::ITEM_8)
      inv.set_wielding(3);
    if (ic->actions() & ContinousAction::ITEM_9)
      inv.set_wielding(3);
#endif

    PhysicsC* p = w.physics().get(inv.eid());
    assert(p != nullptr);

    if (ic->actions() & ContinousAction::THROW) {
      if (inv.itemCount[inv.wielding] > 0) {
        w.throw_object(*p, inv.wielding);
        inv.itemCount[inv.wielding] -= 1;
      }
    }

    if ((ic->actions() & ContinousAction::FIRST) or
        ic->actions() & ContinousAction::SECOND)
    {
      glm::vec3 pos = p->eye_position();
      glm::vec3 dir = p->look_direction();
      float distance;
      char* hitBlock;
      char* faceBlock;
      int b[3];
      if (w.grid().raycast(pos, dir, distance, &hitBlock, &faceBlock, b)) {
        if (ic->actions() & ContinousAction::FIRST and *hitBlock != 5) {
          w.onBlockDestruction(b[0], b[1], b[2]);
        }
        if (ic->actions() & ContinousAction::SECOND and faceBlock != nullptr) {
          if (inv.itemCount[inv.wielding] > 0) {
            *faceBlock = inv.wielding;
            inv.itemCount[inv.wielding] -= 1;
          }
        }
      }
    }
  }
  pickupItems(w);
}

void InventoryHandler::pickupItems(World& w) {
  for (size_t i = 0; i < mComponents.size(); ++i) {
    EntityId eid = mComponents[i].eid();
    PhysicsC* p1 = w.physics().get(eid);
    Inventory& inv = mComponents[i];
    if (!p1) continue;
    for (size_t j = 0; j < w.physics().components().size(); ++ j) {
      const PhysicsC& p2 = w.physics().components()[j];
      if (eid == p2.entityid) continue;
      if (get(p2.entityid)) continue;
      if (!AABBvsAABB(p1->bb, p2.bb)) continue;
      w.mDeleteList.insert(p2.entityid);
      inv.itemCount[p2.type] += 1;
    }
  }
}
