#pragma once
#include <GLFW/glfw3.h>
#include <map>

#include "Logger.h"

extern GLFWwindow* inputWindowRef;
extern bool windowAssigned;

extern double xOffset;
extern double yOffset;
extern double lastX;
extern double lastY;

extern bool moved;
extern bool camForward;
extern bool camBackward;
extern bool camLeft;
extern bool camRight;
extern bool camUp;
extern bool camDown;
extern bool locked;

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

	moved = true;
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		locked = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		locked = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W)
	{
		if (action == GLFW_PRESS)
			camForward = true;
		if (action == GLFW_RELEASE)
			camForward = false;
	}
	if (key == GLFW_KEY_S)
	{
		if (action == GLFW_PRESS)
			camBackward = true;
		if (action == GLFW_RELEASE)
			camBackward = false;
	}
	if (key == GLFW_KEY_A)
	{
		if (action == GLFW_PRESS)
			camLeft = true;
		if (action == GLFW_RELEASE)
			camLeft = false;
	}
	if (key == GLFW_KEY_D)
	{
		if (action == GLFW_PRESS)
			camRight = true;
		if (action == GLFW_RELEASE)
			camRight = false;
	}
	if (key == GLFW_KEY_Q)
	{
		if (action == GLFW_PRESS)
			camUp = true;
		if (action == GLFW_RELEASE)
			camUp = false;
	}
	if (key == GLFW_KEY_E)
	{
		if (action == GLFW_PRESS)
			camDown = true;
		if (action == GLFW_RELEASE)
			camDown = false;
	}
}