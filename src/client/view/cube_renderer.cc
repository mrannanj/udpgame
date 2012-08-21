#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "client/view/cube_renderer.h"

float cube_vertices[] =
{
  -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
   1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
   1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
   1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
  -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

  -1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
   1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
   1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
   1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
  -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
  -1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

  -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
  -1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
  -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
  -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
  -1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

   1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
   1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
   1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
   1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
   1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
   1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

  -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
   1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
   1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
   1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
  -1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
  -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

  -1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
   1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
   1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
   1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
  -1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
  -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
};

CubeRenderer::CubeRenderer():
  Shader("resources/shaders/cube.vert", "resources/shaders/cube.frag")
{
  Init();
}

void CubeRenderer::Init()
{
  size_t vertex_element_size = 8 * sizeof(float);
  glUseProgram(shader_program);
  glBindFragDataLocation(shader_program, 0, "frag_color");

  GLint position = glGetAttribLocation(shader_program, "position");
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

  m_mvp_uniform = glGetUniformLocation(shader_program, "mvp");
  m_texture_uniform = glGetUniformLocation(shader_program, "texture");
  glUseProgram(0);
}

void CubeRenderer::SetTexture(GLuint texture) const
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glUniform1i(m_texture_uniform, 0);
}

void CubeRenderer::DrawCube(const glm::mat4& mvp) const
{
  glUniformMatrix4fv(m_mvp_uniform, 1, GL_FALSE, glm::value_ptr(mvp));

  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*36*8, cube_vertices, GL_STREAM_DRAW);
  glDrawArrays(GL_TRIANGLES, 0, 36);
}

