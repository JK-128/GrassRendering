#pragma once
#define LOGGING 0

#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <fstream>

class Logger
{
private:
	std::vector<std::string> m_messages;
	
	std::string m_currentFile = "NULL";

	int m_position      =  0;
	int m_previousLevel = -1;

	bool m_containsErrors   = false;
	bool m_containsWarnings = false;

public:
	std::vector<std::string>* getMessages();

	void addMessage(std::string message, int level = 0);
	void saveToFile();
};

extern Logger logger;

std::string getCurrentTimeString();

void logMessage(std::string message, std::string author = "NULL", int level = 0);