#include "Console.h"

void Console::draw()
{
	std::vector<std::string> messages = logger.getMessages();

	m_messageCount = messages.size();
	m_errorCount   = 0;
	m_warningCount = 0;

	ImGui::SetNextWindowSize(ImVec2(500, 200));
	ImGui::Begin("Console");

	if (ImGui::IsWindowHovered())
		imgui->setHovered(true);

	float ySpacing     = ImGui::GetStyle().ItemSpacing.y;
	float frameHeight  = ImGui::GetFrameHeightWithSpacing();
	float footerHeight = ySpacing + frameHeight;

	ImGui::BeginChild("Text", ImVec2(0, -footerHeight), false);

	if (ImGui::IsWindowHovered())
		imgui->setHovered(true);

	for (int i = 0; i < m_messageCount; i++)
	{
		printMessage(messages[i]);
	}

	//ImGui::SetScrollHereY(1.0f);
	ImGui::EndChild();

	ImGui::End();
}

void Console::printMessage(std::string message)
{
	int level = (int)message[0] - 48;

	if (level == 0 && !m_showMessages) return;
	if (level == 1 && !m_showWarnings) return;
	if (level == 2 && !m_showErrors)   return;

	color mColor = MessageColors[level];

	std::string cleanMessage = message.substr(1, message.size() - 1);
	std::string author       = getAuthor(cleanMessage);

	if (author != m_previousAuthor)
	{
		ImGui::Separator();
		m_previousAuthor = author;
	}

	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(mColor.r, mColor.g, mColor.b, 255));
	ImGui::PushTextWrapPos(450);

	ImGui::Text(cleanMessage.c_str());

	ImGui::PopTextWrapPos();
	ImGui::PopStyleColor();
}

std::string Console::getAuthor(std::string message)
{
	std::string noTime = message.substr(15, message.size() - 14);

	int index = noTime.find(']');

	std::string author = noTime.substr(0, index);

	return author;
}