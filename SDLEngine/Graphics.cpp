#include "Graphics.h"
#include "Error.h"
#include "Input.h"



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

	// --------------------------------
	//				TEST
	// --------------------------------
	
	shader.reset(new ShaderProgram("texture.vs", "texture.fs"));
	shader->SetUniform("sampler", 0);
	texture.reset(new Texture("models/dwarf/dwarf_Body.png"));
	mesh.reset(new Mesh("models/dwarf/dwarf.obj"));

	/*Vertex verts[] =
	{
		new Vertex()
	};
	mesh.reset(new Mesh());*/

	// --------------------------------
	//				END
	// --------------------------------
}


Graphics::~Graphics()
{
	if (glContext)
		SDL_GL_DeleteContext(glContext);
	if (window)
		SDL_DestroyWindow(window);

	SDL_Quit();
}


void Graphics::InitSDL()
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}


static char windowtitle[BUFSIZ];

void Graphics::Update(float deltaTime)
{
	sprintf_s(windowtitle, BUFSIZ, "camera pos = { %f, %f, %f, }", camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
	SDL_SetWindowTitle(window, windowtitle);

	camera->Update();

	if (Input::IsKeyDown(SDL_SCANCODE_W))
		camera->ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (Input::IsKeyDown(SDL_SCANCODE_S))
		camera->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (Input::IsKeyDown(SDL_SCANCODE_A))
		camera->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (Input::IsKeyDown(SDL_SCANCODE_D))
		camera->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	if (Input::IsKeyDown(SDL_SCANCODE_SPACE))
		camera->ProcessKeyboard(Camera_Movement::UP, deltaTime);
	if (Input::IsKeyDown(SDL_SCANCODE_E))
		camera->ProcessKeyboard(Camera_Movement::DOWN, deltaTime);

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

	// --------------------------------						   
	//				TEST									   
	// --------------------------------	  					   

	texture->Bind();
	shader->Bind();
	{
		shader->Update(meshTransform, *camera);
		mesh->Draw();
	}
	shader->Unbind();

	// --------------------------------						   
	//				END										   
	// --------------------------------						   

	SDL_GL_SwapWindow(window);
}