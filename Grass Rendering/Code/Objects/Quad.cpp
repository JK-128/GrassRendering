#include "Quad.h"

Quad::Quad() : Object()
{
	m_elements  = true;
	m_normals   = false;
	m_texCoords = true;

	m_vertices =
	{
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	m_indices =
	{
		0, 1, 3,
		1, 2, 3
	};

	setup(20, 6, 5);
}