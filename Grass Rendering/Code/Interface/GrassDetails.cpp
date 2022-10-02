#include "GrassDetails.h"

void GrassDetails::draw()
{
	if (!m_hasGrass)
	{
		logMessage("Attempting to use grass without object attached.", "GDET", 1);
		return;
	}

	if (ImGui::CollapsingHeader("Tweak Grass"))
	{
		ImGui::Indent(10.0f);

		if (ImGui::CollapsingHeader("Base Colors"))
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
			floatProp("Scale X:", "nx", &m_noiseX, 0.01f, false);
			floatProp("Scale Z:", "nz", &m_noiseZ, 0.01f, false);
			floatProp("Height Strength:", "ns", &m_noiseS, 0.01f, false);
			floatProp("Color Strength:", "ncs", &m_noiseC, 0.01f, false);

			ImGui::NewLine();
		}
		if (ImGui::CollapsingHeader("Wind"))
		{
			floatProp("Scale:", "ws", &m_windScale, 0.05f, false);
			floatProp("Strength:", "s", &m_strength, 0.01f, false);
			floatProp("Speed:", "wsp", &m_windSpeed, 0.05f, false);

			ImGui::NewLine();
		}
		if (ImGui::CollapsingHeader("Amount"))
		{
			ImGui::Text("Count:");
			ImGui::InputInt("count", &m_count, 50);

			if (ImGui::Button("Update"))
			{
				//for(int i = 0; i < m_grasses.size(); i++)
					m_grass->updateCount(m_count);
			}

			m_count = std::max(50, m_count);

			floatProp("Height:", "h", &m_height, 0.05f, false);

			ImGui::Text("Grid Aligned:");
			ImGui::Checkbox("##ga", &m_gridAligned);

			ImGui::NewLine();
		}
		ImGui::Indent(-10.0f);
	}

	//for (int i = 0; i < m_grasses.size(); i++)
	//{
		Shader* shader = m_grass->getShader();

		m_grass->setColor(m_baseColor[0], m_baseColor[1], m_baseColor[2], 1.0);
		m_grass->setGridAligned(m_gridAligned);

		shader->bind();
		shader->setV3("tipColor", glm::vec3(m_tipColor[0], m_tipColor[1], m_tipColor[2]));
		shader->setV3("baseColor", glm::vec3(m_baseColor[0], m_baseColor[1], m_baseColor[2]));
		shader->setF("noiseX", m_noiseX);
		shader->setF("noiseZ", m_noiseZ);
		shader->setF("wScale", m_windScale);
		shader->setF("strength", m_strength);
		shader->setF("noiseS", m_noiseS);
		shader->setF("grassHeight", m_height);
		shader->setF("brightness", m_brightness);
		shader->setF("contrast", m_contrast);
		shader->setF("noiseC", m_noiseC);
		shader->setF("windSpeed", m_windSpeed);
	//}
}

void GrassDetails::attachGrass(Grass* grass)
{
	m_grass = grass;
	//m_grasses.push_back(grass);
	m_hasGrass = true;
}

GrassDetails::~GrassDetails()
{
	//for (int i = 0; i < m_grasses.size(); i++)
	//	delete m_grasses[i];
}