#version 450 core

in vec3 vertexPosition;
in vec2 vertexUV;

out vec2 uv;

void main(void)
{
	gl_Position.xyz = vertexPosition;
	gl_Position.w = 1.0;

    uv = vertexUV;
}