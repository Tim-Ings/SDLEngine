#version 450 core

in vec2 textureCoord;

out vec4 color;

uniform sampler2D sampler;

void main(void)
{
	color = texture(sampler, vec2(textureCoord.x, -textureCoord.y)).rgba;
}