#pragma once
#include <GLFW/glfw3.h>

extern double deltaTime;
static double lastFrame = 0.0;

static void updateDeltaTime()
{
	double currentFrame = glfwGetTime();

	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}