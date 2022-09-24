#pragma once
#include <GLFW/glfw3.h>

static double deltaTime = 0.0;
static double lastFrame = 0.0;

static void updateDeltaTime()
{
	double currentFrame = glfwGetTime();

	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}