#include "mesh.h"
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>



Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals, std::vector<int> indices)
{
	numIndices = indices.size();

	// create and bind a new vao
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	{
		// create buffers for model data
		glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

		// bind and fill the position vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * positions.size(), &positions[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		// bind and fill the texture coords vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(textures[0]) * textures.size(), &textures[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}

		// bind and fill the normals vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		// bind and fill the index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
		}
	}
	glBindVertexArray(NULL);
}


Mesh::~Mesh()
{
	// free memory
	glDeleteBuffers(NUM_BUFFERS, vertexArrayBuffers);
	glDeleteVertexArrays(1, &vertexArrayObject);
}


void Mesh::Draw()
{
	// bind vao
	glBindVertexArray(vertexArrayObject);
	{
		//glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
		// draw triangles in mesh
		glDrawElementsBaseVertex(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0, 0);
	}
	glBindVertexArray(NULL);
}