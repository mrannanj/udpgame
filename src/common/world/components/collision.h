#include "common/world/components/AABB.h"

bool AABBvsAABB(const AABB&, const AABB&);
float AABBvsAABB_overlap(const AABB&, const AABB&, unsigned&);
bool AABBvsRay(const AABB&, const glm::vec3&, const glm::vec3&,
	       float&, int&, int&);
