#pragma once
#include <string>
#include <GL\glew.h>
#include "Error.h"
#include <vector>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
	~ShaderProgram();

	void Use();
	void Disuse();

	GLuint GetUniformLocation(const std::string& name);

private:
	GLuint Compile(const std::string& filePath, GLenum type);
	GLuint Link(GLuint vertexID, GLuint fragID);

private:
	GLuint programID;
	int attributeCount;
};

