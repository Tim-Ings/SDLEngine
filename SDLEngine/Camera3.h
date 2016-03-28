#pragma once
#include <iostream>
#include <math.h>
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Error.h"

#define VEC3_UP glm::vec3(0.0f, 1.0f, 0.0f)
#define VEC3_DOWN glm::vec3(0.0f, -1.0f, 0.0f)
#define VEC3_RIGHT glm::vec3(1.0f, 0.0f, 0.0f)
#define VEC3_LEFT glm::vec3(-1.0f, 0.0f, 0.0f)
#define VEC3_FORWARD glm::vec3(0.0f, 0.0f, -1.0f)
#define VEC3_BACKWARD glm::vec3(0.0f, 0.0f, 1.0f)
#define MAT4_I glm::mat4(1.0f)

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera3
{
public:
	Camera3(SDL_Window* window);
	~Camera3();

	void SetWarpMouse(bool warp) { warpMouse = warp; }
	glm::mat4 GetTransformationMatrix() { return perspective * view; }
	glm::mat4 GetViewMatrix() { return view; }
	glm::mat4 GetPerspectiveMatrix() { return perspective; }

	void LookAt(glm::vec3 target);
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(const glm::vec2& newMousePos);
	void ProcessMouseScroll(float yoffset);
	void Update();

private:
	void CalculateVectors();

private:
	SDL_Window* window;
	int windowWidth;
	int windowHeight;
	bool warpMouse;
	glm::vec2 oldMousePosition;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	glm::mat4 view;
	glm::mat4 perspective;
	float fov;
	float yaw;
	float pitch;
	float movementSpeed;
	float mouseSensitivity;
	float zoom;
	bool constrainPitch;
};
