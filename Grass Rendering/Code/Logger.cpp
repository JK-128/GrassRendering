#include "Logger.h"

Logger logger;

std::vector<std::string> Logger::getMessages()
{
	return m_messages;
}

void Logger::addMessage(std::string message)
{
	m_messages.push_back(message);
}

void Logger::printNewMessages()
{
	for (; m_position < m_messages.size(); m_position++)
		std::cout << m_messages[m_position] << "\n";
}


void logMessage(std::string message)
{
	logger.addMessage(message);
}