#include "ShaderProgram.h"



ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) :
	programID(0),
	attributeCount(0)
{
	GLuint vertexID = Compile(vertexPath, GL_VERTEX_SHADER);
	GLuint fragmentID = Compile(fragmentPath, GL_FRAGMENT_SHADER);

	programID = Link(vertexID, fragmentID);
}


ShaderProgram::~ShaderProgram()
{
}


GLuint ShaderProgram::Compile(const std::string& filePath, GLenum type)
{
	GLuint shaderID = glCreateShader(type);
	if (!shaderID)
		fatalError("FAILED: glCreateShader()");

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

	fclose(file);

	char const* fileContentsPtr = fileContents.c_str();
	glShaderSource(shaderID, 1, &fileContentsPtr, nullptr);
	glCompileShader(shaderID);

	GLint isCompiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(shaderID); // Don't leak the shader.

		printf("%s\n", &(errorLog[0]));
		fatalError("FAILED: Failed to compile shader: " + filePath);
		return 0;
	}

	return shaderID;
}


GLuint ShaderProgram::Link(GLuint vertexID, GLuint fragID)
{
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	GLuint program = glCreateProgram();

	//Attach our shaders to our program
	glAttachShader(program, vertexID);
	glAttachShader(program, fragID);

	//Link our program
	glLinkProgram(program);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(program);
		//Don't leak shaders either.
		glDeleteShader(vertexID);
		glDeleteShader(fragID);

		//Use the infoLog as you see fit.
		printf("%s\n", &(errorLog[0]));
		fatalError("FAILED: Failed to link shaders");

		//In this simple program, we'll just leave
		return 0;
	}

	//Always detach shaders after a successful link.
	glDetachShader(program, vertexID);
	glDetachShader(program, fragID);

	return program;
}


void ShaderProgram::Use()
{
	glUseProgram(programID);
	/*for (int i = 0; i < attributeCount; i++)
	{
		glEnableVertexAttribArray(i);
	}*/
}


void ShaderProgram::Disuse()
{
	for (int i = 0; i < attributeCount; i++)
	{
		glDisableVertexAttribArray(i);
	}
	glUseProgram(0);
}