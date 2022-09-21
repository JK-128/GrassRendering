#pragma once
#include <GLFW/glfw3.h>

#include "../Utility/Logger.h"
#include "ImGuiBase.h"


class ImGuiWrapper
{
private:
	bool m_hovered = false;
	bool m_created = false;

	std::vector<ImGuiBase*> m_objects;

	void newFrame();
	void render();

public:
	ImGuiWrapper(GLFWwindow* window);

	void destroy();
	void setHovered(bool status);
	void addObject(ImGuiBase* object);
	void drawObjects();
};

extern ImGuiWrapper* imgui;
