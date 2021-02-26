#include "client/view/world_renderer.h"

#include "common/include/glm.h"
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>
#include <algorithm>
#include <iostream>

#include "common/world/world.h"
#include "common/world/components/inventory.h"

void draw_grid(const Renderer& r, World& w, const glm::mat4& v,
	       const glm::mat4& p, const glm::vec3& center)
{
	r.cube_renderer.On();

	GridHandler& g = w.grid();
	LightHandler& l = w.light();

	constexpr size_t max_lights = 10;
	size_t size = std::min(l.components().size(), (size_t) max_lights);
	glUniform1i(r.cube_renderer.activeLights(), size);
	GLfloat light_pos[max_lights][3];
	for (size_t i = 0; i < size; ++i) {
		const Light & lc = l.components().at(i);
		Physics *p = w.physics().get(lc.eid());
		assert(p);
		light_pos[i][0] = p->position[0];
		light_pos[i][1] = p->position[1];
		light_pos[i][2] = p->position[2];
	}
	glUniform3fv(r.cube_renderer.lightPositions(), size,
		     (float*)&light_pos[0]);

    int ind[3][2];
    g.range_indices(center, ind);
    for (int x = ind[0][0]; x <= ind[0][1]; ++x) {
	for (int y = ind[1][0]; y <= ind[1][1]; ++y) {
	    for (int z = ind[2][0]; z <= ind[2][1]; ++z) {
		char block = g.mArr.get(x, y, z);
		if (block == 0)
		    continue;
		r.cube_renderer.SetTexture(r.texture_manager[block]);

		glm::mat4 model = glm::translate(glm::mat4(1.0f),
						 glm::vec3((float) x + 0.5f,
							   (float) y + 0.5f,
							   (float) z + 0.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		r.cube_renderer.DrawCube(model, v, p);
	    }
	}
    }
}

float rad_to_degree(float r)
{
	constexpr float rad_in_degrees = (180.0f / (float) M_PI);
	return rad_in_degrees * r;
}

void draw_units(const Renderer& r, const PhysicsHandler& ps,
		const glm::mat4& v, const glm::mat4& p)
{
	r.cube_renderer.On();

	for (const Physics & pc:ps.components()) {
		r.cube_renderer.SetTexture(r.texture_manager[pc.type]);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), pc.position);
		model = glm::rotate(model, pc.horizontal_angle,
				    glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, pc.half_dim);
		r.cube_renderer.DrawCube(model, v, p);
	}
}

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

void draw_inventory(const Renderer& r, World& w, EntityId id)
{
	Inventory *inv = w.inventory().get(id);
	if (!inv)
		return;
	std::stringstream ss;
	ss << "w:" << inv->wielding;
	for (const auto & p : inv->itemCount) {
		ss << "," << p.first << ":" << p.second;
	}
	r.text_renderer.On();
	r.text_renderer.DrawText(-1.0f, 1.0f, 0.08f, ss.str(), Blue);
}

void draw_hud(const Renderer& r, World& w, EntityId id, Perspective& p)
{
	draw_crosshair(r);
	draw_position(r, p);
	draw_inventory(r, w, id);
}
