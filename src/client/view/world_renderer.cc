#include "client/view/world_renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

        if (block == 1)
          r.cube_renderer.SetTexture(r.texture_manager[Texture::GRASS]);
        if (block == 2)
          r.cube_renderer.SetTexture(r.texture_manager[Texture::FACE]);
        if (block == 3)
          r.cube_renderer.SetTexture(r.texture_manager[Texture::FONT]);

        glm::mat4 model = glm::translate(glm::mat4(1.0f),
          glm::vec3((float)x + 0.5f, (float)y + 0.5f, (float)z + 0.5f)
        );
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        r.cube_renderer.DrawCube(vp * model);
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
  r.cube_renderer.SetTexture(r.texture_manager[Texture::HEAD]);

  for (const PhysicsC& p : ps.components()) {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), p.position);
    model = glm::rotate(model, rad_to_degree(p.horizontal_angle),
      glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, p.dimensions);
    r.cube_renderer.DrawCube(vp * model);
  }
}
