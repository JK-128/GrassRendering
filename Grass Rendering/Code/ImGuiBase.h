#pragma once
#include "../Dependencies/imgui-master/imgui-master/imgui.h"
#include "../Dependencies/imgui-master/imgui-master/imgui_impl_opengl3.h"
#include "../Dependencies/imgui-master/imgui-master/imgui_impl_glfw.h"
#include "../Dependencies/imgui-master/imgui-master/imgui_internal.h"

class ImGuiBase
{
public:
	ImGuiBase();

	virtual void draw();
};

