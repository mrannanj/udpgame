#include "common/world/components/physics.h"
#include "common/util/hash.h"

void Physics::update_bb()
{
	bb.max = position + half_dim;
	bb.min = position - half_dim;
}

EntityId Physics::eid() const
{
	return entityid;
}

glm::vec3 Physics::eye_position() const
{
	glm::vec3 eye_pos(position);
	eye_pos.y += 0.7f;
	return eye_pos;
}

glm::vec3 Physics::look_direction() const
{
	return glm::vec3(cos(vertical_angle) * sin(horizontal_angle),
			 sin(vertical_angle),
			 cos(vertical_angle) * cos(horizontal_angle));
}

Physics::Physics():
	entityid(0),
	position(0.0f, 0.0f, 0.0f),
	velocity(0.0f, 0.0f, 0.0f),
	half_dim(0.0f, 0.0f, 0.0f),
	horizontal_angle(0.0f),
	vertical_angle(0.0f),
	on_ground(false),
	bb()
{
	update_bb();
}
