#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "Graphics/Window.h"
#include "Interface/Console.h"
#include "Interface/FrameRate.h"
#include "Graphics/Shader.h"
#include "Utility/DeltaTime.h"
#include "Objects/Quad.h"

int WinMain()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	logMessage("Grass Renderer Program Started.", "MAIN");

	Window window(1920, 1080, "Test Window", true, true);

	if (window.isCreated())
	{
		imgui = new ImGuiWrapper(window.getGlfwWindow());

		Console   console;
		FrameRate fps;

		Quad quad;

		while (!window.isClosing())
		{
			updateDeltaTime();
	
			window.clear();
			quad.draw();
			imgui->drawObjects();

			window.swap();
			window.poll();
		}
		imgui->destroy();
	}
	glfwTerminate();

	logMessage("Grass Rendering Program closing.", "MAIN");
	//logger.saveToFile();

	return 0;
}


/*
TO DO:
------
+ Ammend logger saving to file so it still happens even with fatal crashes.
+ Check for and cover error conditions in newly added sections.
+ Create input system
	+ Enum to map strings to GLFW keys.
	+ function to take a string and return bool based on if key is pressed/down.
+ Create some kind of simple camera that allows for WASD movement.
+ Add mouse functionality to this.
+ Implement a sky box.

	Remember not to overcomplicate the shaders. No need for lighting/PBR/GI etc.
	Keep it simple so you can focus on the actual interesting parts of the grass sim.
*/