#include "Window.h"

Window::Window(int width, int height, const char* title, bool createNow, bool initGlfw)
{
	if (initGlfw)
	{
		if (!glfwInit())
			logMessage("Failed to initialise GLFW.");
		else
			logMessage("GLFW initialised.");
	}

	m_width = width;
	m_height = height;
	m_title = title;

	if (createNow)
		create(initGlfw);
}

GLFWwindow* Window::getGlfwWindow()
{
	return mp_window;
}

bool Window::isClosing()
{
	return m_closing;
}

void Window::create(bool initGlad)
{
	logMessage("Window created.");

	mp_window = glfwCreateWindow(m_width, m_height, m_title, 0, 0);

	glfwMakeContextCurrent(mp_window);

	if (initGlad)
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			logMessage("Failed to initialise GLAD.");
		else
			logMessage("GLAD initialised.");

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}
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

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}