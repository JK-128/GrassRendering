#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Logger.h"

class Window
{
private:
	int m_width  = 800;
	int m_height = 800;

	bool m_closing = false;

	const char* m_title = "Default Title";

	GLFWwindow* mp_window = 0;

public:
	Window(int width, int height, const char* title, bool createNow = true, bool initGlfw = false);

	GLFWwindow* getGlfwWindow();

	bool isClosing();

	void create(bool initGlad = false);
	void poll();
	void swap();
	void close();
	void clear();
};

