#include "common/world/components/physics_handler.h"
#include "common/world/components/grid_handler.h"
#include "common/world/components/collision.h"
#include "common/world/world.h"
#include "client/controller/input/input.h"

#include <iostream>
#include <cassert>
#include <algorithm>
#include <cstdio>

constexpr float HALF_PI = (float)M_PI / 2.0f;
constexpr float move_speed = 1.5f;
constexpr float jump_velocity = 5.0f;
constexpr float FRICTION = 0.85f;
constexpr float GRAVITY = 10.0f;

using namespace std;

void PhysicsHandler::tick(float dt, World& w)
{
	for (Physics& p : mComponents) {
		handleInput(p, w);

		p.velocity.y -= GRAVITY * dt;
		p.velocity.x *= FRICTION;
		p.velocity.z *= FRICTION;
		if (!w.grid().check_collision(p, dt))
			w.mDeleteList.insert(p.eid());
	}
}

void PhysicsHandler::handleInput(Physics& p, World& w)
{
	FrameInput *i = w.input().get(p.eid());
	if (!i)
		return;

	p.horizontal_angle -= i->horizontal_delta();
	p.vertical_angle -= i->vertical_delta();
	if (p.vertical_angle < -HALF_PI)
		p.vertical_angle = -HALF_PI;
	else if (p.vertical_angle > HALF_PI)
		p.vertical_angle = HALF_PI;

	glm::vec3 forward = glm::vec3(sin(p.horizontal_angle), 0.0f,
				      cos(p.horizontal_angle));

	glm::vec3 right = glm::vec3(sin(p.horizontal_angle - HALF_PI), 0.0f,
				    cos(p.horizontal_angle - HALF_PI));

	if (i->actions() & ContinousAction::MOVE_FORWARD)
		p.velocity += forward * move_speed;
	else if (i->actions() & ContinousAction::MOVE_BACK)
		p.velocity -= forward * move_speed;
	if (i->actions() & ContinousAction::MOVE_RIGHT)
		p.velocity += right * move_speed;
	else if (i->actions() & ContinousAction::MOVE_LEFT)
		p.velocity -= right * move_speed;

	if (i->actions() & ContinousAction::JUMP && p.on_ground) {
		p.velocity.y += jump_velocity;
		p.on_ground = false;
	}
}

bool PhysicsHandler::canPlaceBlock(int f[3])
{
	AABB a(f[0], f[1], f[2]);
	for (Physics& p : mComponents)
		if (AABBvsAABB(a, p.bb))
			return false;
	return true;
}
