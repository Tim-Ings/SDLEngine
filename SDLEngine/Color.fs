#version 450 core

in vec3 fragmentPosition;
in vec4 fragmentColor;

out vec4 color;

uniform float time;

void main(void)
{
	//color = fragmentColor + vec4((cos(time) + 1.0) * 0.5, (cos(time + 2.0) + 2.0) * 0.5, (sin(time) + 1.0) * 0.5, 0.0);
	//color = vec4(fragmentColor.r * (cos((fragmentPosition.x + time) * 0.5) + 1.0) * 0.5, 
	//			 fragmentColor.g * (cos((fragmentPosition.y + time + 2) * 0.5) + 1.0) * 0.5,
	//			 fragmentColor.b * (cos((fragmentPosition.z + time + 5) * 0.5) + 1.0) * 0.5, 1.0);
	color = fragmentColor;
}