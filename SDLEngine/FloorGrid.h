#pragma once
#include "Vertex.h"
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <SDL\SDL.h>
#include <vector>
#include "Camera3.h"
#include <glm\gtc\matrix_transform.hpp>
#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>


class FloorGrid
{
public:
	FloorGrid(glm::vec3 centre = glm::vec3(0.0f), int dim = 12000.0f, int spacing = 20.0f, Color color = { 255, 255, 255 });

	void Draw(Camera3* camera);

private:
	void GenerateVertexArrayObject();

private:
	int vertexCount;
	VertexPositionColor* vertexData;
	int* indexData;
	int indexCount;
	GLuint vertexArrayObjectID;
	GLuint vertexBuffer;
	GLuint indexBuffer;
	ShaderProgram* shader;
	GLuint shaderUniformLoc_model;
	GLuint shaderUniformLoc_view;
	GLuint shaderUniformLoc_projection;
	GLuint shaderAttribLoc_vertexPosition;
	GLuint shaderAttribLoc_vertexColor;
};