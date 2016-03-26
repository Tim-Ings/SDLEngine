#pragma once
#include <SDL\SDL.h>
#include "Graphics.h"
#include "Input.h"

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
	
};

