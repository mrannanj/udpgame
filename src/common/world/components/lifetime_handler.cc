#include "common/world/components/lifetime_handler.h"
#include "common/world/world.h"

void LifetimeHandler::tick(float dt, World& w) {
  for (Lifetime &l : mComponents) {
    l.set_ttl(l.ttl()-dt);
    if (l.ttl() < 0.0f)
      w.mDeleteList.insert(l.eid());
  }
}

void LifetimeHandler::serialize(
    google::protobuf::RepeatedPtrField<Lifetime>* ls)
{
  for (const Lifetime& l : mComponents)
    ls->Add()->CopyFrom(l);
}

void LifetimeHandler::deserialize(
    const google::protobuf::RepeatedPtrField<Lifetime>& ls)
{
  mComponents.clear();
  for (const Lifetime& l : ls)
    mComponents.push_back(l);
}
