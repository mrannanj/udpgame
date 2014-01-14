#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "client/view/cube_renderer.h"

float cube_vertices[] = {
  -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
   1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
   1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
   1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
  -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
  -1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,

  -1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
   1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
   1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
   1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  -1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

  -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
  -1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
  -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
  -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
  -1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
  -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

   1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
   1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
   1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
   1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
   1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
   1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

  -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
   1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
   1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
   1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
  -1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
  -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

  -1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
   1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
   1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
   1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
  -1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
  -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f
};

CubeRenderer::CubeRenderer(const ResourceLocator& rl):
  Shader(rl, "resources/shaders/cube.vert", "resources/shaders/cube.frag"),
  m_p_uniform(0),
  m_v_uniform(0),
  m_m_uniform(0),
  m_texture_uniform(0),
  m_light_positions(0),
  m_active_lights(0)
{
  Init();
}

void CubeRenderer::Init() {
  size_t vertex_element_size = 11 * sizeof(float);
  glUseProgram(shader_program);
  glBindFragDataLocation(shader_program, 0, "frag_color");

  GLint position = glGetAttribLocation(shader_program, "position_modelspace_");
  glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, vertex_element_size, 0);
  glEnableVertexAttribArray(position);

  GLint color = glGetAttribLocation(shader_program, "color_");
  glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, vertex_element_size,
    (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(color);

  GLint tex_coord = glGetAttribLocation(shader_program, "tex_coord_");
  glVertexAttribPointer(tex_coord, 2, GL_FLOAT, GL_FALSE, vertex_element_size,
    (void*)(6*sizeof(float)));

  glEnableVertexAttribArray(tex_coord);
  GLint normal = glGetAttribLocation(shader_program, "normal_modelspace_");
  glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, vertex_element_size,
    (void*)(8*sizeof(float)));
  glEnableVertexAttribArray(normal);

  m_m_uniform = glGetUniformLocation(shader_program, "m");
  m_p_uniform = glGetUniformLocation(shader_program, "p");
  m_v_uniform = glGetUniformLocation(shader_program, "v");
  m_texture_uniform = glGetUniformLocation(shader_program, "texture");
  m_light_positions = glGetUniformLocation(shader_program, "lightPosition");
  m_active_lights = glGetUniformLocation(shader_program, "activeLights");
  glUseProgram(0);
}

GLint CubeRenderer::lightPositions() const {
  return m_light_positions;
}

GLint CubeRenderer::activeLights() const {
  return m_active_lights;
}

void CubeRenderer::SetTexture(GLuint texture) const {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glUniform1i(m_texture_uniform, 0);
}

void CubeRenderer::DrawCube(const glm::mat4& m, const glm::mat4& v,
    const glm::mat4& p) const {
  glUniformMatrix4fv(m_m_uniform, 1, GL_FALSE, glm::value_ptr(m));
  glUniformMatrix4fv(m_v_uniform, 1, GL_FALSE, glm::value_ptr(v));
  glUniformMatrix4fv(m_p_uniform, 1, GL_FALSE, glm::value_ptr(p));

  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*36*11, cube_vertices, GL_STREAM_DRAW);
  glDrawArrays(GL_TRIANGLES, 0, 36);
}

