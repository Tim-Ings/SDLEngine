#version 450 core

in vec2 uv;
in vec4 tint;

out vec4 color;

uniform sampler2D sampler;

void main(void)
{
	color = texture(sampler, uv).rgba * tint;
}