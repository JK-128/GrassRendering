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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	mp_window = glfwCreateWindow(m_width, m_height, m_title, 0, 0);

	glfwMakeContextCurrent(mp_window);
	glfwSetCursorPosCallback(mp_window, mouse_callback);
	glfwSetKeyCallback(mp_window, key_callback);
	glfwSetInputMode(mp_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(0);

	if (initGlad)
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			logMessage("Failed to initialise GLAD.", "WNDW", 2);
		else
		{
			m_created = true;
			logMessage("GLAD initialised.", "WNDW");

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
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
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}