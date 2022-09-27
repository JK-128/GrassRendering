#pragma once
#include "Quad.h"

class GrassBlade : public Object
{
private:
	Quad m_blade;

public:
	GrassBlade();

	void updateView(glm::mat4 view);
	void draw();
};

