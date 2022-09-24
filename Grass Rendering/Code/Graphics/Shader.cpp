#include "Shader.h"

Shader::Shader(std::string vertPath, std::string fragPath)
{
	int success;

	std::string vertString = loadSource(vertPath);
	std::string fragString = loadSource(fragPath);

	const char* vertSource = vertString.c_str();
	const char* fragSource = fragString.c_str();

	if (vertSource == "NULL" || fragSource == "NULL")
	{
		logMessage("Could not create shader program.", "SHDR", 2);
		m_compiled = false;
		return;
	}

	m_vert = glCreateShader(GL_VERTEX_SHADER);
	m_frag = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(m_vert, 1, &vertSource, NULL);
	glShaderSource(m_frag, 1, &fragSource, NULL);

	glCompileShader(m_vert);
	glGetShaderiv(m_vert, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(m_vert, 512, NULL, m_shaderLog);
		logMessage("Could not compile VERTEX SHADER: " + std::string(m_shaderLog), "SHDR", 2);
		m_compiled = false;
	}

	glCompileShader(m_frag);
	glGetShaderiv(m_frag, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(m_frag, 512, NULL, m_shaderLog);
		logMessage("Could not compile FRAGMENT SHADER: " + std::string(m_shaderLog), "SHDR", 2);
		m_compiled = false;
	}

	m_program = glCreateProgram();

	glAttachShader(m_program, m_vert);
	glAttachShader(m_program, m_frag);

	glLinkProgram(m_program);
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);

	if (!success)
	{
		logMessage("Failed to link program.", "SHDR", 2);
		m_compiled = false;
	}

	glDeleteShader(m_vert);
	glDeleteShader(m_frag);
}

GLuint* Shader::get()
{
	return &m_program;
}

std::string Shader::loadSource(std::string path)
{
	std::fstream file;
	file.open(path, std::ios::in);

	if (!file)
	{
		logMessage("Failed to load shader source: " + path, "SHDR", 2);
		return "NULL";
	}
	
	std::string content;
	std::string line;

	while (std::getline(file, line))
		content += line + "\n";

	file.close();

	return content;
}

void Shader::bind()
{
	if (m_compiled)
		glUseProgram(m_program);
	else
		logMessage("Attempting to use an uncompiled shader.", "SHDR", 2);
}



void Shader::setB(std::string name, bool value)
{
	glUniform1i(glGetUniformLocation(m_program, name.c_str()), (int)value);
}
void Shader::setI(std::string name, int value)
{
	glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}
void Shader::setF(std::string name, float value)
{
	glUniform1f(glGetUniformLocation(m_program, name.c_str()), value);
}
void Shader::setM4(std::string name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
void Shader::setV2(std::string name, glm::vec2 value)
{
	glUniform2fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);
}
void Shader::setV3(std::string name, glm::vec3 value)
{
	glUniform3fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);
}
void Shader::setV4(std::string name, glm::vec4 value)
{
	glUniform4fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);
}