#include "Input.h"

GLFWwindow* inputWindowRef;
bool windowAssigned = false;


double xOffset = 0.0;
double yOffset = 0.0;
double lastX   = 960.0;
double lastY   = 540.0;

bool moved       = false;
bool camForward  = false;
bool camBackward = false;
bool camLeft     = false;
bool camRight    = false;
bool camUp       = false;
bool camDown     = false;