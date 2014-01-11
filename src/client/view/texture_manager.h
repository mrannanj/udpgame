#pragma once

#include <map>
#include <string>
#include <GL/gl.h>

#include "common/proto/udpgame.pb.h"

class TextureManager {
public:
  TextureManager();
  ~TextureManager();

  GLuint operator[](Texture) const;
  GLuint operator[](int) const;

private:
  void LoadTextures();
  GLuint LoadTexture(const std::string&);

  GLuint mTextures[Texture::TEXTURE_SIZE];
};
