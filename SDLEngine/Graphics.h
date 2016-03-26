#pragma once
#include <windows.h>
#include <GL\glew.h>
#include <SDL\SDL.h>
#include "Error.h"
#include "ShaderProgram.h"
#include "Vertex.h"
#include <cstddef>

class Graphics
{
public:
	Graphics();
	~Graphics();
	
	SDL_Window* GetWindow() { return window; }

	void Draw();

private:
	void InitSDL();

private:
	int screenWidth;
	int screenHeight;
	SDL_Window* window;

	// --------------------------------
	//				TEST
	// --------------------------------
	Vertex vertexData[6];
	GLuint vboID;
	ShaderProgram* colorProg;
};

