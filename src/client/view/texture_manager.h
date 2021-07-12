#pragma once

#include <map>
#include <string>

#include "common/platform.h"
#include "common/resource_locator.h"

enum Texture {
	NONE = 0,
	GRASS = 1,
	SAND = 2,
	ROCK = 3,
	BW = 4,
	FONT = 5,
	FACE = 6,
	HEAD = 7,
	GRR = 8,
	SIZE = 9,
};

class TextureManager {
public:
	TextureManager(const ResourceLocator&);
	~TextureManager();

	GLuint operator[](int) const;

private:
	void LoadTextures();

	GLuint loadTexture(const std::string&);
	bool tryLoadTexture(const std::string&, GLuint&);

	ResourceLocator mResourceLocator;
	GLuint mTextures[Texture::SIZE];
};
