#ifndef CLIENT_VIEW_TEXTURE_MANAGER_H
#define CLIENT_VIEW_TEXTURE_MANAGER_H

#include <map>
#include <string>
#include <GL/gl.h>

#include "common/google.h"

namespace Texture {
  enum Enum {
    GRASS,
    FONT,
    SIZE
  };
}

class TextureManager
{
public:
  TextureManager();
  ~TextureManager();
  DISALLOW_COPY_AND_ASSIGN(TextureManager);

  GLuint operator[](Texture::Enum) const;

private:
  void LoadTextures();
  GLuint LoadTexture(const std::string&);

  GLuint m_textures[Texture::SIZE];
};

#endif

