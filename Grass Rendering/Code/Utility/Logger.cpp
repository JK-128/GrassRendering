#include "Logger.h"

Logger logger;

std::vector<std::string>* Logger::getMessages()
{
	return &m_messages;
}

void Logger::addMessage(std::string message, int level)
{
	if (level == 1) m_containsWarnings = true;
	if (level == 2) m_containsErrors   = true;

	m_messages.push_back(message);
}

void Logger::saveToFile(std::string filePath)
{
	std::string timeString = getCurrentTimeString();

	//Replacing 'time unit separators' so can be used in file name.
	for (int i = 0; i < timeString.length(); i++)
		if (timeString[i] == ':' || timeString[i] == '.')
			timeString[i] = '-';

	if (m_containsErrors)
		timeString += " [ERR]";
	else if (m_containsWarnings)
		timeString += " [WAR]";
	else
		timeString += " [CLR]";

	filePath += timeString + ".log";

	std::fstream file;
	file.open(filePath, std::ios::app);

	for (std::string message : m_messages)
	{
		int level = std::stoi(message.substr(0, 1));

		message = message.substr(1, message.size() - 1);
		
		if ((m_previousLevel != level) && (m_previousLevel != -1))
			file << "\n";

		if (level == 0) message = "[CLR]" + message;
		if (level == 1) message = "[WAR]" + message;
		if (level == 2) message = "[ERR]" + message;

		file << message << "\n";
		
		m_previousLevel = level;
	}

	file.close();
}

std::string getCurrentTimeString()
{
	auto timeSinceEpoch = std::chrono::system_clock::now().time_since_epoch();
	auto timeMS         = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch);
	int  msCount        = (int)timeMS.count();

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

void logMessage(std::string message, std::string author, int level)
{
	std::string timeString   = "[" + getCurrentTimeString() + "]";
	std::string authorString = "[" + author + "] ";

	std::string updatedMessage = std::to_string(level) + timeString + authorString + message;

	logger.addMessage(updatedMessage, level);
}