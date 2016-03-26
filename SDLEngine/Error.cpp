#include "Error.h"
#include <SDL\SDL.h>
#include <iostream>

void fatalError(std::string err)
{
	std::cout << err << std::endl;
	std::cout << "Press any key to exit" << std::endl;
	int temp;
	std::cin >> temp;
	SDL_Quit();
	exit(EXIT_FAILURE);
}