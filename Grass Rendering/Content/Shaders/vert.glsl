#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinates;

out vec2 texCoords;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
	texCoords = textureCoordinates;

	gl_Position = projection * view * model * vec4(position, 1.0);
}