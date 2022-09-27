#include "Object.h"

Object::Object()
{
	m_shader = new Shader("Content/Shaders/vert.glsl", "Content/Shaders/frag.glsl");

	m_transform.model = glm::mat4(1.0f);
	m_transform.view  = glm::mat4(1.0f);
	m_transform.scale = glm::vec3(1.0f);

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	setColor(m_color);
}

Object::~Object()
{
	delete m_shader;
}

color Object::getColor()
{
	return m_color;
}

void Object::setup(int vertices, int indices, int offset)
{
	m_shader->bind();

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);

	if (m_elements)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices * sizeof(int), &m_indices[0], GL_STATIC_DRAW);
	}

	//Vertex Positions:
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, offset * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	if (m_texCoords)
	{
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, offset * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	update();
}

void Object::draw()
{
	if (!m_visible) return;

	m_shader->bind();

	glBindVertexArray(m_VAO);

	if (m_textured)
		m_texture->bind();

	if (m_elements)
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, m_triangleCount);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Object::move(float x, float y, float z)
{
	m_transform.model = glm::translate(m_transform.model, glm::vec3(x, y, z));

	glm::mat4 mT = m_transform.model;
	m_transform.position = glm::vec3(mT[3][0], mT[3][1], mT[3][2]);

	update();
}

void Object::move(glm::vec3 offset)
{
	move(offset.x, offset.y, offset.z);
}

void Object::rotate(char axis, float amount)
{
	float angle = glm::radians(amount);
	
	glm::vec3 rotAxis;

	if (axis == 'x')
	{
		rotAxis = glm::vec3(1.0f, 0.0f, 0.0f);
		m_transform.rotation.x += amount;
	}
	else if (axis == 'y')
	{
		rotAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		m_transform.rotation.y += amount;
	}
	else if (axis == 'z')
	{
		rotAxis = glm::vec3(0.0f, 0.0f, 1.0f);
		m_transform.rotation.z += amount;
	}
	else
	{
		logMessage("Attempting to rotate an object around a non-existent axis: " + axis, "OBJT", 1);
		return;
	}

	m_transform.model = glm::rotate(m_transform.model, angle, rotAxis);

	update();
}

void Object::scale(float x, float y, float z)
{
	m_transform.model = glm::scale(m_transform.model, glm::vec3(x, y, z));

	m_transform.scale.x *= x;
	m_transform.scale.y *= y;
	m_transform.scale.z *= z;

	update();
}

void Object::scale(glm::vec3 offset)
{
	scale(offset.x, offset.y, offset.z);
}

void Object::setPosition(float x, float y, float z)
{
	glm::vec3 newPos = glm::vec3(x, y, z);
	glm::vec3 amount = newPos - m_transform.position;

	move(amount);
}

void Object::setPosition(glm::vec3 offset)
{
	setPosition(offset.x, offset.y, offset.z);
}

void Object::setRotation(char axis, float amount)
{
	glm::vec3 newRot = glm::vec3(0.0f);

	if (axis == 'x') newRot = glm::vec3(amount, 0.0f, 0.0f);
	else if (axis == 'y') newRot = glm::vec3(0.0f, amount, 0.0f);
	else if (axis == 'z') newRot = glm::vec3(0.0f, 0.0f, amount);
	else
	{
		logMessage("Attempting to rotate object around nonexistent axis: " + axis, "OBJT", 1);
		return;
	}

	glm::vec3 diff = m_transform.rotation - newRot;

	if	    (axis == 'x') rotate('x', diff.x);
	else if (axis == 'y') rotate('y', diff.y);
	else if (axis == 'z') rotate('z', diff.z);
}

void Object::setScale(float x, float y, float z)
{
	glm::vec3 newScale = glm::vec3(1.0f) + glm::vec3(x, y, z);
	glm::vec3 amount   = newScale - m_transform.scale;

	scale(amount);
}

void Object::setScale(glm::vec3 offset)
{
	setScale(offset.x, offset.y, offset.z);
}

void Object::update()
{
	m_shader->bind();

	m_transform.proj = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

	m_shader->setM4("model", m_transform.model);
	m_shader->setM4("projection", m_transform.proj);
}

void Object::updateView(glm::mat4 view)
{
	m_shader->bind();
	m_shader->setM4("view", view);
}

void Object::setColor(float r, float g, float b, float a)
{
	m_shader->bind();
	m_color = color{ r, g, b, a };
	m_shader->setV4("color", glm::vec4(m_color.r, m_color.g, m_color.b, m_color.a));
}

void Object::setColor(color newColor)
{
	m_shader->bind();
	m_color = newColor;
	m_shader->setV4("color", glm::vec4(m_color.r, m_color.g, m_color.b, m_color.a));
}

void Object::setTexture(Texture* texture)
{
	m_shader->bind();
	m_texture  = texture;
	m_textured = true;
	m_shader->setB("textured", true);
}

void Object::setTexture(std::string path)
{
	Texture newTexture(path);
	m_texture  = &newTexture;
	m_textured = true;
	m_shader->setB("textured", true);
}