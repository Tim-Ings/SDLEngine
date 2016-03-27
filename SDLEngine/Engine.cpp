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
	fpsManager = new FpsManager(10);
	fpsManager->SetWindowTitleFormat("SDL Engine - %d fps");
	fpsManager->SetWindowTitleUpdatePeriod(1);
	fpsManager->SetWindow(graphics->GetWindow());
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
	fpsManager->Update();
	Input::Update();
}