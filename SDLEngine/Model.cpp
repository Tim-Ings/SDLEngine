#include "Model.h"
#include <algorithm>
#include "SplitString.h"


Model::Model(const std::string& fileName)
{
	ObjModel* objModel = new ObjModel(fileName);
	
	// add a layer for each material
	for (int i = 0; i < objModel->materials.size(); i++)
	{
		
	}

	// populate each material layer with its indicies
	for (int matI = 0; matI < objModel->materials.size(); matI++)
	{
		Material* material = objModel->materials[matI];
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> textures;
		std::vector<glm::vec3> normals;
		std::vector<int> indices;

		for (int indexI = 0; indexI < objModel->indices_material.size(); indexI++)
		{
			if (objModel->indices_material[indexI] == matI)
			{
				positions.push_back(objModel->positions[indexI]);
				textures.push_back(objModel->textures[indexI]);
				normals.push_back(objModel->normals[indexI]);
				indices.push_back(objModel->indices_positions[indexI]);
			}
		}

		Mesh* mesh = new Mesh(positions, textures, normals, indices);

		MeshMaterial* mm = new MeshMaterial();
		mm->mesh.reset(mesh);
		mm->material.reset(material);

		layers.push_back(mm);
	}
}


Model::~Model()
{
}


void Model::Draw(Camera3* camera, const Transform& transform)
{
	for (int i = 0; i < layers.size(); i++)
	{
		MeshMaterial* mm = layers[i];
		mm->material->texture->Bind();
		//mm->material->shader->Bind(); // do this after we have a shader for each material implemented
		shader->Bind();					// but for now just use a simple global shader
		{
			shader->Update(transform, camera);
			mm->mesh->Draw();
		}
		shader->Unbind();
	}
}