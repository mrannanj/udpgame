#pragma once

#include "client/controller/perspective.h"
#include "common/world/components/grid_handler.h"
#include "common/world/components/physics_handler.h"
#include "client/view/renderer.h"

void draw_grid(const Renderer&, World&, const glm::mat4&, const glm::mat4&,
	       const glm::vec3&);
void draw_units(const Renderer&, const PhysicsHandler&, const glm::mat4&,
	        const glm::mat4&);
void draw_hud(const Renderer&, World&, EntityId, Perspective&);
