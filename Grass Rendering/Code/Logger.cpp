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

void Logger::saveToFile(std::string filePath)
{
	std::string timeString = getCurrentTimeString();

	for (int i = 0; i < timeString.length(); i++)
		if (timeString[i] == ':' || timeString[i] == '.')
			timeString[i] = '-';

	filePath += timeString + ".log";

	std::fstream file;
	file.open(filePath, std::ios::app);

	for (std::string s : m_messages)
		file << s << "\n";

	file.close();
}

std::string getCurrentTimeString()
{
	auto timeSinceEpoch = std::chrono::system_clock::now().time_since_epoch();
	auto timeMS         = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch);
	int  msCount        = timeMS.count();

	std::string time = std::to_string(msCount);
	std::string ms   = time.substr(time.size() - 3, 3);

	struct tm timeinfo;
	std::time_t result = std::time(nullptr);

	localtime_s(&timeinfo, &result);

	std::string h = std::to_string(timeinfo.tm_hour);
	std::string m = std::to_string(timeinfo.tm_min);
	std::string s = std::to_string(timeinfo.tm_sec);

	if (h.size() == 1) h = "0" + h;
	if (m.size() == 1) m = "0" + m;
	if (s.size() == 1) s = "0" + s;

	std::string timeString = h + ':' + m + ':' + s + '.' + ms;

	return timeString;
}

void logMessage(std::string message)
{
	std::string timeString = getCurrentTimeString();
	
	std::string updatedMessage = "[" + timeString + "] " + message;

	logger.addMessage(updatedMessage);
}