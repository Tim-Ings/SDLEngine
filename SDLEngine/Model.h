#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Mesh.h"
#include "Texture.h"
#include "ShaderProgram.h"

struct ModelLayer
{
	GLuint indexBufferID;
	unsigned int numIndices;
	Material* material;
};

class Model
{
public:
	Model(const std::string& fileName);
	~Model();

	void SetShader(ShaderProgram* shader) { this->shader = shader; }

	void Draw(Camera3* camera, const Transform& transform);

private:
	static const unsigned int NUM_BUFFERS = 3;

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];

	ShaderProgram* shader;
	std::vector<ModelLayer*> layers;
};

