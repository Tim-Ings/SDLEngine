#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <SDL\SDL.h>
#include <algorithm>
#include <glm\glm.hpp>


enum MouseButton
{
	MOUSE_LEFT = 0,
	MOUSE_MIDDLE = 1,
	MOUSE_RIGHT = 2,
};


class Input
{
public:
	static void Update();
	static bool IsKeyDown(SDL_Scancode key);
	static bool IsKeyUp(SDL_Scancode key);
	static bool WasKeyDown(SDL_Scancode key);
	static bool WasKeyUp(SDL_Scancode key);
	static bool IsMouseDown(MouseButton mouseButton);
	static bool IsMouseUp(MouseButton mouseButton);
	static bool WasMouseDown(MouseButton mouseButton);
	static bool WasMouseUp(MouseButton mouseButton);

	static glm::vec2 GetMousePos() { return glm::vec2(mouseX, mouseY); }

private:
	static bool Input::keyboardState[BUFSIZ];
	static bool Input::lastKeyboardState[BUFSIZ];
	
	static int mouseX;
	static int mouseY;
	static bool mouseButtons[3];
	static bool lastMouseButtons[3];
};

