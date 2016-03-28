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

	void Bind();
	void Unbind();

	void SetUniform(const std::string& name, GLuint value);
	void SetUniform(const GLuint& location, GLuint value);
	GLuint GetUniformLocation(const std::string& name);
	GLuint GetAttribLocation(const std::string& name);

private:
	GLuint Compile(const std::string& filePath, GLenum type);
	GLuint Link(GLuint vertexID, GLuint fragID);

private:
	GLuint programID;
};

