#pragma once
#include "../Utility/Logger.h"
#include "../../Dependencies/stb_image.h"
#include <glad/glad.h>

class Texture
{
private:
	int m_width    = 0;
	int m_height   = 0;
	int m_channels = 0;

	std::string m_path;

	unsigned int m_texture;

public:
	Texture(std::string path);

	unsigned int get();

	void bind(int unit = 0);
};

