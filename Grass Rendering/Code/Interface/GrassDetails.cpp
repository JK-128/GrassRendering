#include "GrassDetails.h"

void GrassDetails::draw()
{
	if (!m_hasGrass)
	{
		logMessage("Attempting to use grass without object attached.", "GDET", 1);
		return;
	}

	if (ImGui::CollapsingHeader("Grass Details"))
	{
		ImGui::Indent(10.0f);

		if (ImGui::CollapsingHeader("Colors"))
		{
			ImGui::ColorPicker3("Tip Color:", m_tipColor);
			ImGui::ColorPicker3("Base Color:", m_baseColor);

			ImGui::Separator();

			floatProp("Brightness:", "b", &m_brightness, 0.05f, false);
			floatProp("Contrast:", "c", &m_contrast, 0.05f, false);
			ImGui::NewLine();
		}
		if (ImGui::CollapsingHeader("Noise"))
		{
			floatProp("Noise X:", "nx", &m_noiseX, 0.01f, false);
			floatProp("Noise Z:", "nz", &m_noiseZ, 0.01f, false);
			floatProp("Strength:", "ns", &m_noiseS, 0.01f, false);
			ImGui::NewLine();
		}
		if (ImGui::CollapsingHeader("Wind"))
		{
			floatProp("Wind speed:", "ws", &m_windSpeed, 0.05f, false);
			floatProp("Strength:", "s", &m_strength, 0.01f, false);
			ImGui::NewLine();
		}
		if (ImGui::CollapsingHeader("Grass"))
		{
			floatProp("Height:", "h", &m_height, 0.05f, false);
			ImGui::NewLine();
		}
		ImGui::Indent(-10.0f);
	}
	//ImGui::End();

	Shader* shader = m_grass->getShader();

	shader->bind();
	shader->setV3("tipColor", glm::vec3(m_tipColor[0], m_tipColor[1], m_tipColor[2]));
	shader->setV3("baseColor", glm::vec3(m_baseColor[0], m_baseColor[1], m_baseColor[2]));
	shader->setF("noiseX", m_noiseX);
	shader->setF("noiseZ", m_noiseZ);
	shader->setF("wSpeed", m_windSpeed);
	shader->setF("strength", m_strength);
	shader->setF("noiseS", m_noiseS);
	shader->setF("grassHeight", m_height);
	shader->setF("brightness", m_brightness);
	shader->setF("contrast", m_contrast);
}

void GrassDetails::attachGrass(Grass* grass)
{
	m_grass = grass;
	m_hasGrass = true;
}