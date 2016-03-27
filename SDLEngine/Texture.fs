#version 450 core

in vec2 uv;

out vec4 color;

uniform sampler2D sampler;

void main(void)
{
	color = texture(sampler, uv).rgba;
	//color = vec4(1, 1, 1, 1);
}