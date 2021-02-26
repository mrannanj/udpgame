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
	type(ObjectType::NONE),
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

Physics::Physics(const PhysicsData& pd):
	entityid(pd.eid()),
	type(pd.type()),
	position(pd.pos().x(), pd.pos().y(), pd.pos().z()),
	velocity(pd.vel().x(), pd.vel().y(), pd.vel().z()),
	half_dim(pd.half_dim().x(), pd.half_dim().y(), pd.half_dim().z()),
	horizontal_angle(pd.horizontal_angle()),
	vertical_angle(pd.vertical_angle()),
	on_ground(pd.on_ground()),
	bb()
{
	update_bb();
}

Physics::operator PhysicsData() const
{
	PhysicsData pd;
	pd.set_eid(entityid);
	pd.set_type(type);
	pd.mutable_pos()->set_x(position.x);
	pd.mutable_pos()->set_y(position.y);
	pd.mutable_pos()->set_z(position.z);
	pd.mutable_vel()->set_x(velocity.x);
	pd.mutable_vel()->set_y(velocity.y);
	pd.mutable_vel()->set_z(velocity.z);
	pd.mutable_half_dim()->set_x(half_dim.x);
	pd.mutable_half_dim()->set_y(half_dim.y);
	pd.mutable_half_dim()->set_z(half_dim.z);
	pd.set_horizontal_angle(horizontal_angle);
	pd.set_vertical_angle(vertical_angle);
	pd.set_on_ground(on_ground);
	return pd;
}
