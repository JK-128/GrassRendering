#include "CubeMap.h"

CubeMap::CubeMap(std::vector<std::string>* paths)
{
	stbi_set_flip_vertically_on_load(false);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

	for (int i = 0; i < (*paths).size(); i++)
	{
		unsigned char* data = stbi_load((*paths).at(i).c_str(), &m_width, &m_height, &m_channels, 0);
		
		if(data)
		{
			GLenum format;
			if      (m_channels == 1) format = GL_RED;
			else if (m_channels == 3) format = GL_RGB;
			else if (m_channels == 4) format = GL_RGBA;
			else
				logMessage("Attempting to create a texture with unsupported number of channels.", "CTXT", 1);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			logMessage("Path not found: " + (*paths).at(i), "CTXT", 1);
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

unsigned int CubeMap::get()
{
	return m_texture;
}

void CubeMap::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
}

CubeMap::~CubeMap()
{
	glDeleteTextures(1, &m_texture);
}