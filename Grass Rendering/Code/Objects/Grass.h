#pragma once
#include <random>

#include "Quad.h"

class Grass : public Object
{
private:
	Quad m_ground;

	std::vector<glm::vec3> m_positions;
	std::vector<glm::vec3> m_newPositions;

	glm::vec3 m_previousPos;

	unsigned int m_posVBO = 0;

	int m_count   = 50;
	int m_density = 1;

	float m_randomX = 0.0f;
	float m_randomY = 0.0f;
	float m_randomZ = 0.0f;

	bool m_gridAligned = true;
	bool m_first = true;

public:
	Grass();

	void setupExtra();
	void draw();
	void setPosition(float x, float y, float z);
	void setPositions();
	void updateCount(int count);
	void setColor(float r, float g, float b, float a);
	void setGridAligned(bool status);
	void updatePositions(glm::vec3 position = glm::vec3(0.0f), bool countChanged = false);

	bool isInRange(glm::vec3 v1, glm::vec3 v2);

	Shader* getShader();
};

