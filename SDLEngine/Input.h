#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <SDL\SDL.h>
#include <algorithm>
#include <glm\glm.hpp>

class Input
{
public:
	static void Update();
	static bool IsKeyDown(SDL_Scancode key);
	static bool IsKeyUp(SDL_Scancode key);
	static bool WasKeyDown(SDL_Scancode key);
	static bool WasKeyUp(SDL_Scancode key);

	static glm::vec2 GetMousePos() { return glm::vec2(mouseX, mouseY); }

private:
	static Uint8* Input::keyboardState;
	static Uint8* Input::lastKeyboardState;
	
	static int mouseX;
	static int mouseY;
	static bool mouseButtons[4];
};

