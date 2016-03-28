#pragma once
#include <windows.h>
#include <GL\glew.h>
#include <SDL\SDL.h>
#include <cstddef>
#include <memory>
#include "Error.h"
#include "ShaderProgram.h"
#include "Vertex.h"
#include "Sprite.h"
#include "Camera3.h"
#include "Input.h"
#include "FloorGrid.h"
#include "Model.h"

class Engine;

class Graphics
{
public:
	Graphics(Engine* e);
	~Graphics();
	
	SDL_Window* GetWindow() { return window; }

	void Update(float deltaTime);
	void Draw();

private:
	void InitSDL();

private:
	Engine* engine;
	int screenWidth;
	int screenHeight;
	SDL_Window* window;
	std::unique_ptr<Camera3> camera;
	std::unique_ptr<FloorGrid> floorGrid;

	Model* model;
	Sprite* sprite;
	Sprite* sprite2;
};

