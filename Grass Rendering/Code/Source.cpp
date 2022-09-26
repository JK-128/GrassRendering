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
#include "Utility/Input.h"
#include "Graphics/Camera.h"

int WinMain()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	logMessage("Grass Renderer Program Started.", "MAIN");

	Window window(1920, 1080, "Test Window", true, true);

	if (window.isCreated())
	{
		imgui = new ImGuiWrapper(window.getGlfwWindow());
		
		inputWindowRef = window.getGlfwWindow();
		windowAssigned = true;

		Console   console;
		FrameRate fps;

		Quad quad;

		Camera camera;

		while (!window.isClosing())
		{
			updateDeltaTime();
			camera.move();

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

	return 0;
}


/*
TO DO:
------
+ Create some kind of simple camera that allows for WASD movement.
+ Add mouse functionality to this.
+ Check that the plane is loading correctly.
+ Implement a sky box.
*/