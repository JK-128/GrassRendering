#pragma once
#include "../Objects/Grass.h"
#include "ImGuiBase.h"

class GrassDetails : public ImGuiBase
{
private:
	Grass* m_grass;
	//std::vector<Grass*> m_grasses;

	float m_tipColor[3] = {0.4f, 0.7f, 0.22f};
	float m_baseColor[3] = {0.2f, 0.35f, 0.11f};

	float m_noiseX     = 0.05f;
	float m_noiseZ     = 0.5f;
	float m_noiseS     = 0.3f;
	float m_windScale  = 0.3f;
	float m_strength   = 0.3f;
	float m_height     = 0.6f;
	float m_brightness = 0.3f;
	float m_contrast   = 2.0f;
	float m_noiseC     = 0.0f;
	float m_windSpeed  = 1.0f;

	float m_interStrength = 0.5f;
	float m_interRadius   = 1.0f;
	float m_interTargetZ  = 0.0f;
	float m_interBRadius  = 0.1f;

	int m_count = 50;
	int m_shape = 0;

	bool m_hasGrass = false;
	bool m_gridAligned = true;

public:
	~GrassDetails();

	void draw();
	void attachGrass(Grass* grass);
};

