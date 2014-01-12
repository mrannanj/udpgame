#pragma once

#include "common/world/entity_id.h"
#include "common/proto/udpgame.pb.h"

#include <algorithm>
#include <vector>
#include <set>

class World;

template<typename T, typename D> class WorldHandler {
public:
  WorldHandler();

  T* get(EntityId);
  void add(const T&);
  virtual void remove(EntityId);
  virtual void handleDead(const std::set<EntityId>&);

  virtual void tick(float, World&);
  virtual ~WorldHandler();

  void serialize(google::protobuf::RepeatedPtrField<D>*) const;
  void deserialize(const google::protobuf::RepeatedPtrField<D>&);

  const std::vector<T>& components() const;

protected:
  std::vector<T> mComponents;
};

template<typename T, typename D>
WorldHandler<T,D>::WorldHandler():
  mComponents()
{
}

template<typename T, typename D>
void WorldHandler<T,D>::handleDead(const std::set<EntityId>& r) {
  for (EntityId id : r) remove(id);
}

template<typename T, typename D>
void WorldHandler<T,D>::tick(float, World&) {
}

template<typename T, typename D>
T* WorldHandler<T,D>::get(EntityId eid) {
  for (T& c : mComponents)
    if (c.eid() == eid)
      return &c;
  return nullptr;
}

template<typename T, typename D>
void WorldHandler<T,D>::add(const T& c) {
  mComponents.push_back(c);
}

template<typename T, typename D>
WorldHandler<T,D>::~WorldHandler() {
}

template<typename T, typename D>
const std::vector<T>& WorldHandler<T,D>::components() const {
  return mComponents;
}

template<typename T, typename D>
void WorldHandler<T,D>::remove(EntityId eid) {
  mComponents.erase(std::remove_if(std::begin(mComponents),
    std::end(mComponents), [&](T& c) { return c.eid() == eid; }),
    std::end(mComponents));
}

template<typename T, typename D>
void WorldHandler<T,D>::serialize(
    google::protobuf::RepeatedPtrField<D>* ls) const
{
  for (const T& l : mComponents)
    ls->Add()->CopyFrom(l);
}

template<typename T, typename D>
void WorldHandler<T,D>::deserialize(
    const google::protobuf::RepeatedPtrField<D>& ls)
{
  mComponents.clear();
  for (const D& l : ls)
    mComponents.push_back(l);
}
