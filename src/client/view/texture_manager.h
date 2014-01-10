#pragma once

#include <map>
#include <string>
#include <GL/gl.h>

namespace Texture {
  enum Enum {
    GRASS,
    FONT,
    FACE,
    HEAD,
    BW,
    ROCK,
    SAND,
    SIZE
  };
}

class TextureManager {
public:
  TextureManager();
  ~TextureManager();

  GLuint operator[](Texture::Enum) const;

private:
  void LoadTextures();
  GLuint LoadTexture(const std::string&);

  GLuint m_textures[Texture::SIZE];
};
