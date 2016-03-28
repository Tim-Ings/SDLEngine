#pragma once
#include <GL\glew.h>
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <string>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <math.h>
#include <algorithm>
#include <vector>
#include <fbxsdk.h>
#include "ShaderProgram.h"
#include "Camera3.h"
#include "Error.h"
#include "Vertex.h"


class Model
{
public:
	Model(const std::string& path);
	~Model();

	std::string GetName() { return name; }

	void Draw(Camera3* cam, const glm::vec3& pos);

private:
	void LoadModel(std::string file);
	void GenerateBuffers();
	void GenerateVertexArrayObject();
	void MapShaderAttributes();
	void Unload();

private:
	std::string name;
	ShaderProgram* shader;
	GLuint textureID;
	GLuint vertexArrayObjectID;

	// data
	FbxScene* fbxScene;
	std::vector<VertexPositionColor> vertexData;
	std::vector<int> indexData;
	int indexCount;

	// buffers
	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint uvBuffer;

	// shader attrib locations
	GLuint shaderUniformLoc_model;
	GLuint shaderUniformLoc_view;
	GLuint shaderUniformLoc_projection;
	GLuint shaderAttribLoc_vertexPosition;
	GLuint shaderAttribLoc_vertexColor;
};

