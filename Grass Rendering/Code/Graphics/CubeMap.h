#pragma once
#include "Texture.h"

class CubeMap
{
private:
	int m_width    = 0;
	int m_height   = 0;
	int m_channels = 0;

	unsigned int m_texture;

public:
	CubeMap(std::vector<std::string> paths);

	unsigned int get();

	void bind();
};

