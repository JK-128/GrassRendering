#include "SkyboxPicker.h"


void SkyboxPicker::draw()
{
	if (!m_hasSkybox)
	{
		logMessage("No skybox attached.", "SBPR", 1);
		return;
	}

	if(ImGui::CollapsingHeader("Skybox"))
	{
		ImGui::ListBox("##skyboxes", &m_choice, m_names, 3);

		if (m_choice != m_selection)
		{
			m_selection = m_choice;
			updateCubeMap();
		}
	}
}

void SkyboxPicker::updateCubeMap()
{
	std::vector<std::string> paths =
	{
		m_paths[m_selection] + "/right"  + m_types[m_selection],
		m_paths[m_selection] + "/left"   + m_types[m_selection],
		m_paths[m_selection] + "/top"    + m_types[m_selection],
		m_paths[m_selection] + "/bottom" + m_types[m_selection],
		m_paths[m_selection] + "/front"  + m_types[m_selection],
		m_paths[m_selection] + "/back"   + m_types[m_selection]
	};

	CubeMap* cMap = new CubeMap(paths);

	m_skybox->setTexture(cMap);
}

void SkyboxPicker::attachSkyBox(SkyBox* skybox)
{
	m_skybox = skybox;
	m_hasSkybox = true;
}