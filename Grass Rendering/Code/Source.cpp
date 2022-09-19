#include <iostream>
#include "Window.h"

int main()
{
	Window window(800, 800, "Test Window", true, true);

	while (!window.isClosing())
	{
		window.poll();
		window.swap();
	}
}