#include "GrassBlade.h"


GrassBlade::GrassBlade() : Object()
{
	m_blade.scale(0.05f, 0.25f, 1.0f);
}

void GrassBlade::updateView(glm::mat4 view)
{
	m_blade.updateView(view);
}

void GrassBlade::draw()
{
	m_blade.draw();
}