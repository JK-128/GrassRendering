#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "Window.h"

//Testing the include methods for IMGUI:
#include "../Dependencies/imgui-master/imgui-master/imgui.h"
#include "../Dependencies/imgui-master/imgui-master/imgui_impl_opengl3.h"
#include "../Dependencies/imgui-master/imgui-master/imgui_impl_glfw.h"
#include "../Dependencies/imgui-master/imgui-master/imgui_internal.h"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	logMessage("Grass Renderer Program Started.");

	Window window(800, 800, "Test Window", true, true);

	//Setting up imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(window.getGlfwWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460");

	while (!window.isClosing())
	{
		window.clear();

		logger.printNewMessages();

		
		//Testing IMGUI functionality
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Test");
		ImGui::Text("This is a test of IMGUI.");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		window.swap();
		window.poll();
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
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