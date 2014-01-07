#pragma once

#include "common/world/components/grid_handler.h"
#include "common/world/components/physics_handler.h"
#include "client/view/renderer.h"

void draw_grid(const Renderer&, const GridHandler&, const glm::mat4&,
    const glm::vec3&);
void draw_units(const Renderer&, const PhysicsHandler&, const glm::mat4&);
