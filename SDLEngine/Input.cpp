#include "Input.h"

bool Input::keyboardState[BUFSIZ];
bool Input::lastKeyboardState[BUFSIZ];
int Input::mouseX;
int Input::mouseY;
bool Input::mouseButtons[3];
bool Input::lastMouseButtons[3];

void Input::Update()
{
	// reset all the last frame's key states
	for (int i = 0; i < BUFSIZ; i++)
		Input::lastKeyboardState[i] = false;

	// reset all the last frame's mouse button states
	for (int i = 0; i < 3; i++)
		Input::lastMouseButtons[i] = false;

	SDL_Event e;
	static bool keysUpdatedThisFrame[BUFSIZ];
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			exit(EXIT_SUCCESS); // this should fire an event so the engine knows to do stuff before exiting
			break;
		case SDL_MOUSEMOTION:
			Input::mouseX = e.motion.x;
			Input::mouseY = e.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			// sdl button 0 is null, so subtract 1
			Input::mouseButtons[e.button.button - 1] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			// sdl button 0 is null, so subtract 1
			Input::mouseButtons[e.button.button - 1] = false;
			Input::lastMouseButtons[e.button.button - 1] = true;
			break;
		case SDL_KEYDOWN:
			Input::keyboardState[e.key.keysym.scancode] = true;
			break;
		case SDL_KEYUP:
			Input::keyboardState[e.key.keysym.scancode] = false;
			Input::lastKeyboardState[e.key.keysym.scancode] = true;
			break;
		}
	}
}


bool Input::IsKeyDown(SDL_Scancode key)
{
	if (!Input::keyboardState)
		return false;

	return Input::keyboardState[key];
}


bool Input::IsKeyUp(SDL_Scancode key)
{
	if (!Input::keyboardState)
		return false;
	
	return !Input::keyboardState[key];
}


bool Input::WasKeyDown(SDL_Scancode key)
{
	if (!Input::lastKeyboardState || !Input::keyboardState)
		return false;

	return Input::lastKeyboardState[key] && !Input::keyboardState[key];
}


bool Input::WasKeyUp(SDL_Scancode key)
{
	if (!Input::lastKeyboardState || !Input::keyboardState)
		return false;

	return !Input::lastKeyboardState[key] && Input::keyboardState[key];
}


bool Input::IsMouseDown(MouseButton mouseButton)
{
	return Input::mouseButtons[mouseButton];
}


bool Input::IsMouseUp(MouseButton mouseButton)
{
	return !Input::mouseButtons[mouseButton];
}


bool Input::WasMouseDown(MouseButton mouseButton)
{
	return !Input::mouseButtons[mouseButton] && Input::lastMouseButtons[mouseButton];
}


bool Input::WasMouseUp(MouseButton mouseButton)
{
	return Input::mouseButtons[mouseButton] && !Input::lastMouseButtons[mouseButton];
}