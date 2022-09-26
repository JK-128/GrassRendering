#include "Console.h"

void Console::draw()
{
	std::vector<std::string>* messageList = logger.getMessages();

	m_messageCount = (int)(*messageList).size();
	m_errorCount   = 0;
	m_warningCount = 0;

	ImGui::SetNextWindowSize(ImVec2((float)m_height, (float)m_width));
	ImGui::Begin("Console");

	if (ImGui::IsWindowHovered())
		imgui->setHovered(true);

	//Footer height used to place buttons properly below text.
	float ySpacing     = ImGui::GetStyle().ItemSpacing.y;
	float frameHeight  = ImGui::GetFrameHeightWithSpacing();
	float footerHeight = ySpacing + frameHeight;

	ImGui::BeginChild("Text", ImVec2(0, -footerHeight), false);

	if (ImGui::IsWindowHovered())
		imgui->setHovered(true);

	for (int i = 0; i < m_messageCount; i++)
		printMessage(messageList->at(i));

	ImGui::SetScrollHereY(1.0f); //(Used to keep the scroll bar at the bottom)
	ImGui::EndChild();

	std::string errors   = "[Errors: "   + std::to_string(m_errorCount)   + "]";
	std::string warnings = "[Warnings: " + std::to_string(m_warningCount) + "]";
	std::string messages = "[Messages: " + std::to_string(m_messageCount) + "]";
	
	ImGui::Separator();
	if (ImGui::Button(messages.c_str()))
		m_showMessages = !m_showMessages;

	ImGui::SameLine();
	if (ImGui::Button(warnings.c_str())) 
		m_showWarnings = !m_showWarnings;

	ImGui::SameLine();
	if (ImGui::Button(errors.c_str()))
		m_showErrors = !m_showErrors;

	ImGui::End();
}

void Console::printMessage(std::string message)
{

	int level = (int)message[0] - 48;

	if (level == 0 && !m_showMessages) return;

	if (level == 1)
	{
		m_warningCount++;
		if(!m_showWarnings) 
			return;
	}
	if (level == 2)
	{
		m_errorCount++;
		if(!m_showErrors)   
			return;
	}
	
	color mColor = MessageColors[level];

	std::string cleanMessage = message.substr(1, message.size() - 1); //Removes the preceeding error value.
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

	int index = (int)noTime.find(']');

	std::string author = noTime.substr(0, index);

	return author;
}