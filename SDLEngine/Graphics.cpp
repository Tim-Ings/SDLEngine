#include "Graphics.h"
#include "Error.h"
#include "Input.h"



Graphics::Graphics(Engine* e)
{
	// init values
	engine = e;
	screenWidth = 1600;
	screenHeight = 900;
	window = nullptr;

	// init sdl
	InitSDL();

	// init camera
	camera.reset(new Camera3(window));

	// --------------------------------
	//				TEST
	// --------------------------------
	
	shader.reset(new ShaderProgram("TextureVertex.shader", "TextureFragment.shader"));
	shader->SetUniform("sampler", 0);
	model.reset(new Model("models/dwarf/dwarf.objmodel"));
	model->SetShader(shader.get());
	skyBox.reset(new Model("models/skycloud/skycloud.objmodel"));
	skyBox->SetShader(shader.get());

	modelTransform = Transform();

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

	// clear
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClearDepth(1.0);

	// culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


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
	if (Input::IsKeyDown(SDL_SCANCODE_SPACE))
		camera->ProcessKeyboard(Camera_Movement::UP, deltaTime);
	if (Input::IsKeyDown(SDL_SCANCODE_E))
		camera->ProcessKeyboard(Camera_Movement::DOWN, deltaTime);

	camera->ProcessMouseMovement(Input::GetMousePos());

	if (Input::WasKeyDown(SDL_SCANCODE_ESCAPE))
		camera->SetWarpMouse(false);

	if (Input::IsMouseDown(MOUSE_LEFT))
		camera->SetWarpMouse(true);


	if (Input::WasKeyDown(SDL_SCANCODE_I))
		SetRenderMode(RENDERMODE_NORMAL);
	if (Input::WasKeyDown(SDL_SCANCODE_O))
		SetRenderMode(RENDERMODE_WIREFRAME);
	if (Input::WasKeyDown(SDL_SCANCODE_P))
		SetRenderMode(RENDERMODE_POINT);

	float modelMoveSpeed = 0.01f;
	float modelRotationSpeed = 0.01f;
	if (Input::IsKeyDown(SDL_SCANCODE_KP_8))
		modelTransform.GetPos()->z += modelMoveSpeed;
	if (Input::IsKeyDown(SDL_SCANCODE_KP_5))
		modelTransform.GetPos()->z -= modelMoveSpeed;
	if (Input::IsKeyDown(SDL_SCANCODE_KP_4))
		modelTransform.GetPos()->x += modelMoveSpeed;
	if (Input::IsKeyDown(SDL_SCANCODE_KP_6))
		modelTransform.GetPos()->x -= modelMoveSpeed;
	if (Input::IsKeyDown(SDL_SCANCODE_KP_7))
		modelTransform.GetRot()->y -= modelRotationSpeed;
	if (Input::IsKeyDown(SDL_SCANCODE_KP_9))
		modelTransform.GetRot()->y += modelRotationSpeed;
	if (Input::WasKeyDown(SDL_SCANCODE_KP_MINUS))
		modelTransform = Transform();
}


void Graphics::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind camera
	camera->Update();

	// --------------------------------
	//				TEST
	// --------------------------------
	
	model->Draw(camera.get(), modelTransform);
	skyBox->Draw(camera.get(), Transform());

	// --------------------------------
	//				END
	// --------------------------------

	SDL_GL_SwapWindow(window);
}