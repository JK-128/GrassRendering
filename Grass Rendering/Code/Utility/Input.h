#pragma once
#include <GLFW/glfw3.h>
#include <map>

#include "Logger.h"

extern GLFWwindow* inputWindowRef;
extern bool windowAssigned;

static std::map<std::string, int> stringToGlfwInput
{
	{"Escape", GLFW_KEY_ESCAPE},
	{"w", GLFW_KEY_W}
};

static bool isKeyPressed(std::string key)
{
	if (!windowAssigned)
	{
		logMessage("Trying to get input without an assigned window.", "INPT", 2);
		return false;
	}

	if (stringToGlfwInput.find(key) != stringToGlfwInput.end())
	{
		if (glfwGetKey(inputWindowRef, stringToGlfwInput[key]) == GLFW_PRESS)
			return true;
	}
	else
	{
		logMessage("Key [" + key + "] does not exist.", "INPT", 1);
	}

	return false;
}