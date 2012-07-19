
#include <SDL.h>
#include <GL/glew.h>
#include <stdlib.h>
#include <string.h>

#include "common/world/world.h"

World::World() {
}

void World::Init() {
}

EntityId World::SpawnEntity() {
  EntityId id = idgen_.NextId();
  entities_[id] = Entity();
  return id;
}

void World::SetEntityInput(EntityId id, Actions& a) {
  Entity& e = entities_[id];
  memcpy(&e.actions_, &a, sizeof(a));
}

void World::Tick(Real dt) {
  for (auto it = entities_.begin(); it != entities_.end(); ++it) {
    it->second.Tick(dt);
  }
}

const std::map<EntityId, Entity>& World::entities() const {
  return entities_;
}
