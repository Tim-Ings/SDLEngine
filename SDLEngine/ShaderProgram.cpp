#include "ShaderProgram.h"
#include "Error.h"
#include <vector>
#include <glm\gtc\type_precision.hpp>


ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) :
	programID(0)
{
	// compile the vertex shader
	GLuint vertexID = Compile(vertexPath, GL_VERTEX_SHADER);

	// compile the fragment shader
	GLuint fragmentID = Compile(fragmentPath, GL_FRAGMENT_SHADER);

	// link the shaders
	programID = Link(vertexID, fragmentID);
}


ShaderProgram::~ShaderProgram()
{
}


GLuint ShaderProgram::Compile(const std::string& filePath, GLenum type)
{
	// create an ogl shader
	GLuint shaderID = glCreateShader(type);
	if (!shaderID)
		fatalError("FAILED: glCreateShader()");

	// read file contents into a string
	FILE* file;
	fopen_s(&file, filePath.c_str(), "r");
	if (!file)
		fatalError("FAILED: unable to open file: " + filePath);

	std::string fileContents;
	char* line = new char[BUFSIZ];
	while (fgets(line, BUFSIZ, file))
	{
		fileContents += line;
		fileContents += "\n";
	}

	// free resources
	fclose(file);

	// pass pointer to shader string and compile
	char const* fileContentsPtr = fileContents.c_str();
	glShaderSource(shaderID, 1, &fileContentsPtr, nullptr);
	glCompileShader(shaderID);

	// check for errors
	GLint isCompiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		// get compilation log
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// the maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(shaderID); // free resources

		// report the error
		printf("%s\n", &(errorLog[0]));
		fatalError("FAILED: Failed to compile shader: " + filePath);
		return NULL;
	}

	return shaderID;
}


GLuint ShaderProgram::Link(GLuint vertexID, GLuint fragID)
{
	// create a new ogl program
	GLuint program = glCreateProgram();

	// attatch compiled shaders
	glAttachShader(program, vertexID);
	glAttachShader(program, fragID);
	{
		// link attatched shaders
		glLinkProgram(program);

		// check for errors
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			// get linker log
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// the maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &errorLog[0]);

			// free resources
			glDeleteProgram(program);
			glDeleteShader(vertexID);
			glDeleteShader(fragID);

			// report the error
			printf("%s\n", &(errorLog[0]));
			fatalError("FAILED: Failed to link shaders");
			return NULL;
		}
	}
	// detatch shaders
	glDetachShader(program, vertexID);
	glDetachShader(program, fragID);

	return program;
}


void ShaderProgram::Update(const Transform& transform, Camera3* camera)
{
	//// uniform mat4 projectionMatrix;
	//// uniform mat4 modelMatrix;
	//// uniform mat4 viewMatrix;
	//// uniform mat4 normalMatrix;

	//glm::mat4 projectionMatrix = camera->GetProjection();
	//glm::mat4 modelMatrix = transform.GetModel();
	//glm::mat4 viewMatrix = camera->GetView();
	//glm::mat4 normalMatrix = MAT4_I;

	//glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(projectionMatrix)); // uniform mat4 projectionMatrix;
	//glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(modelMatrix)); // uniform mat4 modelMatrix;
	//glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(viewMatrix)); // uniform mat4 viewMatrix;
	//glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(normalMatrix)); // uniform mat4 viewMatrix;

	glm::mat4 mvp = transform.GetModelViewProjection(*camera);
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mvp)); // layout(location = 0) in mat4 mvp;
}


void ShaderProgram::Bind()
{
	// bind the linked program
	glUseProgram(programID);
}


void ShaderProgram::Unbind()
{
	// unbind the current program
	glUseProgram(NULL);
}


void ShaderProgram::SetUniform(const std::string& name, GLuint value)
{
	Bind();
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}


void ShaderProgram::SetUniform(const GLuint& location, GLuint value)
{
	Bind();
	glUniform1i(location, value);
}


GLuint ShaderProgram::GetUniformLocation(const std::string& name)
{
	GLuint locationID = glGetUniformLocation(programID, name.c_str());
	if (locationID == GL_INVALID_INDEX)
		fatalError("Uniform \"" + name + "\" not found in shader");
	return locationID;
}


GLuint ShaderProgram::GetAttribLocation(const std::string& name)
{
	GLuint locationID = glGetAttribLocation(programID, name.c_str());
	if (locationID == GL_INVALID_INDEX)
		fatalError("Attribute \"" + name + "\" not found in shader");
	return locationID;
}