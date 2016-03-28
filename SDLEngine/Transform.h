#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "camera3.h"

struct Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f))
	{
		this->position = pos;
		this->rotation = rot;
		this->scale = scale;
	}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate(position);
		glm::mat4 scaleMat = glm::scale(scale);
		glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return posMat * rotMat * scaleMat;
	}

	inline glm::mat4 GetModelViewProjection(const Camera3& camera) const
	{
		glm::mat4 vp = camera.GetViewProjection();
		glm::mat4 m = GetModel();
		return vp * m;
	}

	inline glm::vec3* GetPos() { return &position; }
	inline glm::vec3* GetRot() { return &rotation; }
	inline glm::vec3* GetScale() { return &scale; }

	inline void SetPos(glm::vec3& pos) { this->position = pos; }
	inline void SetRot(glm::vec3& rot) { this->rotation = rot; }
	inline void SetScale(glm::vec3& scale) { this->scale = scale; }

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};
