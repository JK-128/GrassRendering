#version 460

out vec4 fragColor;

in float height;

uniform vec3 tipColor;
uniform vec3 baseColor;

uniform float weight = 1.0f;

void main()
{
	fragColor = vec4(mix(baseColor, tipColor, vec3(height)), 1.0);
}