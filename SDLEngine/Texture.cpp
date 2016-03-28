#include "texture.h"
#include "Error.h"
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>



Texture::Texture(const std::string& fileName) :
	textureID(0),
	width(0),
	height(0)
{
	// load image
	SDL_Surface* surface = nullptr;
	surface = IMG_Load(fileName.c_str());
	if (!surface)
		fatalError("Failed to load image from file: " + fileName);
	width = surface->w;
	height = surface->h;

	// create an ogl texture and bind it
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	{
		// texture uv wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// linear filtering
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// give ogl the sdl surface's data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	}
	glBindTexture(GL_TEXTURE_2D, NULL);

	// free the surface as ogl has the data it needs
	if (surface)
		SDL_FreeSurface(surface);
}


Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}


void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}