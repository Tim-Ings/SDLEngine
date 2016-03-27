#version 450 core

in vec3 vertexPosition;
in vec4 vertexColor;

out vec3 fragmentPosition;
out vec4 fragmentColor;

uniform float time;

void main(void)
{
	gl_Position.xyz = vertexPosition;
	gl_Position.w = 1.0;
	fragmentColor = vertexColor;
}