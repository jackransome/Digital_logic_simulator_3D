#include "Globals.h"

#include <windows.h>
#include <chrono>
#include <stdio.h>

#include "ComponentManipulation.h"
#include "GUI.h"

using std::chrono::time_point_cast;
using std::chrono::duration_cast;

const bool debug = false;

int main()
{
	using std::make_shared;

	try
	{
		typedef std::chrono::high_resolution_clock Time;
		typedef std::chrono::microseconds us;

		globals::globalInit();

		auto currentTime = time_point_cast<us>(Time::now());
		double accumulator = 0.0;

		glm::vec3 cameraOffset{ 0, 2, 0 };

		glm::vec3 cameraPos = glm::vec3(0, 0, 0);

		DigitalLogic digitalLogic;
		GUI gui;
		gui.init(&digitalLogic);
		gui.loadMainMenu();
		ComponentManipulation componentManipulation;
		componentManipulation.init(&digitalLogic);
		digitalLogic.init();

		componentType componentTypeSelected = wire;

		//the green origin model
		globals::gfx.addObject(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 2);
		glm::vec3 cameraDirection;
		while (!globals::gfx.shouldClose && !gui.EXIT) {
			auto newTime = time_point_cast<us>(Time::now());
			auto frameTime = duration_cast<us>(newTime - currentTime).count();
			currentTime = newTime;

			accumulator += frameTime;

			while (accumulator >= globals::dt)
			{
				globals::gfx.setCameraAngle(globals::input.cameraAngle);
				globals::input.run();
				globals::gfx.setCameraPos(cameraPos);
				cameraDirection = glm::vec3(
					cos(globals::input.cameraAngle.y) * sin(globals::input.cameraAngle.x),
					sin(globals::input.cameraAngle.y),
					cos(globals::input.cameraAngle.y) * cos(globals::input.cameraAngle.x)
				);
				//getting directions for forward and sideways based on the way the camera is pointed
				glm::vec3 forward = glm::vec3(sin(globals::input.cameraAngle.x), 0, cos(globals::input.cameraAngle.x));
				glm::vec3 right = glm::vec3(
					sin(globals::input.cameraAngle.x - 3.14f / 2.0f),
					0,
					cos(globals::input.cameraAngle.x - 3.14f / 2.0f)
				);

				if (!globals::input.inMenu) {
					if (globals::input.keys.keyCounts["w"]) {
						cameraPos += glm::vec3(forward.x, 0, forward.z) * 0.1f;
					}

					if (globals::input.keys.keyCounts["a"]) {
						cameraPos -= glm::vec3(right.x, 0, right.z) * 0.1f;
					}

					if (globals::input.keys.keyCounts["s"]) {
						cameraPos -= glm::vec3(forward.x, 0, forward.z) * 0.1f;
					}

					if (globals::input.keys.keyCounts["d"]) {
						cameraPos += glm::vec3(right.x, 0, right.z) * 0.1f;
					}

					if (globals::input.keys.keyCounts["leftShift"]) {
						cameraPos.y -= 0.1;
					}

					if (globals::input.keys.keyCounts["space"]) {
						cameraPos.y += 0.1;
					}

					if (globals::input.keys.keyCounts["n1"]) {
						componentTypeSelected = wire;
					}

					if (globals::input.keys.keyCounts["n2"]) {
						componentTypeSelected = inverter;
					}

					if (globals::input.keys.keyCounts["n3"]) {
						componentTypeSelected = andGate;
					}

					if (globals::input.keys.keyCounts["n4"]) {
						componentTypeSelected = orGate;
					}

					if (globals::input.keys.keyCounts["n5"]) {
						componentTypeSelected = xorGate;
					}

					if (globals::input.keys.keyCounts["n6"]) {
						componentTypeSelected = LED;
					}

					if (globals::input.keys.keyCounts["n7"]) {
						componentTypeSelected = button;
					}

					if (globals::input.keys.keyCounts["f"]) {
						digitalLogic.addComponent(cameraPos.x, cameraPos.y, cameraPos.z, wire);
					}

					if (globals::input.keys.keyCounts["mouseRight"] == 1) {
						componentManipulation.deleteComponent(cameraPos, cameraDirection);
					}

					if (globals::input.keys.keyCounts["leftCtrl"] == 1)
					{
						globals::gfx.setObjectsWireFrame(true);
					}
					else if (globals::input.keys.keyCounts["leftCtrl"] == 0)
					{
						globals::gfx.setObjectsWireFrame(false);
					}
				}

				if (globals::input.keys.keyCounts["mouseLeft"] == 1) {
					if (globals::input.inMenu) {
						gui.updateButtons();
						gui.checkTextBoxs();
					}
					else {
						componentManipulation.placeComponent(cameraPos, cameraDirection, componentTypeSelected);
					}
				}

				if (globals::input.keys.keyCounts["mouseMiddle"] == 1) {
					if (!globals::input.inMenu) {
						componentManipulation.switchButton(cameraPos, cameraDirection);
					}
				}

				//mouse pos printing
				//printf("x: %f, y: %f\n", globals::input.mousePosInWindow.x, globals::input.mousePosInWindow.y);

				if (globals::input.keys.keyCounts["escape"] == 1) {
					if (globals::input.inMenu) {
						globals::input.inMenu = false;
					} else{
						globals::input.inMenu = true;
						gui.loadMainMenu();
					}
				}
				if (globals::input.inMenu) {
					gui.updateTextBoxs();
				}
				accumulator -= globals::dt;
			}
			gui.drawGUI(componentTypeSelected);

			globals::gfx.quickDraw(componentManipulation.getNewComponentLocation(cameraPos, cameraDirection), 20, true);
			//draw crosshairs:
			globals::gfx.quickDrawPixelCoordinates(glm::vec3(-10, -1, 0), glm::vec3(20, 2, 0), 103);
			globals::gfx.quickDrawPixelCoordinates(glm::vec3(-1, -10, 0), glm::vec3(2, 20, 0), 103);

			digitalLogic.runLogic();
			digitalLogic.updateModels();
			globals::gfx.run();
		}
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		for (int i = 0; i < 100000000; i++) {}
		return EXIT_FAILURE;
	}

	globals::gfx.cleanup();

	return EXIT_SUCCESS;
}