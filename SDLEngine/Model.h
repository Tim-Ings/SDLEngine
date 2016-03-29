#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Mesh.h"
#include "Texture.h"
#include "ShaderProgram.h"

struct MeshMaterial
{
	std::unique_ptr<Mesh> mesh;
	std::unique_ptr<Material> material;
};

class Model
{
public:
	Model(const std::string& fileName);
	~Model();

	void SetShader(ShaderProgram* shader) { this->shader = shader; }

	void Draw(Camera3* camera, const Transform& transform);

private:
	ShaderProgram* shader;
	std::vector<MeshMaterial*> layers;
};

