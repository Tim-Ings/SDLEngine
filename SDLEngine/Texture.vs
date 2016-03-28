#version 450 core

in vec3 vertexPosition;
in vec2 vertexUV;

out vec2 uvCoord;

uniform vec4 colorTint = vec4(1);
uniform mat4 transform = mat4(1);

layout(location = 0) uniform mat4 modelViewProjection = mat4(1);

void main(void)
{
	gl_Position = modelViewProjection * vec4(vertexPosition, 1);

    uvCoord = vertexUV;
}