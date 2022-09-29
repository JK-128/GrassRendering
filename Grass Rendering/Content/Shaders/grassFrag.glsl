#version 460

out vec4 fragColor;

in float height;

void main()
{
	fragColor = vec4(mix(vec3(0.2, 0.35, 0.11), vec3(0.4, 0.7, 0.22), vec3(height)), 1.0);
}