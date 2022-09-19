#pragma once
#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <fstream>

class Logger
{
private:
	std::vector<std::string> m_messages;

	int m_position = 0;

public:
	std::vector<std::string> getMessages();

	void addMessage(std::string message);
	void printNewMessages();
	void saveToFile(std::string path);
};

extern Logger logger;

std::string getCurrentTimeString();

void logMessage(std::string message);