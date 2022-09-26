#version 460 core

in vec2 texCoords;

out vec4 fragColor;

uniform vec4 color;
uniform sampler2D tex;
uniform bool textured = false;

void main()
{
	if(textured == true)
	{
		fragColor = texture(tex, texCoords) * color;
	}
	else
	{
		fragColor = color;
	}
}