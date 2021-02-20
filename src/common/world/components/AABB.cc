#include "common/world/components/AABB.h"

static constexpr float BLOCK_SIZE = 1.0f;

AABB::AABB():
  min(),
  max()
{
}

AABB::AABB(int x, int y, int z):
  min((float)x, (float)y, (float)z),
  max(min + BLOCK_SIZE)
{
}

AABB::AABB(const glm::vec3& pmin, const glm::vec3& pmax):
  min(pmin),
  max(pmax)
{
}
