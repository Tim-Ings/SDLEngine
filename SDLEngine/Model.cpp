#include "Model.h"



Model::Model(const std::string& meshPath, const std::string& texturePath) :
	mesh(nullptr),
	texture(nullptr)
{
	mesh.reset(new Mesh(meshPath));
	texture.reset(new Texture(texturePath));
}


Model::Model(Mesh* mesh, Texture* texture) :
	mesh(nullptr),
	texture(nullptr)
{
	this->mesh.reset(mesh);
	this->texture.reset(texture);
}


Model::~Model()
{
}


void Model::Draw(Camera3* camera, const Transform& transform)
{
	texture->Bind();
	shader->Bind();
	{
		shader->Update(transform, *camera);
		mesh->Draw();
	}
	shader->Unbind();
}