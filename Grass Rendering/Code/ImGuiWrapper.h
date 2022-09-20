#pragma once
#include <GLFW/glfw3.h>

#include "Logger.h"

#include "../Dependencies/imgui-master/imgui-master/imgui.h"
#include "../Dependencies/imgui-master/imgui-master/imgui_impl_opengl3.h"
#include "../Dependencies/imgui-master/imgui-master/imgui_impl_glfw.h"
#include "../Dependencies/imgui-master/imgui-master/imgui_internal.h"


class ImGuiWrapper
{
private:
	bool m_hovered = false;

public:
	ImGuiWrapper(GLFWwindow* window);

	void newFrame();
	void render();
	void destroy();
	void setHovered(bool status);
};

extern ImGuiWrapper* imgui;