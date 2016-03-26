#include "Engine.h"



Engine::Engine()
{
	running = true;

	Init();
}


Engine::~Engine()
{
}


void Engine::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	graphics = new Graphics(this);
}

void Engine::Run()
{
	GameLoop();
}


void Engine::GameLoop()
{
	while (running)
	{
		Update();
		Draw();
	}
}


void Engine::Draw()
{
	graphics->Draw();
}


void Engine::Update()
{
	Input::Update();
}