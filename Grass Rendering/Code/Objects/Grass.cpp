#include "Grass.h"

Grass::Grass() : Object()
{
	srand(time(NULL));

	delete m_shader;
	m_shader = new Shader("Content/Shaders/grassVert.glsl", "Content/Shaders/grassFrag.glsl");

	m_elements = true;
	m_normals = false;
	m_texCoords = false;

	m_vertices =
	{
		 0.00f,  0.10f, 1.0f,
		 0.05f,  -0.05f, 0.01f,
		 0.05f, -0.05f, 0.0f,
		-0.05f, -0.05f, 0.0f,
		-0.05f,  -0.05f, 0.01f
	};

	m_indices =
	{
		0, 1, 4,
		1, 2, 4,
		2, 3, 4
	};

	for (int y = -m_count; y < m_count; y += m_density)
	{
		for (int x = -m_count; x < m_count; x += m_density)
		{
			float randomOffsetX = (rand() % 100) / 300.0f;
			float randomOffsetZ = (rand() % 100) / 300.0f;
			float randomOffsetY = (rand() % 100) / 100.0f;

			glm::vec3 offset = glm::vec3(0.0f);

			offset.x = (float)x * m_spacingX + randomOffsetX;
			offset.z = (float)y * m_spacingZ + randomOffsetZ;
			offset.y = randomOffsetY;

			m_positions.push_back(offset);
		}
	}

	logMessage("Number of positions: " + std::to_string(m_positions.size()), "GRSS");

	setup(15, 9, 3);

	m_shader->bind();

	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_posVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_posVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_positions.size(), &m_positions[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	//glGenBuffers(1, &m_rotVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, m_rotVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_rotations.size(), &m_rotations[0], GL_STATIC_DRAW);
	
	//glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
	//glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(1, 1);
	//glVertexAttribDivisor(2, 1);
	glBindVertexArray(0);
}

void Grass::draw()
{
	m_shader->bind();
	m_shader->setF("time", glfwGetTime());

	glBindVertexArray(m_VAO);
	glDrawElementsInstanced(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0, m_positions.size());
	glBindVertexArray(0);
}