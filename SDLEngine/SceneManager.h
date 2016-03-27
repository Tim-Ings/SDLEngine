#pragma once
#include <vector>
#include "BaseScene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

private:
	int currentScene;
	std::vector<BaseScene*> scenes;
};

