#include "Model.h"
#include <algorithm>
#include "SplitString.h"


Model::Model(const std::string& fileName)
{
	// load obj data from file
	ObjModel* objModel = new ObjModel(fileName);
	
	// build index buffers for each material
	for (int matI = 0; matI < objModel->materials.size(); matI++)
	{
		Material* mat = objModel->materials[matI];
		std::vector<int> posInices;

		for (int i = 0; i < objModel->indices.size(); i++)
		{
			ObjModelIndex objmi = objModel->indices[i];
			if (objmi.material == matI)
				posInices.push_back(objmi.position);
		}

		GLuint indexBufferID = NULL;
		// bind and fill the index buffer
		glGenBuffers(1, &indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(posInices[0]) * posInices.size(), &posInices[0], GL_STATIC_DRAW);
		}

		ModelLayer* ml = new ModelLayer();
		ml->material = mat;
		ml->indexBufferID = indexBufferID;
		ml->numIndices = posInices.size();
		layers.push_back(ml);
	}

	// create buffers for global data
	// create and bind a new vao
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	{
		// create buffers for model data
		glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

		// bind and fill the position vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(objModel->positions[0]) * objModel->positions.size(), &objModel->positions[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		// bind and fill the texture coords vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(objModel->textures[0]) * objModel->textures.size(), &objModel->textures[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}

		// bind and fill the normals vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(objModel->normals[0]) * objModel->normals.size(), &objModel->normals[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}
	}
	glBindVertexArray(NULL);
}


Model::~Model()
{
}


void Model::Draw(Camera3* camera, const Transform& transform)
{
	glBindVertexArray(vertexArrayObject);
	{
		for (int i = 0; i < layers.size(); i++)
		{
			ModelLayer* ml = layers[i];
			ml->material->texture->Bind();
			//mm->material->shader->Bind(); // do this after we have a shader for each material implemented
			shader->Bind();					// but for now just use a simple global shader
			{
				shader->Update(transform, camera);

				// bind index buffer for layer
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ml->indexBufferID);
				{
					// draw triangles in mesh
					glDrawElementsBaseVertex(GL_TRIANGLES, ml->numIndices, GL_UNSIGNED_INT, 0, 0);
				}
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
			}
			shader->Unbind();
		}
	}
	glBindVertexArray(NULL);
}