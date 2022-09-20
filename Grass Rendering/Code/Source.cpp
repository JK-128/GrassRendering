#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "Window.h"
#include "ImGuiWrapper.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	logMessage("Grass Renderer Program Started.");

	Window window(800, 800, "Test Window", true, true);

	ImGuiWrapper imgui(window.getGlfwWindow());

	while (!window.isClosing())
	{
		window.clear();

		logger.printNewMessages();

		imgui.newFrame();

		ImGui::Begin("Test");
		ImGui::Text("This is a test of IMGUI.");
		ImGui::End();

		imgui.render();
		
		window.swap();
		window.poll();
	}
	imgui.destroy();
	glfwTerminate();


	logMessage("Grass Rendering Program closing.");
	logger.saveToFile("Logs/");
}


/*
TO DO:
------
+ Include IMGUI to the project.
	+ Research the correct way to do this.
+ Add GLAD and GLM to the project.
+ Get a plane loaded in.
+ Create some kind of simple camera that allows for WASD movement.
+ Add mouse functionality to this.
+ Implement a sky box.
*/