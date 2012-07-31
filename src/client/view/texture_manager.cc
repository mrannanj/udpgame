
#include <assert.h>
#include <SDL_image.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <stdexcept>
#include <iostream>

#include "client/view/texture_manager.h"

TextureManager::TextureManager()
{
}

GLuint TextureManager::LoadImage(const std::string& fn)
{
  assert(textures_.find(fn) == textures_.end());

  SDL_Surface *surface;
  assert(surface = IMG_Load(fn.c_str()));

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  SDL_PixelFormat *format = surface->format;

  if (format->Amask)
  {
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
        GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0, GL_BGR,
        GL_UNSIGNED_BYTE, surface->pixels);
  }

  SDL_FreeSurface(surface);
  textures_[fn] = texture;

  return texture;
}

void TextureManager::FreeTextures()
{
  for (const auto& kv : textures_)
    glDeleteTextures(1, &kv.second);
}

GLuint TextureManager::GetTexture(const std::string& fn)
{
  std::map<std::string, GLuint>::const_iterator kv = textures_.find(fn);
  if (kv != textures_.end())
    return kv->second;
  return LoadImage(fn);
}

