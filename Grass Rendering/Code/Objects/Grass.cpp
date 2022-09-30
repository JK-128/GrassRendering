#include "Grass.h"

Grass::Grass() : Object()
{
	srand(time(NULL));

	delete m_shader;
	m_shader = new Shader("Content/Shaders/grassVert.glsl", "Content/Shaders/grassFrag.glsl");

	m_elements = true;
	m_normals = false;
	m_texCoords = false;

	/*
	m_vertices =
	{
		 0.00f,  0.10f, 1.0f,
		 0.05f,  -0.05f, 0.8f,
		 0.05f, -0.05f, 0.0f,
		-0.05f, -0.05f, 0.0f,
		-0.05f,  -0.05f, 0.8f
	};

	m_indices =
	{
		0, 1, 4,
		1, 2, 4,
		2, 3, 4
	};
	*/
	m_vertices =
	{
		 0.00f, 1.00f, 0.00f, //0
		 0.50f, 0.00f, 0.00f, //1
		 0.00f, 0.00f, 0.05f, //2
		-0.50f, 0.00f, 0.00f, //3
	};

	m_indices =
	{
		0, 1, 2,
		0, 2, 3
	};

	setPositions();

	logMessage("No. blades: " + std::to_string(m_positions.size()), "GRSS");

	setup(12, 6, 3);

	setupExtra();

	m_ground.scale(2.0f, 1.0f, 2.0f);
	m_ground.rotate('x', 90.0f);
	m_ground.setColor(color{ 0.2, 0.35, 0.11 });
}

void Grass::updateCount(int count)
{
	m_count = count;

	m_positions.clear();
	setPositions();
	setupExtra();
}

void Grass::setupExtra()
{
	m_shader->bind();

	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_posVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_posVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_positions.size(), &m_positions[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(1, 1);

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

Shader* Grass::getShader()
{
	return m_shader;
}

void Grass::setPositions()
{
	m_positions.clear();

	glm::vec3 gPos   = m_ground.getPosition() - glm::vec3(20.0f, 0.0f, 1.0f);
	glm::vec3 ePos   = glm::vec3(20.0f, 0.0f, -1.0f);
	glm::vec3 diff   = ePos - gPos;

	float density = diff.x / m_count;

	for (int i = 0; i < m_count; i++)
	{
		for (int j = 0; j < m_count; j++)
		{
			float randomOffsetX = (rand() % 100) / 300.0f;
			float randomOffsetZ = (rand() % 100) / 600.0f;
			float randomOffsetY = (rand() % 100) / 100.0f;
			
			randomOffsetX -= 0.08333f;
			randomOffsetZ -= 0.08333f;

			glm::vec3 newPos = gPos + glm::vec3(i * density, 0.0f, j * (density * 0.05));
			
			if (!m_gridAligned)
			{
				newPos.x += randomOffsetX;
				newPos.z += randomOffsetZ;
			}

			newPos.y  = randomOffsetY;

			m_positions.push_back(newPos);
		}
	}
}

void Grass::setColor(float r, float g, float b, float a)
{
	m_ground.setColor(r, g, b, a);
}

void Grass::setGridAligned(bool status)
{
	m_gridAligned = status;
}