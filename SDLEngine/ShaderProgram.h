#pragma once
#include <GL\glew.h>
#include <string>
#include "Transform.h"
#include "Camera3.h"

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
	~ShaderProgram();

	void Update(const Transform& transform, const Camera3& camera);
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
	static const unsigned int NUM_UNIFORMS = 3;

	GLuint programID;
	GLuint uniformLocations[NUM_UNIFORMS];
};

