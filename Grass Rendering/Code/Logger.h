#pragma once
#include <iostream>
#include <vector>

class Logger
{
private:
	std::vector<std::string> m_messages;
	int m_position = 0;

public:
	std::vector<std::string> getMessages();

	void addMessage(std::string message);
	void printNewMessages();
};

extern Logger logger;

void logMessage(std::string message);