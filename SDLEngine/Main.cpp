#include <stdlib.h>
#include "Engine.h"

int main(int argc, char* argv[])
{
	Engine* engine = new Engine();
	engine->Run();
	return EXIT_SUCCESS;
}