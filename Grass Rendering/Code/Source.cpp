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

#include "Objects/GrassBlade.h"

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

		quad2.setRotation('x', 90.0f);

		quad.setTexture(&texture);

		GrassBlade blade;

		Camera camera;

		quad.setVisibility(false);

		while (!window.isClosing())
		{
			updateDeltaTime();

			camera.move();
			camera.look();

			window.clear();
			/*
			quad.updateView(camera.getView());
			//quad.draw();

			quad2.updateView(camera.getView());
			//quad2.draw();

			blade.updateView(camera.getView());
			//blade.draw();

			glm::mat4 skyBoxView = glm::mat4(glm::mat3(camera.getView()));
			skybox.updateView(skyBoxView);
			//skybox.draw();
			*/
			glm::mat4 view = camera.getView();
			for (int i = 0; i < objects.size(); i++)
			{
				objects[i]->updateView(view);
				objects[i]->draw();
			}

			glm::mat4 skyBoxView = glm::mat4(glm::mat3(view));
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
+ Create a grass object.
+ Create a ground plane object.
+ Pick points on the ground plane.
+ Spawn a blade of grass at each point.
+ Make this a very robust function so that the density can be easily changed. 
+ Should get to a instance rendered large plane full of dense grass that is performant.
*/