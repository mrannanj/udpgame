#pragma once

#include "common/world/entity_id.h"

#include <algorithm>
#include <vector>
#include <set>

class World;

template<typename T> class WorldHandler {
public:
  T* get(EntityId);
  void add(const T&);
  void remove(EntityId);
  void removeComponents(const std::set<EntityId>&);

  virtual void tick(float, World&);
  virtual ~WorldHandler();

  const std::vector<T>& components() const;

protected:
  std::vector<T> mComponents;
};

template<typename T>
void WorldHandler<T>::removeComponents(const std::set<EntityId>& r) {
  for (EntityId id : r) remove(id);
}

template<typename T>
void WorldHandler<T>::tick(float, World&) {
}

template<typename T>
T* WorldHandler<T>::get(EntityId eid) {
  for (T& c : mComponents)
    if (c.id == eid)
      return &c;
  return nullptr;
}

template<typename T>
void WorldHandler<T>::add(const T& c) {
  mComponents.push_back(c);
}

template<typename T>
WorldHandler<T>::~WorldHandler() {
}

template<typename T>
const std::vector<T>& WorldHandler<T>::components() const {
  return mComponents;
}

template<typename T>
void WorldHandler<T>::remove(EntityId eid) {
  mComponents.erase(std::remove_if(std::begin(mComponents),
    std::end(mComponents), [&](T& c) { return c.id == eid; }),
    std::end(mComponents));
}
