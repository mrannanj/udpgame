
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL_image.h>
#include <cassert>
#include <cstdio>

#include "common/util/die.h"
#include "client/view/texture_manager.h"

TextureManager::TextureManager() {
  LoadTextures();
  mTypeToTexture[ObjectType::GRASS] = TEXTURE_GRASS;
  mTypeToTexture[ObjectType::SAND] = TEXTURE_SAND;
  mTypeToTexture[ObjectType::ROCK] = TEXTURE_ROCK;
  mTypeToTexture[ObjectType::BW] = TEXTURE_BW;
  mTypeToTexture[ObjectType::FONT] = TEXTURE_FONT;
  mTypeToTexture[ObjectType::PLAYER] = TEXTURE_FACE;
  mTypeToTexture[ObjectType::MONSTER] = TEXTURE_GRR;
}

TextureManager::~TextureManager() {
  for (GLuint texture: mTextures)
    glDeleteTextures(1, &texture);
}

GLuint TextureManager::operator[](ObjectType type) const {
  return mTextures[mTypeToTexture[type]];
}

GLuint TextureManager::operator[](Texture texture) const {
  return mTextures[texture];
}

GLuint TextureManager::operator[](int t) const {
  return mTextures[t];
}

void TextureManager::LoadTextures() {
  mTextures[Texture::TEXTURE_GRASS]=LoadTexture("resources/images/grass.png");
  mTextures[Texture::TEXTURE_FONT] = LoadTexture("resources/images/font.png");
  mTextures[Texture::TEXTURE_SAND] = LoadTexture("resources/images/sand.png");
  mTextures[Texture::TEXTURE_ROCK] = LoadTexture("resources/images/rock.png");
  mTextures[Texture::TEXTURE_BW] = LoadTexture("resources/images/bw.png");
  mTextures[Texture::TEXTURE_HEAD] = LoadTexture("resources/images/head.png");
  mTextures[Texture::TEXTURE_GRR] = LoadTexture("resources/images/grr.png");

  // not used ATM
  mTextures[Texture::TEXTURE_FACE] = LoadTexture("resources/images/face.png");
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

