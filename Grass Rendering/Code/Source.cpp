#include <iostream>
#include "Window.h"

int main()
{
	logMessage("Grass Renderer Program Started.");

	Window window(800, 800, "Test Window", true, true);

	logMessage("Entering main loop.");
	while (!window.isClosing())
	{
		window.poll();
		window.swap();

		logger.printNewMessages();
	}

	logMessage("Grass Rendering Program closing.");
}