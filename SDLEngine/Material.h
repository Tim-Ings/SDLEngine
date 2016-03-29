#pragma once
#include <glm\glm.hpp>
#include <memory>
#include <string>
#include "Texture.h"

enum MaterialIllum
{
	MATERIALILLUM_FLAT,
	MATERIALILLUM_SPECULAR
};


class Material
{
public:
	//Material(std::string name, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, MaterialIllum illum, float shininess, float transparency, std::string textureFilePath);
	Material() {}
	~Material() {}

public:
	std::string name;
	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	MaterialIllum illum;
	float shininess;
	float transparency;
	std::unique_ptr<Texture> texture;
};

