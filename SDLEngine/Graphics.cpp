#include "Graphics.h"


Graphics::Graphics(Engine* e)
{
	// init values
	engine = e;
	screenWidth = 1024;
	screenHeight = 768;
	window = nullptr;

	// init sdl
	InitSDL();

	// init camera
	camera.reset(new Camera3(window));

	// init a floor
	floorGrid.reset(new FloorGrid());

	// --------------------------------
	//				TEST
	// --------------------------------
	
	sprite = new Sprite("ayy_lamao.jpg");
	//sprite2 = new Sprite("undead_cool_face.jpg");

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

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}


// Function to draw a grid of lines
//void drawGround(Camera3* cam, float groundLevel)
//{
//	GLfloat extent = 600.0f; // How far on the Z-Axis and X-Axis the ground extends
//	GLfloat stepSize = 20.0f;  // The size of the separation between points
//
//							   // Set colour to white
//	glColor3ub(255, 0, 255);
//
//	// Draw our ground grid
//	glMatrixMode(GL_MODELVIEW);
//	glMultMatrix(glm::value_ptr(cam->GetViewMatrix()));
//	glBegin(GL_LINES);
//	for (GLint loop = -extent; loop < extent; loop += stepSize)
//	{
//		// Draw lines along Z-Axis
//		glVertex3f(loop, groundLevel, extent);
//		glVertex3f(loop, groundLevel, -extent);
//
//		// Draw lines across X-Axis
//		glVertex3f(-extent, groundLevel, loop);
//		glVertex3f(extent, groundLevel, loop);
//	}
//	glEnd();
//}


void Graphics::Update(float deltaTime)
{
	camera->Update();

	if (Input::IsKeyDown(SDL_SCANCODE_W))
		camera->ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (Input::IsKeyDown(SDL_SCANCODE_S))
		camera->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (Input::IsKeyDown(SDL_SCANCODE_A))
		camera->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (Input::IsKeyDown(SDL_SCANCODE_D))
		camera->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);

	camera->ProcessMouseMovement(Input::GetMousePos());

	if (Input::WasKeyDown(SDL_SCANCODE_ESCAPE))
		camera->SetWarpMouse(false);

	if (Input::IsMouseDown(MOUSE_LEFT))
		camera->SetWarpMouse(true);

}


void Graphics::Draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind camera
	camera->Update();
	camera->Bind();

	// draw the floor
	floorGrid->Draw(camera.get());

	// --------------------------------						   
	//				TEST									   
	// --------------------------------	  					   

	sprite->Draw(camera.get(), { 0, 0, 1, 1 }, { 255, 255, 255, 255 });
	//sprite2->Draw(camera.get(), { 0, 0, 1, 1 }, { 255, 255, 1, 100 });

	// --------------------------------						   
	//				END										   
	// --------------------------------						   

	SDL_GL_SwapWindow(window);
}