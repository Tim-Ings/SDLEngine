#pragma once
#include <vector>
#include "BaseScene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void ChangeScene(const int& sceneID);

private:
	int currentScene;
	std::vector<BaseScene*> scenes;
};

