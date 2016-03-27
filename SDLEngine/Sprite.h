#pragma once
#include <GL\glew.h>
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <string>
#include "Error.h"
#include "Vertex.h"
#include "ShaderProgram.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define _USE_MATH_DEFINES
#include <math.h>


class Sprite
{
public:
	Sprite(const std::string& path);
	~Sprite();

	int GetWidth() { return width; }
	int GetHeight() { return height; }
	std::string GetName() { return name; }

	void Draw(const SDL_Rect& dest, const Color& color);

private:
	void GenerateVertexBuffer();
	void GenerateIndexBuffer();
	GLuint GenerateTexture(SDL_Surface* surface);
	void Unload();

private:
	std::string name;
	int width;
	int height;
	ShaderProgram* shader;
	GLuint textureID;

	// data
	VertexPositionTexture vertexData[4];
	unsigned int indexData[6];

	// buffers
	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint uvBuffer;

	// shader attrib locations
	GLuint shaderUniformLoc_sampler;
	GLuint shaderUniformLoc_colorTint;
	GLuint shaderUniformLoc_transform;
	GLuint shaderAttribLoc_vertexUV;
	GLuint shaderAttribLoc_vertexPosition;

	static ShaderProgram* textureShader;
};

