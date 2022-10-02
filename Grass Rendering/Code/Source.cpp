#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "Graphics/Window.h"
#include "Interface/Console.h"
#include "Interface/FrameRate.h"
#include "Interface/CamControls.h"
#include "Interface/GrassDetails.h"
#include "Interface/SkyboxPicker.h"
#include "Graphics/Shader.h"
#include "Utility/DeltaTime.h"
#include "Objects/Quad.h"
#include "Utility/Input.h"
#include "Graphics/Camera.h"
#include "Objects/SkyBox.h"
#include "Objects/Grass.h"

int WinMain()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	logMessage("Program Started.", "MAIN");

	Window window(1920, 1080, "Test Window", true, true);

	if (window.isCreated())
	{
		imgui = new ImGuiWrapper(window.getGlfwWindow());
		
		inputWindowRef = window.getGlfwWindow();
		windowAssigned = true;

		Console      console;
		FrameRate    fps;
		CamControls  cCtrls;
		GrassDetails gDet;
		SkyboxPicker spbr;

		Texture texture("Content/Textures/test.png");

		SkyBox skybox("Content/Textures/interstellar_skybox", ".png");
		spbr.attachSkyBox(&skybox);

		/*
		int grassCount = 5;
		for (int i = 0; i < grassCount; i++)
		{
			for (int j = 0; j < grassCount; j++)
			{
				Grass* grass = new Grass;

				grass->setPosition((float)i, (float)j, 0.0f);

				gDet.attachGrass(grass);
			}
		}*/
		Grass grass;
		gDet.attachGrass(&grass);

		Camera camera;
		cCtrls.attachCamera(&camera);

		while (!window.isClosing())
		{
			updateDeltaTime();

			camera.move();

			if(locked)
				camera.look();

			window.clear();

			glm::mat4 view = camera.getView();
			for (int i = 0; i < objects.size(); i++)
			{
				objects[i]->updateView(view);
				objects[i]->draw();
			}

			glm::mat4 skyBoxView = glm::mat4(glm::mat3(view));
			skybox.updateView(skyBoxView);
			skybox.draw();

			grass.updatePositions(camera.getPos());

			imgui->drawObjects();

			window.swap();
			window.poll();
		}
		imgui->destroy();
	}
	glfwTerminate();

	logMessage("Program closing.", "MAIN");

	return 0;
}


/*
* Perhaps set an fps limit of 120 (implement the deltatime accumulator thingy).
* This gives a tangable performance target that is definitely high enough for most.
* 
* From BOTW - Culling (with camera distance) uses randomness/noise to avoid obvious hard cut.
* 
* Use worley noise for wind.
TO DO:
------
+ Get grass moving with the plane.
+ See how the program then handles multiple grass objects.
	+ If good then proceed as is.
	+ If bad, then the planes will be a vector for the grass as a whole
	  (rather than multiple grass obejcts each with their own plane).
+ Now can figure out how to perform culling and chunking to get an large tilable area
+ Now optimize and update so that the tileable area can be infinite.
+ Last main feature! change the planes to be any 3D geometry
	+ This is so i can create procedural terrain and put grass on it.
+ Look into ways of creating and using noise that won't mean you're stealing shader code
	+ Should be some tutorials that will get you a very similar result with non-infringing code.
	+ Just need to include the license (MIT) and credit.
*/