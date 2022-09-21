#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "Window.h"
#include "ImGuiWrapper.h"
#include "Console.h"

int WinMain()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	logMessage("Grass Renderer Program Started.", "MAIN");

	Window* window = new Window;

	bool windowCreated = false;
	try
	{
		delete window;
		window = new Window(800, 800, "Test Window", true, true);
		
		windowCreated = window->isCreated();
		if (!windowCreated)
			throw 1;
	}
	catch (int e)
	{
		logMessage("Unable to create GLFW window.", "MAIN", 2);
	}

	if (windowCreated)
	{
		imgui = new ImGuiWrapper(window->getGlfwWindow());

		Console console;

		while (!window->isClosing())
		{
			window->clear();

			imgui->newFrame();

			console.draw();

			imgui->render();

			window->swap();
			window->poll();
		}
		imgui->destroy();
	}
	glfwTerminate();
	delete window;

	logMessage("Grass Rendering Program closing.", "MAIN");
	logger.saveToFile("Logs/");

	return 0;
}


/*
TO DO:
------
+ Look into exceptions/handling and make it so no possible problem will cause a fatal crash.
+ Add GLM to the project.
+ Get a plane loaded in.
+ Create some kind of simple camera that allows for WASD movement.
+ Add mouse functionality to this.
+ Implement a sky box.
*/