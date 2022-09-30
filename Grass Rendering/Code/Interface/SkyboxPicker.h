#pragma once
#include "../Objects/SkyBox.h"
#include "ImGuiBase.h"
#include <tuple>

class SkyboxPicker : public ImGuiBase
{
private:
	SkyBox* m_skybox;

	bool m_hasSkybox = false;

	int m_choice    = 1;
	int m_selection = 1;

	const char* m_names[3] =
	{ 
		"Clouds1",
		"Interstellar",
		"Mountains"
	};

	std::vector<std::string> m_paths = 
	{
		"Content/Textures/clouds1",
		"Content/Textures/interstellar_skybox",
		"Content/Textures/skybox"
	};

	std::vector<std::string> m_types = 
	{
		".bmp",
		".png",
		".jpg"
	};

public:
	void draw();
	void attachSkyBox(SkyBox* skybox);
	void updateCubeMap();
};

