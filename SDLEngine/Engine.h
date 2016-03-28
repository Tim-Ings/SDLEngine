#pragma once
#include "Graphics.h"
#include "FpsManager.h"
#include "SceneManager.h"

class Engine
{
public:
	Engine();
	~Engine();

	void Run();
	Graphics* GetGraphics() { return graphics.get(); }
	FpsManager* GeFpsManager() { return fpsManager.get(); }
	SceneManager* GetSceneManager() { return sceneManager.get(); }

private:
	void Init();
	void GameLoop();
	void Draw();
	void Update();

private:
	bool running;
	std::unique_ptr<Graphics> graphics;
	std::unique_ptr<FpsManager> fpsManager;
	std::unique_ptr<SceneManager> sceneManager;
};

