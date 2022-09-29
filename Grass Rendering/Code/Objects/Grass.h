#pragma once
#include <random>

#include "Quad.h"

class Grass : public Object
{
private:
	std::vector<glm::vec3> m_positions;
	std::vector<glm::mat4> m_rotations;

	unsigned int m_posVBO = 0;
	unsigned int m_rotVBO = 0;

	int m_count   = 500;
	int m_density = 1;

	float m_spacingX = 0.3f;
	float m_spacingZ = 0.05f;

	float m_offset  = 10.0f;

public:
	Grass();

	void draw();
};

