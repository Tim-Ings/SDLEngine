#version 450

layout(location = 0) in vec4 fragmentColor;

out vec4 color;

void main(void)
{
	color = fragmentColor;
}