#include "ImGuiWrapper.h"

ImGuiWrapper* imgui;

ImGuiWrapper::ImGuiWrapper(GLFWwindow* window)
{
	try
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 460");

		logMessage("IMGUI initialised.", "IGUI");
		m_created = true;
	}
	catch (...)
	{
		logMessage("Could not initialise IMGUI.", "IGUI", 2);
	}
}

void ImGuiWrapper::newFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiWrapper::render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiWrapper::destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();

	delete this;
}

void ImGuiWrapper::setHovered(bool status)
{
	m_hovered = status;
}

void ImGuiWrapper::addObject(ImGuiBase* object)
{
	m_objects.push_back(object);
}

void ImGuiWrapper::drawObjects() 
{
	if (m_created)
	{
		imgui->setHovered(false);

		newFrame();

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(300, 1080));
		ImGui::Begin("Details");

		for (int i = 0; i < m_objects.size(); i++)
			m_objects[i]->draw();

		ImGui::End();
		render();
	}
	else
		logMessage("Attempting to use IMGUI before creation.", "IGUI", 1);
}