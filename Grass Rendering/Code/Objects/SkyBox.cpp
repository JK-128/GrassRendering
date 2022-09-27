#include "SkyBox.h"

SkyBox::SkyBox(std::string path, std::string type) : Object()
{
    delete m_shader;
    m_shader = new Shader("Content/Shaders/skyboxVert.glsl", "Content/Shaders/skyboxFrag.glsl");

	m_elements  = false;
	m_normals   = false;

	m_vertices =
	{
          -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
	};

    m_triangleCount = 36;
	setup(108, 0, 3);

    std::vector<std::string> paths =
    {
        path + "/right"  + type,
        path + "/left"   + type,
        path + "/top"    + type,
        path + "/bottom" + type,
        path + "/front"  + type,
        path + "/back"   + type
    };

    m_cubemap = new CubeMap(paths);
}

SkyBox::~SkyBox()
{
    delete m_cubemap;
}

void SkyBox::draw()
{
	glDepthMask(GL_FALSE);

    m_shader->bind();

    glBindVertexArray(m_VAO);
    glActiveTexture(GL_TEXTURE0);
    m_cubemap->bind();

    glDrawArrays(GL_TRIANGLES, 0, 36);

	glDepthMask(GL_TRUE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}