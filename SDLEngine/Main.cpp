#include <stdlib.h>
#include "Engine.h"
#include "Scene_MainMenu.h"
#include "Scene_Game.h"

int main(int argc, char* argv[])
{
	// initialise engine
	std::unique_ptr<Engine> engine;
	engine.reset(new Engine());
	engine->Run();

	// register scenes
	std::unique_ptr<Scene_MainMenu> sceneMainMenu;
	sceneMainMenu.reset(new Scene_MainMenu());

	std::unique_ptr<Scene_Game> sceneGame;
	sceneGame.reset(new Scene_Game());
	
	return EXIT_SUCCESS;
}