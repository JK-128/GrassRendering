#pragma once
#include <GLFW/glfw3.h>
#include <map>

#include "Logger.h"

extern GLFWwindow* inputWindowRef;
extern bool windowAssigned;

static double xOffset;
static double yOffset;
static double lastX;
static double lastY;

static std::map<std::string, int> stringToGlfwInput
{
	{"Escape", GLFW_KEY_ESCAPE},
	{"w", GLFW_KEY_W},
	{"s", GLFW_KEY_S},
	{"a", GLFW_KEY_A},
	{"d", GLFW_KEY_D},
	{"q", GLFW_KEY_Q},
	{"e", GLFW_KEY_E}
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

static void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	xOffset = xPos - lastX;
	yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;
}