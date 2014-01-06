#include "common/world/components/inventory_handler.h"
#include "common/world/components/inputc.h"
#include "common/world/world.h"

void InventoryHandler::tick(float, World& w) {
  for (Inventory& inv : mComponents) {
    InputC* ic = w.input().get(inv.id);
    if (ic == nullptr) continue;

    if (ic->actions & ContinousAction::ITEM_1)
      inv.mWielding = 1;
    if (ic->actions & ContinousAction::ITEM_2)
      inv.mWielding = 2;
    if (ic->actions & ContinousAction::ITEM_3)
      inv.mWielding = 3;

    PhysicsC* p = w.physics().get(inv.id);
    assert(p != nullptr);

    if ((ic->actions & ContinousAction::FIRST) or
        ic->actions & ContinousAction::SECOND)
    {
      glm::vec3 pos = p->eye_position();
      glm::vec3 dir = p->look_direction();
      float distance;
      char* hitBlock;
      char* faceBlock;
      if (w.grid().raycast(pos, dir, distance, &hitBlock, &faceBlock)) {
        if (ic->actions & ContinousAction::FIRST and *hitBlock != 3) {
          *hitBlock = 0;
        }
        if (ic->actions & ContinousAction::SECOND and faceBlock != nullptr) {
          *faceBlock = inv.mWielding;
        }
      }
    }
  }
}
