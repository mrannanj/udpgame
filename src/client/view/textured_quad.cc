#include "client/view/textured_quad.h"

TexturedQuad::TexturedQuad():
  sp_()
{
}

void TexturedQuad::Init(GLuint texture) {
  sp_.Init("resources/shaders/textured_quad.vert", "resources/shaders/textured_quad.frag");

  GLint posAttrib = glGetAttribLocation(sp_.shader_program, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);

  GLint colAttrib = glGetAttribLocation(sp_.shader_program, "color");
  glEnableVertexAttribArray(colAttrib); glVertexAttribPointer(colAttrib, 3,
    GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));

  GLint texAttrib = glGetAttribLocation(sp_.shader_program, "texcoord");
  glEnableVertexAttribArray(texAttrib);   glVertexAttribPointer(texAttrib, 2,
    GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glUniform1i( glGetUniformLocation(sp_.shader_program, "tex" ), 0);
}

void TexturedQuad::Draw() {

  float vertices[] = {
//  Position      Color             Texcoords
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
    -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f  // Bottom-left
  };

  glUseProgram(sp_.shader_program);
  glBindVertexArray(sp_.vertex_array);
  glBindBuffer(GL_ARRAY_BUFFER, sp_.vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
  glDrawArrays(GL_QUADS, 0, 4);
}

