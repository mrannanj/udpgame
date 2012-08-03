#ifndef COMMON_WORLD_WORLD_H
#define COMMON_WORLD_WORLD_H

#include <map>
#include "common/google.h"
#include "common/world/entity.h"
#include "common/world/entity_id.h"
#include "common/world/id_generator.h"

class World {
public:
  World();
  void Init();

  EntityId SpawnEntity();
  void SetEntityInput(EntityId);
  void Tick(Real);

  const std::map<EntityId, Entity>& entities() const;

private:
  DISALLOW_COPY_AND_ASSIGN(World);

  IdGenerator idgen_;
  std::map<EntityId, Entity> entities_;
};

#endif

