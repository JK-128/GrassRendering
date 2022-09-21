#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "Window.h"
#include "ImGuiWrapper.h"
#include "Console.h"

//GLM include test
#include "../Dependencies/glm/glm/glm.hpp"
#include "../Dependencies/glm/glm/matrix.hpp"

int WinMain()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	logMessage("Grass Renderer Program Started.", "MAIN");

	Window window(800, 800, "Test Window", true, true);

	glm::vec3 one   = glm::vec3(1, 1, 1);
	glm::vec3 two   = glm::vec3(2, 2, 2);
	glm::vec3 three = one * two;

	logMessage("GLM test: " + std::to_string(three.x), "MAIN");

	if (window.isCreated())
	{
		imgui = new ImGuiWrapper(window.getGlfwWindow());

		Console console;
	
		while (!window.isClosing())
		{
			window.clear();

			imgui->drawObjects();

			window.swap();
			window.poll();
		}
		imgui->destroy();
	}
	glfwTerminate();

	logMessage("Grass Rendering Program closing.", "MAIN");
	logger.saveToFile("Logs/");

	return 0;
}


/*
TO DO:
------
+ Add GLM to the project.
+ Get a plane loaded in.
+ Create some kind of simple camera that allows for WASD movement.
+ Add mouse functionality to this.
+ Implement a sky box.
*/