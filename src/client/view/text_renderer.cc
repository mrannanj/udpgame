#include "client/view/text_renderer.h"

TextRenderer::TextRenderer(GLuint font_texture):
  Shader("resources/shaders/text.vert", "resources/shaders/text.frag"),
  m_font_texture(font_texture)
{
  glUseProgram(shader_program);
  glBindFragDataLocation(shader_program, 0, "frag_color");

  vertex_elem_size_ = 4 * sizeof(float);

  GLint posAttrib = glGetAttribLocation(shader_program, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, vertex_elem_size_, 0);

  GLint texAttrib = glGetAttribLocation(shader_program, "tex_coord_");
  glEnableVertexAttribArray(texAttrib);
  glVertexAttribPointer(texAttrib, 2,
    GL_FLOAT, GL_FALSE, vertex_elem_size_, (void*)(2 * sizeof(float)));

  GLint fg_color = glGetUniformLocation(shader_program, "fg_color");
  glUniform4f(fg_color, 1.0f, 1.0f, 1.0f, 1.0f);

  bg_color_uni_ = glGetUniformLocation(shader_program, "bg_color");
  glUniform4f(bg_color_uni_, 0.3f, 0.3f, 0.0f, 0.5f);

  GLint texture_uniform = glGetUniformLocation(shader_program, "texture");
  glUniform1i(texture_uniform, GL_TEXTURE0);
}

void TextRenderer::On() const
{
  glUseProgram(shader_program);
  glBindVertexArray(vertex_array);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_font_texture);
}

void TextRenderer::DrawText(float top_x, float top_y, float size,
  const std::string& s, const Color& bg) const
{
  glUniform4f(bg_color_uni_, bg.r, bg.g, bg.b, 0.5f);

  size_t nchar = s.size();
  size_t arr_size = nchar * vertex_elem_size_ * 4;
  float letter_size = 1.0f / 16;
  float* vertices = (float*)alloca(arr_size);
  float* p = vertices;
  float x = top_x;

  for (unsigned i = 0; i < nchar; ++i)
  {
    unsigned c = (unsigned)(s[i] - 32);
    unsigned row = c / 16;
    unsigned col = c % 16;

    // top left
    p[0] = x;
    p[1] = top_y;
    p[2] = col * letter_size;
    p[3] = row * letter_size;

    // top right
    p[4] = x + size;
    p[5] = top_y;
    p[6] = (col+1) * letter_size;
    p[7] = row * letter_size;

    // bottom right
    p[8] = x + size;
    p[9] = top_y - size;
    p[10] = (col+1) * letter_size;
    p[11] = (row+1) * letter_size;

    // bottom left
    p[12] = x;
    p[13] = top_y - size;
    p[14] = col * letter_size;
    p[15] = (row+1) * letter_size;

    p += 16;
    x += size;
  }
  glBufferData(GL_ARRAY_BUFFER, arr_size, vertices, GL_STREAM_DRAW);
  glDrawArrays(GL_QUADS, 0, 4*(GLsizei)nchar);
}

