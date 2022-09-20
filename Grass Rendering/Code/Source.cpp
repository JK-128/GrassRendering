#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "Window.h"
#include "ImGuiWrapper.h"
#include "Console.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	logMessage("Grass Renderer Program Started.", "MAIN");

	Window window(800, 800, "Test Window", true, true);

	imgui = new ImGuiWrapper(window.getGlfwWindow());

	Console console;

	while (!window.isClosing())
	{
		window.clear();

		imgui->newFrame();

		console.draw();

		imgui->render();
		
		window.swap();
		window.poll();
	}
	imgui->destroy();
	glfwTerminate();


	logMessage("Grass Rendering Program closing.", "MAIN");
	logger.saveToFile("Logs/");
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