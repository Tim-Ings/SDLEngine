#include "Camera3.h"



Camera3::Camera3(SDL_Window* window) :
	window(nullptr),
	windowWidth(0),
	windowHeight(0),
	warpMouse(true),
	position(glm::vec3(0.0f, 1.0f, 3.0f)),
	front(glm::vec3(0.0f)),
	up(VEC3_UP),
	right(VEC3_RIGHT),
	worldUp(VEC3_UP),
	yaw(-90.0f),
	pitch(0.0f),
	movementSpeed(3.0f),
	mouseSensitivity(0.25f),
	zoom(45.0f),
	constrainPitch(true)
{
	this->window = window;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	if (windowWidth == 0 || windowHeight == 0)
		fatalError("Invalid window for camera3");
	CalculateVectors();
}


Camera3::~Camera3()
{
	
}


void Camera3::LookAt(glm::vec3 target)
{

}


void Camera3::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;

	printf("camera processing keyboard %d\n", direction);
}


// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera3::ProcessMouseMovement(const glm::vec2& newMousePos)
{
	glm::vec2 mouseDelta = newMousePos - oldMousePosition;

	float xoffset = mouseDelta.x * mouseSensitivity;
	float yoffset = mouseDelta.x * mouseSensitivity;

	printf("camera processing mouse %f %f\n", xoffset, yoffset);

	yaw += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	if (warpMouse)
		SDL_WarpMouseInWindow(window, windowWidth / 2, windowHeight / 2);

	oldMousePosition = newMousePos;

	// Update Front, Right and Up Vectors using the updated Eular angles
	CalculateVectors();
}


// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera3::ProcessMouseScroll(float yoffset)
{
	if (zoom >= 1.0f && zoom <= 45.0f)
		zoom -= yoffset;
	if (zoom <= 1.0f)
		zoom = 1.0f;
	if (zoom >= 45.0f)
		zoom = 45.0f;
}


void Camera3::CalculateVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, front));
}


void Camera3::Update()
{
	view = glm::lookAt(position, position + front, up);
}