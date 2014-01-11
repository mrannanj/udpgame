
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL_image.h>
#include <cassert>
#include <cstdio>

#include "common/util/die.h"
#include "client/view/texture_manager.h"

TextureManager::TextureManager() {
  LoadTextures();
}

TextureManager::~TextureManager() {
  for (GLuint texture: m_textures)
    glDeleteTextures(1, &texture);
}

GLuint TextureManager::operator[](Texture texture) const {
  return m_textures[texture];
}

GLuint TextureManager::operator[](int t) const {
  return m_textures[t];
}

void TextureManager::LoadTextures() {
  m_textures[Texture::GRASS] = LoadTexture("resources/images/grass.png");
  m_textures[Texture::FONT] = LoadTexture("resources/images/font.png");
  m_textures[Texture::SAND] = LoadTexture("resources/images/sand.png");
  m_textures[Texture::ROCK] = LoadTexture("resources/images/rock.png");
  m_textures[Texture::BW] = LoadTexture("resources/images/bw.png");
  m_textures[Texture::HEAD] = LoadTexture("resources/images/head.png");

  // not used ATM
  m_textures[Texture::FACE] = LoadTexture("resources/images/face.png");
}

GLuint TextureManager::LoadTexture(const std::string& fn) {
  SDL_Surface *tmp = IMG_Load(fn.c_str());

  if (tmp == nullptr) {
    fprintf(stderr, "IMG_Load: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_Surface *surface = SDL_DisplayFormatAlpha(tmp);

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  SDL_PixelFormat *format = surface->format;

  if (format->Amask) {
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4,
      surface->w, surface->h, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
  } else {
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
      surface->w, surface->h, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
  }

  SDL_FreeSurface(surface);
  SDL_FreeSurface(tmp);
  return texture;
}

