#include "ImGuiBase.h"
#include "ImGuiWrapper.h"

ImGuiBase::ImGuiBase()
{
	imgui->addObject(this);
}

void ImGuiBase::draw() {}