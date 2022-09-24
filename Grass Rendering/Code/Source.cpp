#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "Graphics/Window.h"
#include "Interface/Console.h"
#include "Graphics/Shader.h"
#include "Utility/DeltaTime.h"

int WinMain()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	logMessage("Grass Renderer Program Started.", "MAIN");

	Window window(800, 800, "Test Window", true, true);

	Shader shader("Content/Shaders/vert.glsl", "Content/Shaders/frag.glsl");

	if (window.isCreated())
	{
		imgui = new ImGuiWrapper(window.getGlfwWindow());

		Console console;
	
		while (!window.isClosing())
		{
			updateDeltaTime();

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
+ Implement a delta time feature.
+ Create an interface element to display the framerate.
	+ Could do a graph like in CSGMod?
+ Create an object base class to contain OpenGL code.
+ Get a plane loaded in.
+ Create some kind of simple camera that allows for WASD movement.
+ Add mouse functionality to this.
+ Implement a sky box.

	Remember not to overcomplicate the shaders. No need for lighting/PBR/GI etc.
	Keep it simple so you can focus on the actual interesting parts of the grass sim.
*/