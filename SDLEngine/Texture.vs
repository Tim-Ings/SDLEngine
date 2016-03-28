#version 450 core

in vec3 vertexPosition;
in vec2 vertexUV;

out vec2 uv;
out vec4 tint;

uniform vec4 colorTint = vec4(1);
uniform mat4 transform = mat4(1);

uniform mat4 projection = mat4(1);
uniform mat4 view = mat4(1);
uniform mat4 model = mat4(1);


void main(void)
{
	gl_Position = projection * view * model * vec4(vertexPosition, 1);

	tint = colorTint;

    uv = vertexUV;
}