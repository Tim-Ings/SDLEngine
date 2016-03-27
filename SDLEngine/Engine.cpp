#include "Engine.h"



Engine::Engine() :
	running(true)
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
	graphics.reset(new Graphics(this));
	fpsManager.reset(new FpsManager(-1));
	fpsManager->SetWindowTitleFormat("SDL Engine - %f cur fps - %f avg fps");
	fpsManager->SetWindowTitleUpdatePeriod(1000);
	fpsManager->SetWindow(graphics->GetWindow());
	sceneManager.reset(new SceneManager());
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
	graphics->Update(fpsManager->GetDeltaTime());
	Input::Update();
}