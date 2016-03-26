#include "Input.h"

const Uint8* Input::keyboardState = nullptr;
const Uint8* Input::lastKeyboardState = nullptr;
int Input::mouseX;
int Input::mouseY;

void Input::Update()
{
	SDL_Event e;
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
		default:
			break;
		}
	}
}


bool Input::IsKeyDown(SDL_Scancode key)
{
	if (!Input::keyboardState)
		return false;

	if (Input::keyboardState[key])
		return true;
	return false;
}


bool Input::IsKeyUp(SDL_Scancode key)
{
	if (!Input::keyboardState)
		return false;

	if (Input::keyboardState[key])
		return false;
	return true;
}


bool Input::WasKeyDown(SDL_Scancode key)
{
	if (!Input::lastKeyboardState || !Input::keyboardState)
		return false;

	if (Input::lastKeyboardState[key] && !Input::keyboardState[key])
		return true;
	return false;
}


bool Input::WasKeyUp(SDL_Scancode key)
{
	if (!Input::lastKeyboardState || !Input::keyboardState)
		return false;

	if (Input::lastKeyboardState[key] && !Input::keyboardState[key])
		return false;
	return true;
}