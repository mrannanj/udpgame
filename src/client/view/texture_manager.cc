
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
}

TextureManager::~TextureManager()
{
	for (GLuint texture : mTextures)
		glDeleteTextures(1, &texture);
}

GLuint TextureManager::operator[] (int t) const {
    return mTextures[t];
}

void TextureManager::LoadTextures()
{
	mTextures[Texture::GRASS] = loadTexture("resources/images/grass.png");
	mTextures[Texture::FONT] = loadTexture("resources/images/font.png");
	mTextures[Texture::SAND] = loadTexture("resources/images/sand.png");
	mTextures[Texture::ROCK] = loadTexture("resources/images/rock.png");
	mTextures[Texture::BW] = loadTexture("resources/images/bw.png");
	mTextures[Texture::HEAD] = loadTexture("resources/images/head.png");
	mTextures[Texture::GRR] = loadTexture("resources/images/grr.png");

	// not used ATM
	mTextures[Texture::FACE] = loadTexture("resources/images/face.png");
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
	SDL_Surface *surface = IMG_Load(fn.c_str());

	if (surface == nullptr)
		return false;

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
	return true;
}
