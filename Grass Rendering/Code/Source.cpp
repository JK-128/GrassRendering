#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "Window.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	logMessage("Grass Renderer Program Started.");

	Window window(800, 800, "Test Window", true, true);

	logMessage("Entering main loop.");
	while (!window.isClosing())
	{
		logger.printNewMessages();

		window.swap();
		window.poll();
	}
	//glfwTerminate();

	logMessage("Grass Rendering Program closing.");

	logger.saveToFile("Logs/");
}