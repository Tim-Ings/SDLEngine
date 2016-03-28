#version 450 core

layout(location = 0) in vec3 position;

uniform mat4 modelViewProjection = mat4(1);

void main(void)
{
	gl_Position = modelViewProjection * vec4(position, 1);
}