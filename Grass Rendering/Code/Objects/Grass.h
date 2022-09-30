#pragma once
#include <random>

#include "Quad.h"

class Grass : public Object
{
private:
	Quad m_ground;

	std::vector<glm::vec3> m_positions;

	unsigned int m_posVBO = 0;

	int m_count   = 50;
	int m_density = 1;

public:
	Grass();

	void setupExtra();
	void draw();
	void setPositions();
	void updateCount(int count);
	void setColor(float r, float g, float b, float a);

	Shader* getShader();
};

