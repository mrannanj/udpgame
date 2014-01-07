#include "common/world/components/inventory_handler.h"
#include "common/world/world.h"
#include "client/controller/input/input.h"

using google::protobuf::RepeatedPtrField;

void InventoryHandler::tick(float, World& w) {
  for (Inventory& inv : mComponents) {
    FrameInput* ic = w.input().get(inv.eid());
    if (ic == nullptr) continue;

    if (ic->actions() & ContinousAction::ITEM_1)
      inv.set_wielding(1);
    if (ic->actions() & ContinousAction::ITEM_2)
      inv.set_wielding(2);
    if (ic->actions() & ContinousAction::ITEM_3)
      inv.set_wielding(3);

    PhysicsC* p = w.physics().get(inv.eid());
    assert(p != nullptr);

    if ((ic->actions() & ContinousAction::FIRST) or
        ic->actions() & ContinousAction::SECOND)
    {
      glm::vec3 pos = p->eye_position();
      glm::vec3 dir = p->look_direction();
      float distance;
      char* hitBlock;
      char* faceBlock;
      if (w.grid().raycast(pos, dir, distance, &hitBlock, &faceBlock)) {
        if (ic->actions() & ContinousAction::FIRST and *hitBlock != 3) {
          *hitBlock = 0;
        }
        if (ic->actions() & ContinousAction::SECOND and faceBlock != nullptr) {
          *faceBlock = inv.wielding();
        }
      }
    }
  }
}

void InventoryHandler::serialize(
    google::protobuf::RepeatedPtrField<Inventory>* invs)
{
  for (const Inventory& i : mComponents)
    invs->Add()->CopyFrom(i);
}

void InventoryHandler::deserialize(
    const google::protobuf::RepeatedPtrField<Inventory>& invs)
{
  mComponents.clear();
  for (const Inventory& i : invs)
    mComponents.push_back(i);
}
