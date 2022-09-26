#pragma once
#include "../../Dependencies/glm/glm/glm.hpp"
#include "../../Dependencies/glm/glm/matrix.hpp"
#include "../../Dependencies/glm/glm/gtc/matrix_transform.hpp"
#include "../../Dependencies/glm/glm/gtc/type_ptr.hpp"

#include "../Graphics/Shader.h"
#include "../Utility/DeltaTime.h"
#include "../Utility/Logger.h"

typedef struct {
	glm::mat4 proj;
	glm::mat4 view;
	glm::mat4 model;
	glm::vec3 position;
	glm::vec3 scale;
} transform;

class Object
{
protected:
	Shader* m_shader;

	color m_color{ 1.0f, 1.0f, 1.0f, 1.0f };

	int m_index = 0;
	int m_triangleCount = 3;

	unsigned int m_VAO = 0;
	unsigned int m_VBO = 0;
	unsigned int m_EBO = 0;

	std::vector<float> m_vertices;
	std::vector<int>   m_indices;
	
	bool m_elements  = false;
	bool m_normals   = true;
	bool m_texCoords = true;
	bool m_visible   = true;

	transform m_transform;

public:
	Object();
	~Object();

	color getColor();

	void setup(int vertices, int indices, int offset = 3);
	virtual void draw();

	void move(float x, float y, float z);
	void move(glm::vec3 offset);

	void scale(float x, float y, float z);
	void scale(glm::vec3 offset);

	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 offset);

	void setScale(float x, float y, float z);
	void setScale(glm::vec3 offset);

	void update();
	void updateView(glm::mat4 view);

	void setColor(float r, float g, float b, float a);
	void setColor(color newColor);
};

