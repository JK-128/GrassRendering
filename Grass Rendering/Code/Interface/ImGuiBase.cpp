#include "ImGuiBase.h"
#include "ImGuiWrapper.h"

ImGuiBase::ImGuiBase()
{
	imgui->addObject(this);
}

void ImGuiBase::draw() {}

void ImGuiBase::floatProp(std::string label, std::string name, float* value, float step, bool sameLine)
{
	std::string identifier = "##" + name;

	ImGui::Text(label.c_str());

	if (sameLine)
		ImGui::SameLine();

	ImGui::InputFloat(identifier.c_str(), value, step, step * 2, "%f", 0);
}