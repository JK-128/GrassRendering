#include "Texture.h"

Texture::Texture(std::string path)
{
	m_path = path;

	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 0);

	if (!data)
	{
		logMessage("Path not found: " + path, "TXTR", 1);
		return;
	}

	GLenum format;
	if      (m_channels == 1) format = GL_RED;
	else if (m_channels == 3) format = GL_RGB;
	else if (m_channels == 4) format = GL_RGBA;
	else
	{
		logMessage("Attempting to create a texture with unsupported number of channels: " + std::to_string(m_channels), "TXTR", 1);
		return;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

unsigned int Texture::get()
{
	return m_texture;
}

void Texture::bind(int unit)
{
	if (unit > 16)
		logMessage("Utilising a high number of texture units.", "TXTR", 1);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}