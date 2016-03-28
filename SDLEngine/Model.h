#pragma once
#include <memory>
#include <string>
#include "Mesh.h"
#include "Texture.h"
#include "ShaderProgram.h"

class Model
{
public:
	Model(const std::string& modelPath, const std::string& texturePath);
	Model(Mesh* mesh, Texture* texture);
	~Model();

	void SetShader(ShaderProgram* shader) { this->shader = shader; }

	void Draw(Camera3* camera, const Transform& transform);

private:
	ShaderProgram* shader;
	std::unique_ptr<Mesh> mesh;
	std::unique_ptr<Texture> texture;
};

