#pragma once
#include <SDL\SDL.h>
#include <memory>
#include "Camera3.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Model.h"

class Engine;

enum RenderMode
{
	RENDERMODE_NORMAL,
	RENDERMODE_WIREFRAME,
	RENDERMODE_POINT,
};

class Graphics
{
public:
	Graphics(Engine* e);
	~Graphics();
	
	SDL_Window* GetWindow() { return window; }
	inline void SetRenderMode(RenderMode mode)
	{
		switch (mode)
		{
		case RENDERMODE_NORMAL:
			glPolygonMode(GL_FRONT, GL_FILL);
			break;
		case RENDERMODE_WIREFRAME:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case RENDERMODE_POINT:
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			break;
		}
	}

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

	std::unique_ptr<Model> skyBox;
	std::unique_ptr<Model> model;
	std::unique_ptr<ShaderProgram> shader;
	Transform modelTransform;
};

