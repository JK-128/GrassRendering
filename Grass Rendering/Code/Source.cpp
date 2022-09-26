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
#include "Objects/SkyBox.h"

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
		Quad quad2;
		SkyBox skybox;

		quad.scale(2.0f, 2.0f, 2.0f);
		quad2.setPosition(0.0f, 0.0f, 2.0f);
		quad.setColor(1.0f, 0.0f, 0.0f, 1.0f);
		skybox.setColor(0.1f, 0.2f, 0.7f, 1.0f);
		skybox.scale(glm::vec3(50.0f));

		Camera camera;

		while (!window.isClosing())
		{
			updateDeltaTime();

			camera.move();
			camera.look();

			window.clear();

			quad.updateView(camera.getView());
			quad.draw();

			quad2.updateView(camera.getView());
			quad2.draw();

			skybox.updateView(camera.getView());
			skybox.draw();

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
+ Get a texture class working to load textures
+ Use these with the plane
+ Create custom shaders for the skybox.
+ Load a textured skybox to test.
*/