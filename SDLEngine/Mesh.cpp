#include "mesh.h"
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>



Mesh::Mesh(const std::string& fileName)
{
	ObjModel* objModel = LoadObjModel("models/dwarf", "dwarf.obj");
	InitMesh(*objModel);
}


void Mesh::InitMesh(const ObjModel& model)
{
	numIndices = model.indices_vertex.size();

	// create and bind a new vao
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	{
		// create buffers for model data
		glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

		// bind and fill the position vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(model.vertices[0]) * model.vertices.size(), &model.vertices[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		// bind and fill the texture coords vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(model.textureCoords[0]) * model.textureCoords.size(), &model.textureCoords[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}

		// bind and fill the normals vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		// bind and fill the index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices_vertex[0]) * model.indices_vertex.size(), &model.indices_vertex[0], GL_STATIC_DRAW);
		}
	}
	glBindVertexArray(NULL);
}


Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	//// declare a new indexed model
	//ObjModel model;

	//// fill model with vertex data
	//for (unsigned int i = 0; i < numVertices; i++)
	//{
	//	model.vertices.push_back(*vertices[i].GetPos());
	//	model.textureCoords.push_back(*vertices[i].GetTexCoord());
	//	model.normals.push_back(*vertices[i].GetNormal());
	//}

	//// fill model with index data
	//for (unsigned int i = 0; i < numIndices; i++)
	//	model.indices.push_back(indices[i]);

	//// initialise the mesh
	//InitMesh(model);
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