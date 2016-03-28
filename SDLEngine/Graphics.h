#pragma once
#include <SDL\SDL.h>
#include <memory>
#include "Camera3.h"
#include "Mesh.h"
#include "ShaderProgram.h"

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
	SDL_GLContext glContext;
	std::unique_ptr<Camera3> camera;

	std::unique_ptr<Mesh> mesh;
	std::unique_ptr<ShaderProgram> colorShader;
	Transform meshTransform;
};

