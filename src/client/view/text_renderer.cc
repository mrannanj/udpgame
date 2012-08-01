#include "client/view/text_renderer.h"

TextRenderer::TextRenderer():
  sp_()
{
}

void TextRenderer::Init(GLuint font_texture) {
  sp_.Init("resources/shaders/text.vert", "resources/shaders/text.frag");
  vertex_elem_size_ = 4 * sizeof(float);

  GLint posAttrib = glGetAttribLocation(sp_.shader_program, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, vertex_elem_size_, 0);

  GLint texAttrib = glGetAttribLocation(sp_.shader_program, "tex_coord_");
  glEnableVertexAttribArray(texAttrib);
  glVertexAttribPointer(texAttrib, 2,
    GL_FLOAT, GL_FALSE, vertex_elem_size_, (void*)(2 * sizeof(float)));

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, font_texture);
  glUniform1i(glGetUniformLocation(sp_.shader_program, "tex" ), 0);

  GLint color_uniform = glGetUniformLocation(sp_.shader_program, "color");
  glUniform3f(color_uniform, 1.0f, 0.5f, 0.5f);
}

void TextRenderer::DrawText(float top_x, float top_y, float size, const std::string& s) const {
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

  glUseProgram(sp_.shader_program);
  glBindVertexArray(sp_.vertex_array);
  glBindBuffer(GL_ARRAY_BUFFER, sp_.vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, arr_size, vertices, GL_STREAM_DRAW);
  glDrawArrays(GL_QUADS, 0, 4*(GLsizei)nchar);
}

