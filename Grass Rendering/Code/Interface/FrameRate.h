#pragma once
#include "ImGuiBase.h"

class FrameRate : public ImGuiBase
{
private:
	float m_framerates[500] = { 0.0f };

public:
	void draw();
};

