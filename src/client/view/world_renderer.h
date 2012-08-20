#ifndef CLIENT_CONTROLLER_VIEW_WORLD_RENDERER_H
#define CLIENT_CONTROLLER_VIEW_WORLD_RENDERER_H

#include "common/world/components/grid.h"
#include "common/world/components/physics_system.h"
#include "client/view/renderer.h"

void draw_grid(const Renderer&, const Grid&, const glm::mat4&);
void draw_units(const Renderer&, const PhysicsSystem&, const glm::mat4&);

#endif


