#pragma once
#include "ImGuiBase.h"
#include "../Graphics/Camera.h"

class CamControls : public ImGuiBase
{
private:
	Camera* m_cam;

	float m_moveSpeed = 0.0f;
	float m_lookSpeed = 0.0f;

	bool m_hasCamera = false;

public:
	void draw();
	void attachCamera(Camera* camera);
};

