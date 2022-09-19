#include "Window.h"

Window::Window(int width, int height, const char* title, bool createNow, bool initGlfw)
{
	if (initGlfw)
	{
		glfwInit();

		logMessage("GLFW initialised.");
	}

	m_width = width;
	m_height = height;
	m_title = title;

	if (createNow)
		create();
}

bool Window::isClosing()
{
	return m_closing;
}

void Window::create()
{
	logMessage("Window created.");

	mp_window = glfwCreateWindow(m_width, m_height, m_title, 0, 0);

	glfwMakeContextCurrent(mp_window);
}

void Window::poll()
{
	glfwPollEvents();

	if (glfwWindowShouldClose(mp_window))
		close();
}

void Window::swap()
{
	glfwSwapBuffers(mp_window);
}

void Window::close()
{
	logMessage("Window closing.");

	m_closing = true;
}