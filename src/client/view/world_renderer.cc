#include "client/view/world_renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void draw_grid(const Renderer& r, const Grid& g, const glm::mat4& vp)
{
  r.cube_renderer.On();
  r.cube_renderer.SetTexture(r.texture_manager[Texture::GRASS]);

  for (unsigned x = 0; x < GRID_SIZE_X; ++x) {
    for (unsigned y = 0; y < GRID_SIZE_Y; ++y) {
      for (unsigned z = 0; z < GRID_SIZE_Z; ++z) {
        char block = g.m_grid[x][y][z];
        if (block)
        {
          glm::mat4 model = glm::translate(glm::mat4(1.0f),
            glm::vec3((float)x + 0.5f, (float)y + 0.5f, (float)z + 0.5f)
          );
          model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
          r.cube_renderer.DrawCube(vp * model);
        }
      }
    }
  }
}

float rad_to_degree(float r)
{
  static float rad_in_degrees = (180.0f/(float)M_PI);
  return rad_in_degrees * r;
}

void draw_units(const Renderer& r, const PhysicsSystem& ps, const glm::mat4& vp)
{
  r.cube_renderer.On();
  r.cube_renderer.SetTexture(r.texture_manager[Texture::HEAD]);

  for (const PhysicsC& p : ps.physics_components())
  {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), p.position);
    model = glm::rotate(model, rad_to_degree(p.horizontal_angle),
      glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, p.dimensions);
    r.cube_renderer.DrawCube(vp * model);
  }
}

