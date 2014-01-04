#pragma once

#include "common/world/components/grid.h"
#include "common/world/components/physics_handler.h"
#include "client/view/renderer.h"

void draw_grid(const Renderer&, const Grid&, const glm::mat4&);
void draw_units(const Renderer&, const PhysicsHandler&, const glm::mat4&);
