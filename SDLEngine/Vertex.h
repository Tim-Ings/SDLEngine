#pragma once
#include <GL\glew.h>

struct Position
{
	float x;
	float y;
	float z;
};

struct TextureCoord
{
	float u;
	float v;
};

struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct VertexPositionColor
{
	Position position;
	Color color;
};

struct VertexPosition
{
	Position position;
};

struct VertexPositionTexture
{
	Position position;
	TextureCoord uv;
};