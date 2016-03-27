#include "Graphics.h"


Graphics::Graphics(Engine* e)
{
	engine = e;

	screenWidth = 1024;
	screenHeight = 768;
	window = nullptr;

	InitSDL();

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// --------------------------------
	//				TEST
	// --------------------------------
	
	sprite = new Sprite("ayy_lamao.jpg");
	sprite2 = new Sprite("undead_cool_face.jpg");

	// --------------------------------
	//				END
	// --------------------------------
}


Graphics::~Graphics()
{
}


void Graphics::InitSDL()
{
	window = SDL_CreateWindow("SDL Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
	if (!window)
		fatalError("FAILED: SDL_CreateWindow()");
	
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (!glContext)
		fatalError("FAILED: SDL_GL_CreateContext()");

	auto err = glewInit();
	if (err != GLEW_OK)
		fatalError("FAILED: glewInit(): " + err);
}


void Graphics::Draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// --------------------------------
	//				TEST
	// --------------------------------

	sprite->Draw({ 0, 0, 1, 1 });
	sprite2->Draw({ 0, 0, 1, 1 });

	// --------------------------------
	//				END
	// --------------------------------

	SDL_GL_SwapWindow(window);
}