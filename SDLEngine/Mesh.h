#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Vertex.h"
#include "ObjLoader.h"

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB
};

class Mesh
{
public:
	Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals, std::vector<int> indices);
	~Mesh();

	void Draw();

private:
	static const unsigned int NUM_BUFFERS = 4;

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	unsigned int numIndices;
};
