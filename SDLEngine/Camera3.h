#include <iostream>
#include <math.h>
#include <GLFW\glfw3.h>
#include <SDL\SDL.h>
#include <glm\glm.hpp>


class Camera3
{
protected:
	// Camera position
	glm::vec3 position;

	// Camera rotation
	glm::vec3 rotation;

	// Camera movement speed. When we call the move() function on a camera, it moves using these speeds
	glm::vec3 speed;

	float movementSpeedFactor; // Controls how fast the camera moves
	float pitchSensitivity;    // Controls how sensitive mouse movements affect looking up and down
	float yawSensitivity;      // Controls how sensitive mouse movements affect looking left and right

								// Window size in pixels and where the midpoint of it falls
	int windowWidth;
	int windowHeight;
	int windowMidX;
	int windowMidY;

	// Method to set some reasonable default values. For internal use by the class only.
	void initCamera();

public:
	static const double TO_RADS; // The value of 1 degree in radians

								 // Holding any keys down?
	bool holdingForward;
	bool holdingBackward;
	bool holdingLeftStrafe;
	bool holdingRightStrafe;

	// Constructor
	Camera3(int theWindowWidth, int theWindowHeight);

	// Destructor
	~Camera3();

	// Mouse movement handler to look around
	void handleMouseMove(int mouseX, int mouseY);

	// Method to convert an angle in degress to radians
	const double toRads(const double &angleInDegrees) const;

	// Method to move the camera based on the current direction
	void move(double deltaTime);

	// --------------------------------- Inline methods ----------------------------------------------

	// Setters to allow for change of vertical (pitch) and horizontal (yaw) mouse movement sensitivity
	float getPitchSensitivity() { return pitchSensitivity; }
	void  setPitchSensitivity(float value) { pitchSensitivity = value; }
	float getYawSensitivity() { return yawSensitivity; }
	void  setYawSensitivity(float value) { yawSensitivity = value; }

	// Position getters
	glm::vec3 getPosition() const { return position; }
	float getXPos()           const { return position.x; }
	float getYPos()           const { return position.y; }
	float getZPos()           const { return position.z; }

	// Rotation getters
	glm::vec3 getRotation()	   const { return rotation; }
	float getXRot()           const { return rotation.x; }
	float getYRot()           const { return rotation.y; }
	float getZRot()           const { return rotation.z; }
};
