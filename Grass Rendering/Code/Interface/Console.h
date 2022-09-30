#pragma once
#include "../Utility/Logger.h"
#include "../Graphics/Shader.h"

#include "ImGuiWrapper.h"

class Console : public ImGuiBase
{
private:
	int m_messageCount = 0;
	int m_errorCount   = 0;
	int m_warningCount = 0;

	int m_height = 300;
	int m_width  = 200;

	bool m_showErrors   = true;
	bool m_showWarnings = true;
	bool m_showMessages = true;

	std::string m_previousAuthor = "NULL";

public:
	std::string getAuthor(std::string message);

	void draw();
	void printMessage(std::string message);
};


static color MessageColors[] =
{
	color{255, 255, 255, 255},		//Message
	color{255, 255,   0, 255},		//Warning
	color{255,   0,   0, 255},		//Error
};