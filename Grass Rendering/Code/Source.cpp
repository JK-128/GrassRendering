#include <iostream>
#include <GLFW/glfw3.h>

int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 800, "Title", 0, 0);
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
}