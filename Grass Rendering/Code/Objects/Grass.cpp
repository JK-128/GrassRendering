#include "Grass.h"

Grass::Grass() : Object()
{
	srand(time(NULL));

	delete m_shader;
	m_shader = new Shader("Content/Shaders/grassVert.glsl", "Content/Shaders/grassFrag.glsl");

	m_elements = true;
	m_normals = false;
	m_texCoords = false;

	
	std::vector<float> vertices1 =
	{
		 0.000f, 0.50f, 0.000f,
		 0.025f, 0.00f, 0.000f,
		 0.000f, 0.00f, 0.025f,
		-0.025f, 0.00f, 0.000f,
	};

	std::vector<int> indices1 =
	{
		0, 1, 2,
		0, 2, 3
	};

	std::vector<float> vertices2 =
	{
		 0.00f, 0.50f, 0.00f,
		 0.025f, 0.25f, 0.025f,
		 0.00f, 0.00f, 0.00f,
		-0.025f, 0.25f, 0.025f
	};

	std::vector<int> indices2 =
	{
		0, 1, 2,
		0, 2, 3
	};

	std::vector<float> vertices3 =
	{
		 0.000f, 0.5f, 0.0f,
		 0.025f, 0.4f, 0.0f,
		 0.025f, 0.0f, 0.0f,
		-0.025f, 0.0f, 0.0f,
		-0.025f, 0.4f, 0.0f
	};

	std::vector<int> indices3 =
	{
		0, 1, 4,
		1, 2, 4,
		2, 3, 4
	};

	m_shapes.push_back(vertices1);
	m_shapes.push_back(vertices2);
	m_shapes.push_back(vertices3);

	m_tris.push_back(indices1);
	m_tris.push_back(indices2);
	m_tris.push_back(indices3);

	m_ground.scale(2.0f, 1.0f, 2.0f);
	m_ground.rotate('x', 90.0f);
	m_ground.setColor(color{ 0.2, 0.35, 0.11 });
	m_previousPos = glm::vec3(0.0f);

	setPositions();

	glGenBuffers(1, &m_posVBO);
	
	updateShape(0);

	updatePositions(glm::vec3(0.0f));
	setupExtra();
}

void Grass::updateCount(int count)
{
	m_count = count;

	setPositions();
	updatePositions(glm::vec3(0.0f), true);

	m_previousPos = glm::vec3(0.0f);
}

void Grass::updateShape(int selection)
{
	if (selection < 0 || selection > m_shapes.size() - 1)
		return;

	m_vertices.clear();
	m_vertices = m_shapes[selection];

	m_indices.clear();
	m_indices = m_tris[selection];

	setup(m_vertices.size(), m_indices.size(), 3);
}

void Grass::setupExtra()
{
	m_shader->bind();

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_posVBO);

	if (m_newPositions.size() == 0)
		glInvalidateBufferData(GL_ARRAY_BUFFER);
	else
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_newPositions.size(), &m_newPositions[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(1, 1);

	glBindVertexArray(0);
}

void Grass::draw()
{
	if (m_newPositions.size() < 10)
		return;

	m_shader->bind();
	m_shader->setF("time", glfwGetTime());

	glBindVertexArray(m_VAO);
	glDrawElementsInstanced(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0, m_newPositions.size());
	glBindVertexArray(0);
}

Shader* Grass::getShader()
{
	return m_shader;
}

void Grass::setPositions()
{
	m_positions.clear();

	glm::vec3 offset = glm::vec3(0.5f) * m_ground.getScale();
	glm::vec3 gPos   = m_ground.getPosition() - offset;
	glm::vec3 ePos   = m_ground.getPosition() + offset;

	glm::vec3 diff   = ePos - gPos;

	float density = diff.x / m_count;

	for (int i = 0; i < m_count; i++)
	{
		for (int j = 0; j < m_count; j++)
		{
			float randomOffsetX = (rand() % 100) / 300.0f;
			float randomOffsetZ = (rand() % 100) / 300.0f;
			float randomOffsetY = (rand() % 100) / 100.0f;
			
			randomOffsetX -= 0.08333f;
			randomOffsetZ -= 0.08333f;

			glm::vec3 newPos = gPos + glm::vec3(i * density, 0.0f, j * density);

			if (!m_gridAligned)
			{
				newPos.x += randomOffsetX;
				newPos.z += randomOffsetZ;
			}

			newPos.y  = randomOffsetY;

			m_positions.push_back(newPos);
		}
	}

	logMessage("No. blades: " + std::to_string(m_positions.size()), "GRSS");
}

void Grass::setColor(float r, float g, float b, float a)
{
	m_ground.setColor(r, g, b, a);
}

void Grass::setGridAligned(bool status)
{
	m_gridAligned = status;
}

void Grass::setPosition(float x, float y, float z)
{
	m_ground.setPosition(x, y, z);

	setPositions();
	setupExtra();
}

void Grass::updatePositions(glm::vec3 position, bool countChanged)
{
	glm::vec3 diff = abs(position - m_previousPos);

	if (diff.x > 0.2f || diff.y > 0.2f || diff.z > 0.2f || m_first || countChanged)
	{
		m_first = false;

		if(!countChanged)
			m_previousPos = position;

		m_newPositions.clear();

		for (int i = 0; i < m_positions.size(); i++)
		{
			if (isInRange(m_positions[i], position))
				m_newPositions.push_back(m_positions[i]);
		}

		if (m_newPositions.size() == m_positions.size() && !countChanged)
			return;

		setupExtra();
	}
}

bool Grass::isInRange(glm::vec3 v1, glm::vec3 v2)
{
	float x = (v1.x - v2.x) * (v1.x - v2.x);
	float y = (v1.y - v2.y) * (v1.y - v2.y);
	float z = (v1.z - v2.z) * (v1.z - v2.z);

	if (x + y + z < 20.0f)
		return true;

	return false;
}

int Grass::getShapesCount()
{
	return m_shapes.size();
}