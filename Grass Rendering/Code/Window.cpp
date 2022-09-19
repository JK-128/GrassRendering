#include "Window.h"

Window::Window(int width, int height, const char* title, bool createNow, bool initGlfw)
{
	if (initGlfw)
		glfwInit();

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
	mp_window = glfwCreateWindow(m_width, m_height, m_title, 0, 0);

	glfwMakeContextCurrent(mp_window);
}

void Window::poll()
{
	glfwPollEvents();

	if (glfwWindowShouldClose(mp_window))
		m_closing = true;
}

void Window::swap()
{
	glfwSwapBuffers(mp_window);
}

void Window::close()
{
	m_closing = true;
}