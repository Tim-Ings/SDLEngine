#include "Graphics.h"


Graphics::Graphics()
{
	screenWidth = 1024;
	screenHeight = 768;
	window = nullptr;

	InitSDL();

	glClearColor(0.1, 0.1, 0.1, 1);

	// --------------------------------
	//				TEST
	// --------------------------------
	vertexData[0].position.x = 0.9;
	vertexData[0].position.y = -0.9;
	vertexData[0].position.z = 0.0;

	vertexData[1].position.x = -0.7;
	vertexData[1].position.y = -1.0;
	vertexData[1].position.z = 0.0;

	vertexData[2].position.x = 0.0;
	vertexData[2].position.y = 1.0;
	vertexData[2].position.z = 0.0;

	vertexData[0].color.r = 255;
	vertexData[0].color.g = 0;
	vertexData[0].color.b = 0;
	vertexData[0].color.a = 255;

	vertexData[1].color.r = 0;
	vertexData[1].color.g = 255;
	vertexData[1].color.b = 0;
	vertexData[1].color.a = 255;

	vertexData[2].color.r = 0;
	vertexData[2].color.g = 0;
	vertexData[2].color.b = 255;
	vertexData[2].color.a = 255;

	/*for (int i = 0; i < 3; i++)
	{
		vertexData[i].color.r = 1;
		vertexData[i].color.g = 1;
		vertexData[i].color.b = 1;
		vertexData[i].color.a = 1;
	}*/

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	colorProg = new ShaderProgram("BasicVertexShader.glsl", "BasicFragmentShader.glsl");
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

	colorProg->Use();

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); // position
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)); // color
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	colorProg->Disuse();

	// --------------------------------
	//				END
	// --------------------------------

	SDL_GL_SwapWindow(window);
}