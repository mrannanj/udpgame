#pragma once

#include "common/include/glm.h"

#include "common/world/components/AABB.h"
#include "common/world/entity_id.h"
#include "common/proto/udpgame.pb.h"
#include "common/util/hash.h"

struct Physics {
	Physics();
	Physics(const PhysicsData&);
	operator PhysicsData() const;

	EntityId entityid;
	ObjectType type;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 half_dim;
	float horizontal_angle;
	float vertical_angle;
	bool on_ground;

	// this is calculated, no need to serialize
	AABB bb;

	void update_bb();

	EntityId eid() const;
	glm::vec3 eye_position() const;
	glm::vec3 look_direction() const;
};

template <> uint32_t inline thash<Physics> (const Physics& p) {
	return thash(p.entityid)
	       ^ thash(p.type)
	       ^ thash(p.position)
	       ^ thash(p.velocity)
	       ^ thash(p.half_dim)
	       ^ thash(p.horizontal_angle)
	       ^ thash(p.vertical_angle)
	       ^ thash(p.on_ground);
}
