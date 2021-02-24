#include "client/view/ft_renderer.h"
#include <stdio.h>
#include <alloca.h>
#include <ft2build.h>
#include FT_FREETYPE_H

FtRenderer::FtRenderer(const ResourceLocator& rl):
  Shader(rl, "resources/shaders/ft_text.vert",
         "resources/shaders/ft_text.frag"),
  m_chars()
{
  FT_Library ft_lib;
  FT_Error err = FT_Init_FreeType(&ft_lib);
  if (err != FT_Err_Ok) {
    printf("FT_Init_FreeType: %d\n", err);
    exit(1);
  }

  FT_Face face;
  err = FT_New_Face(ft_lib, "resources/fonts/ChicagoFLF.ttf", 0, &face);
  if (err != FT_Err_Ok) {
    printf("FT_New_Face: %d\n", err);
    exit(1);
  }

  FT_Set_Pixel_Sizes(face, 0, 48);
  // disable byte-alignment restriction
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for (unsigned char c = 0; c < 128; c++) {
    // load character glyph
    err = FT_Load_Char(face, c, FT_LOAD_RENDER);
    if (err != FT_Err_Ok) {
      printf("FT_Load_Char: FT_Error %d on glyph %u\n", err, c);
      exit(1);
    }
    // generate texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
      face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
      face->glyph->bitmap.buffer);
    // set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // now store character for later use
    CharGlyph character = {
      texture,
      glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
      face->glyph->advance.x
    };
    m_chars.insert(std::pair<char, CharGlyph>(c, character));
  }

  FT_Done_Face(face);
  FT_Done_FreeType(ft_lib);
}

void FtRenderer::On() const {
}

void FtRenderer::DrawText(float x, float y, float scale,
                          const std::string& text, const Color& color) const
{
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL,
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

  glUseProgram(shader_program);
  glUniform3f(glGetUniformLocation(shader_program, "textColor"),
              color.r, color.g, color.b);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);

  // iterate through all characters
  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++) {
    CharGlyph ch = m_chars.at(*c);

    float xpos = x + ch.bearing.x * scale;
    float ypos = y - (ch.size.y - ch.bearing.y) * scale;

    float w = ch.size.x * scale;
    float h = ch.size.y * scale;
    // update VBO for each character
    float vertices[6][4] = {
      { xpos,     ypos + h, 0.0f, 0.0f },
      { xpos,     ypos,     0.0f, 1.0f },
      { xpos + w, ypos,     1.0f, 1.0f },

      { xpos,     ypos + h, 0.0f, 0.0f },
      { xpos + w, ypos,     1.0f, 1.0f },
      { xpos + w, ypos + h, 1.0f, 0.0f },
    };
    // render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.textureID);
    // update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // advance cursors for next glyph
    // (note that advance is number of 1/64 pixels)
    // bitshift by 6 to get value in pixels (2^6 = 64)
    x += (ch.advance >> 6) * scale;
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

