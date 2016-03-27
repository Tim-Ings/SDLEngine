#pragma once
#include <SDL\SDL.h>
#include <memory>
#include "Graphics.h"
#include "Input.h"
#include "FpsManager.h"

class Engine
{
public:
	Engine();
	~Engine();

	void Run();

private:
	void Init();
	void GameLoop();
	void Draw();
	void Update();

private:
	bool running;
	Graphics* graphics;
	FpsManager* fpsManager;
};

