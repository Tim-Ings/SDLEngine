#pragma once
#include <GL\glew.h>
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <string>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <math.h>
#include <algorithm>
#include <vector>
#include "ShaderProgram.h"
#include "Camera3.h"
#include "Error.h"
#include "Vertex.h"


class Sprite
{
public:
	Sprite(const std::string& path);
	~Sprite();

	int GetWidth() { return width; }
	int GetHeight() { return height; }
	std::string GetName() { return name; }

	void Draw(Camera3* cam, const SDL_Rect& dest, const Color& color);

private:
	void GenerateVertexBuffer();
	void GenerateIndexBuffer();
	void GenerateVertexArrayObject();
	void MapShaderAttributes();
	void LoadImage();
	GLuint GenerateTexture(SDL_Surface* surface);
	void Unload();

private:
	std::string name;
	int width;
	int height;
	ShaderProgram* shader;
	GLuint textureID;
	GLuint vertexArrayObjectID;

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
	GLuint shaderUniformLoc_model;
	GLuint shaderUniformLoc_view;
	GLuint shaderUniformLoc_projection;
	GLuint shaderAttribLoc_vertexUV;
	GLuint shaderAttribLoc_vertexPosition;
};

