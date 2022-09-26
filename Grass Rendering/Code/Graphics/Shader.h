#pragma once
#include "../Utility/Logger.h"
#include "../../Dependencies/glm/glm/glm.hpp"
#include "../../Dependencies/glm/glm/matrix.hpp"
#include <glad/glad.h>

typedef struct 
{ 
	float r; 
	float g; 
	float b; 
	float a; 
} color;

class Shader
{
private:
	unsigned int m_vert;
	unsigned int m_frag;
	unsigned int m_program;

	char m_shaderLog[512];

	std::string m_vertexPath    = "NULL";
	std::string m_fragementPath = "NULL";

	bool m_compiled = true;

public:
	Shader(std::string vertPath, std::string fragPath);

	GLuint* get();

	std::string loadSource(std::string path);

	void bind();
	void setB(std::string name, bool value);
	void setI(std::string name, int value);
	void setF(std::string name, float value);
	void setM4(std::string name, glm::mat4 value);
	void setV2(std::string name, glm::vec2 value);
	void setV3(std::string name, glm::vec3 value);
	void setV4(std::string name, glm::vec4 value);
};

