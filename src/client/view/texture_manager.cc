
#include <SDL_image.h>
#include <cassert>
#include <iostream>
#include <sstream>

#include "common/platform.h"
#include "common/util/die.h"
#include "client/view/texture_manager.h"

TextureManager::TextureManager(const ResourceLocator& resourceLocator):
	mResourceLocator(resourceLocator)
{
	LoadTextures();
	mTypeToTexture[ObjectType::GRASS] = TEXTURE_GRASS;
	mTypeToTexture[ObjectType::SAND] = TEXTURE_SAND;
	mTypeToTexture[ObjectType::ROCK] = TEXTURE_ROCK;
	mTypeToTexture[ObjectType::BW] = TEXTURE_BW;
	mTypeToTexture[ObjectType::FONT] = TEXTURE_FONT;
	mTypeToTexture[ObjectType::PLAYER] = TEXTURE_FACE;
	mTypeToTexture[ObjectType::MONSTER] = TEXTURE_GRR;
	mTypeToTexture[ObjectType::TORCH] = TEXTURE_GRR;
}

TextureManager::~TextureManager()
{
	for (GLuint texture : mTextures)
		glDeleteTextures(1, &texture);
}

GLuint TextureManager::operator[] (ObjectType type) const {
	return mTextures[mTypeToTexture[type]];
}

GLuint TextureManager::operator[] (Texture texture) const
{
	return mTextures[texture];
}

GLuint TextureManager::operator[] (int t) const {
    return mTextures[t];
}

void TextureManager::LoadTextures()
{
	mTextures[Texture::TEXTURE_GRASS] =
		loadTexture("resources/images/grass.png");
	mTextures[Texture::TEXTURE_FONT] =
		loadTexture("resources/images/font.png");
	mTextures[Texture::TEXTURE_SAND] =
		loadTexture("resources/images/sand.png");
	mTextures[Texture::TEXTURE_ROCK] =
		loadTexture("resources/images/rock.png");
	mTextures[Texture::TEXTURE_BW] =
		loadTexture("resources/images/bw.png");
	mTextures[Texture::TEXTURE_HEAD] =
		loadTexture("resources/images/head.png");
	mTextures[Texture::TEXTURE_GRR] =
		loadTexture("resources/images/grr.png");

	// not used ATM
	mTextures[Texture::TEXTURE_FACE] =
		loadTexture("resources/images/face.png");
}

GLuint TextureManager::loadTexture(const std::string& fn)
{
	std::string texture_path = mResourceLocator.findResource(fn);
	GLuint texture;
	if (tryLoadTexture(texture_path, texture))
		return texture;

	std::cerr << "Failed to load " << fn << std::endl;
	exit(EXIT_FAILURE);
}

bool TextureManager::tryLoadTexture(const std::string& fn,
				    GLuint& texture)
{
	SDL_Surface *tmp = IMG_Load(fn.c_str());

	if (!tmp)
		return false;

	SDL_Surface *surface = SDL_DisplayFormatAlpha(tmp);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	SDL_PixelFormat *format = surface->format;

	if (format->Amask) {
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, surface->w, surface->h,
				  GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
	} else {
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, surface->w, surface->h,
				  GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
	}

	SDL_FreeSurface(surface);
	SDL_FreeSurface(tmp);
	return true;
}
