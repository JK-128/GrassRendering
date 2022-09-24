#include "FrameRate.h"

void FrameRate::draw()
{
	float updated[500] = { 0.0f };

	for (int i = 0; i < 499; i++)
		updated[i] = m_framerates[i + 1];

	updated[499] = (float)deltaTime;

	for (int i = 0; i < 500; i++)
		m_framerates[i] = updated[i];

	ImGui::Begin("FPS");

	std::string frameTime = std::to_string(deltaTime);
	std::string frameRate = std::to_string(1.0 / deltaTime);
	std::string combined  = frameTime + " : " + frameRate;

	ImGui::PlotLines("", m_framerates, 500, 0, combined.c_str(), 0, 0.25, ImVec2(250, 50));

	ImGui::End();
}