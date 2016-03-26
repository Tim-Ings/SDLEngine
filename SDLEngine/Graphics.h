#pragma once
#include <windows.h>
#include <GL\glew.h>
#include <SDL\SDL.h>
#include "Error.h"
#include "ShaderProgram.h"
#include "Vertex.h"
#include <cstddef>

class Engine;

class Graphics
{
public:
	Graphics(Engine* e);
	~Graphics();
	
	SDL_Window* GetWindow() { return window; }

	void Draw();

private:
	void InitSDL();

private:
	Engine* engine;
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

