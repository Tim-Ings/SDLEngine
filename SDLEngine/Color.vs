#version 450 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColor;

out vec3 fragmentPosition;
out vec4 fragmentColor;

uniform float time;

void main(void)
{
	gl_Position.xyz = vertexPosition;
	gl_Position.w = 1.0;
	fragmentColor = vertexColor;
}