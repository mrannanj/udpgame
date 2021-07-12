#include "client/view/world_renderer.h"

#include "common/include/glm.h"
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>
#include <algorithm>
#include <iostream>

#include "common/world/world.h"
#include "common/world/components/inventory.h"

void draw_crosshair(const Renderer& r)
{
	float q[] = {
		-0.005f, -0.005f, 0.005f, 0.005f,
		-0.005f, 0.005f, 0.005f, -0.005f
	};
	r.quad_renderer.On();
	set_color(r.quad_renderer.color_uni(), Blue, 1.0f);
	r.quad_renderer.draw_quad(q);
}

void draw_position(const Renderer& r, Perspective& p)
{
	r.text_renderer.On();
	r.text_renderer.DrawText(-1.0f, -0.9f, 0.1f, p.pos_string(), Green);
}
