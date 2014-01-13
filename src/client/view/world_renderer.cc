#include "client/view/world_renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>

#include "common/world/world.h"
#include "common/world/components/inventory.h"

void draw_grid(const Renderer& r, const GridHandler& g, const glm::mat4& vp,
    const glm::vec3& center) {
  r.cube_renderer.On();

  int ind[3][2];
  g.range_indices(center, ind);
  for (int x = ind[0][0]; x <= ind[0][1]; ++x) {
    for (int y = ind[1][0]; y <= ind[1][1]; ++y) {
      for (int z = ind[2][0]; z <= ind[2][1]; ++z) {
        char block = g.mArr.get(x,y,z);
        if (block == 0) continue;
        r.cube_renderer.SetTexture(r.texture_manager[block]);

        glm::mat4 model = glm::translate(glm::mat4(1.0f),
          glm::vec3((float)x + 0.5f, (float)y + 0.5f, (float)z + 0.5f)
        );
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        r.cube_renderer.DrawCube(vp, model);
      }
    }
  }
}

float rad_to_degree(float r) {
  constexpr float rad_in_degrees = (180.0f/(float)M_PI);
  return rad_in_degrees * r;
}

void draw_units(const Renderer& r, const PhysicsHandler& ps,
    const glm::mat4& vp)
{
  r.cube_renderer.On();

  for (const Physics& p : ps.components()) {
    r.cube_renderer.SetTexture(r.texture_manager[p.type]);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), p.position);
    model = glm::rotate(model, rad_to_degree(p.horizontal_angle),
      glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, p.half_dim);
    r.cube_renderer.DrawCube(vp, model);
  }
}

void draw_crosshair(const Renderer& r) {
  float q[] = {
    -0.005f, -0.005f, 0.005f, 0.005f,
    -0.005f, 0.005f, 0.005f, -0.005f
  };
  r.quad_renderer.On();
  set_color(r.quad_renderer.color_uni(), Blue, 1.0f);
  r.quad_renderer.draw_quad(q);
}

void draw_position(const Renderer& r, Perspective& p) {
  r.text_renderer.On();
  r.text_renderer.DrawText(-1.0f, -0.9f, 0.1f, p.pos_string(), Green);
}

void draw_inventory(const Renderer& r, World& w, EntityId id) {
  Inventory* inv = w.inventory().get(id);
  if (!inv) return;
  std::stringstream ss;
  ss << "w:" << inv->wielding;
  for (const auto& p : inv->itemCount) {
    ss << "," << p.first << ":" << p.second;
  }
  r.text_renderer.On();
  r.text_renderer.DrawText(-1.0f, 1.0f, 0.08f, ss.str(), Blue);
}

void draw_hud(const Renderer& r, World& w, EntityId id, Perspective& p) {
  draw_crosshair(r);
  draw_position(r, p);
  draw_inventory(r, w, id);
}
