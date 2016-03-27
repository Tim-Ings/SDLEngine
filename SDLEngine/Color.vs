#version 450 core

in vec3 vertexPosition;
in vec4 vertexColor;

out vec3 fragmentPosition;
out vec4 fragmentColor;

uniform mat4 model = mat4(1);
uniform mat4 view = mat4(1);
uniform mat4 projection = mat4(1);


void main(void)
{
	gl_Position = projection * view * model * vec4(vertexPosition, 1);
	fragmentColor = vertexColor;
}