#include "Window.h"

Window::Window() {}

Window::Window(int width, int height, const char* title, bool createNow, bool initGlfw)
{
	if (initGlfw)
	{
		if (!glfwInit())
			logMessage("Failed to initialise GLFW.", "WNDW", 2);
		else
			logMessage("GLFW initialised.", "WNDW");
	}

	m_width  = width;
	m_height = height;
	m_title  = title;

	if (createNow)
	{
		create(initGlfw);

		if (!m_created)
			logMessage("Unable to create GLFW window.", "WNDW", 2);
	}
}

GLFWwindow* Window::getGlfwWindow()
{
	return mp_window;
}

bool Window::isClosing()
{
	return m_closing;
}

bool Window::isCreated()
{
	if (!m_created)
		logMessage("Trying to use a window that has not been created.", "WNDW", 1);

	return m_created;
}

void Window::create(bool initGlad)
{
	if (m_created)
	{
		logMessage("Window already created.", "WNDW", 1);
		return;
	}

	logMessage("Window created.", "WNDW");

	mp_window = glfwCreateWindow(m_width, m_height, m_title, 0, 0);

	glfwMakeContextCurrent(mp_window);
	glfwSetCursorPosCallback(mp_window, mouse_callback);

	if (initGlad)
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			logMessage("Failed to initialise GLAD.", "WNDW", 2);
		else
		{
			m_created = true;
			logMessage("GLAD initialised.", "WNDW");

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
		}
	}
}

void Window::poll()
{
	glfwPollEvents();

	if (isKeyPressed("Escape"))
		close();

	if (glfwWindowShouldClose(mp_window))
		close();
}

void Window::swap()
{
	glfwSwapBuffers(mp_window);
}

void Window::close()
{
	glfwSetWindowShouldClose(mp_window, true);

	logMessage("Window closing.", "WNDW");

	m_closing = true;
}

void Window::clear()
{
	glClearColor(0.2f, 0.03f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}