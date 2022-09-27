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

		Texture texture("Content/Textures/test.png");

		Quad quad;
		Quad quad2;
		SkyBox skybox("Content/Textures/interstellar_skybox", ".png");

		quad.scale(2.0f, 2.0f, 2.0f);
		quad2.setPosition(0.0f, 0.0f, 2.0f);
		quad2.setColor(1.0f, 0.0f, 0.0f, 1.0f);

		quad.setTexture(&texture);

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
			//quad2.draw();

			glm::mat4 skyBoxView = glm::mat4(glm::mat3(camera.getView()));
			skybox.updateView(skyBoxView);
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
+ Create custom shaders for the skybox.
+ Load a textured skybox to test.
+ Get rotations working
	+ Probably don't need quaternions, right?
*/