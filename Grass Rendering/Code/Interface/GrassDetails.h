#pragma once
#include "../Objects/Grass.h"
#include "ImGuiBase.h"

class GrassDetails : public ImGuiBase
{
private:
	Grass* m_grass;

	float m_tipColor[3] = {0.4, 0.7, 0.22};
	float m_baseColor[3] = {0.2, 0.35, 0.11};

	float m_noiseX     = 0.05f;
	float m_noiseZ     = 0.5f;
	float m_noiseS     = 0.3f;
	float m_windSpeed  = 0.3f;
	float m_strength   = 0.3f;
	float m_height     = 0.6f;
	float m_brightness = 0.3f;
	float m_contrast   = 2.0f;
	
	int m_count = 50;

	bool m_hasGrass = false;

public:

	void draw();
	void attachGrass(Grass* grass);
};

