#pragma once

#include <map>
#include <string>

#include "common/platform.h"
#include "common/proto/udpgame.pb.h"
#include "common/resource_locator.h"

class TextureManager {
public:
	TextureManager(const ResourceLocator&);
	~TextureManager();

	GLuint operator[](ObjectType) const;
	GLuint operator[](Texture) const;
	GLuint operator[](int) const;

private:
	void LoadTextures();

	GLuint loadTexture(const std::string&);
	bool tryLoadTexture(const std::string&, GLuint&);

	ResourceLocator mResourceLocator;
	GLuint mTextures[Texture::TEXTURE_SIZE];
	Texture mTypeToTexture[Texture::TEXTURE_SIZE];
};
