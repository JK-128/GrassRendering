#include "Quad.h"

Quad::Quad() : Object()
{
	m_elements  = true;
	m_normals   = false;
	m_texCoords = false;

	m_vertices =
	{
		 0.0f,  1.0f, 0.0f,
		 0.1f,  0.3f, 0.0f, //1.0f, 1.0f,
		 0.1f, -0.5f, 0.0f, //1.0f, 0.0f,
		-0.1f, -0.5f, 0.0f, //0.0f, 0.0f,
		-0.1f,  0.3f, 0.0f //0.0f, 1.0f
	};

	m_indices =
	{
		0, 1, 4,
		1, 2, 4,
		2, 3, 4
	};

	setup(15, 9, 3);
}