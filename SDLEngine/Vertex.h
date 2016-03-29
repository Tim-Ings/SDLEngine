#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal, const glm::vec4& color)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
		this->color = color;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }
	glm::vec4* GetColor() { return &color; }

	void SetPos(glm::vec3 p) { pos = p; }
	void SetTexCoord(glm::vec2 tc) { texCoord = tc; }
	void SetNormal(glm::vec3 n) { normal = n; }
	void SetColor(glm::vec4 c) { color = c; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
	glm::vec4 color;
};