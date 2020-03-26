#include "Input.h"
#include <iostream>

void Input::init(GLFWwindow * window)
{
	windowPointer = window;
}
//======================================================================||
// function that uses glfw to get key inputs (presses and releases) and ||
// uses them to set the KeyValues struct's properties, so that anywhere ||
// I to know what keys are pressed, I can just find out using the       ||
// keyValues struct.                                                    ||
//======================================================================||

void Input::run() {
	glfwPollEvents();
	glfwGetCursorPos(windowPointer, &xpos, &ypos);
	if (inFocus && !inMenu) {
		glfwSetCursorPos(windowPointer, windowWidth / 2, windowHeight / 2);
		cameraAngle.x += 0.003f * float(windowWidth / 2 - xpos);
		cameraAngle.y += 0.003f * float(windowHeight / 2 - ypos);
		if (cameraAngle.y < -3.14f / 2.0f) {
			cameraAngle.y = -3.14f / 2.0f;
		}
		if (cameraAngle.y > 3.14f / 2.0f) {
			cameraAngle.y = 3.14f / 2.0f;
		}
		glfwSetInputMode(windowPointer, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		keys.updateCounts();
	}
	else {
		if (inFocus) {
			keys.updateCounts();
		}
		glfwSetInputMode(windowPointer, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	glfwGetFramebufferSize(windowPointer, &windowWidth, &windowHeight);
	mousePosInWindow = glm::vec2((xpos - windowWidth / 2), (ypos - windowHeight / 2));
	//mousePosInWindow = glm::vec2(xpos, ypos);
}

void Input::clearInputString() {
	inputString = "";
}
//Callback function for scrolling with the mouse
void Input::scroll_callback(double xoffset, double yoffset)
{
	if (yoffset != 0) {
		mouseScrollValue = yoffset;
	}
}
//Callback function for all keyboard input
void Input::key_callback(int key, int scancode, int action, int mods)
{
	//Code for allowing the user to type out strings (for a textbox)
	if (stringInputEnabled) {
		if (action == GLFW_PRESS) {
			if (key == GLFW_KEY_A ||
				key == GLFW_KEY_B ||
				key == GLFW_KEY_C ||
				key == GLFW_KEY_D ||
				key == GLFW_KEY_E ||
				key == GLFW_KEY_F ||
				key == GLFW_KEY_G ||
				key == GLFW_KEY_H ||
				key == GLFW_KEY_I ||
				key == GLFW_KEY_J ||
				key == GLFW_KEY_K ||
				key == GLFW_KEY_L ||
				key == GLFW_KEY_M ||
				key == GLFW_KEY_N ||
				key == GLFW_KEY_O ||
				key == GLFW_KEY_P ||
				key == GLFW_KEY_Q ||
				key == GLFW_KEY_R ||
				key == GLFW_KEY_S ||
				key == GLFW_KEY_T ||
				key == GLFW_KEY_U ||
				key == GLFW_KEY_V ||
				key == GLFW_KEY_W ||
				key == GLFW_KEY_X ||
				key == GLFW_KEY_Y ||
				key == GLFW_KEY_Z ||
				key == GLFW_KEY_1 ||
				key == GLFW_KEY_2 ||
				key == GLFW_KEY_3 ||
				key == GLFW_KEY_4 ||
				key == GLFW_KEY_5 ||
				key == GLFW_KEY_6 ||
				key == GLFW_KEY_7 ||
				key == GLFW_KEY_8 ||
				key == GLFW_KEY_9 ||
				key == GLFW_KEY_0 ||
				key == GLFW_KEY_MINUS
				) {
				if (keys.keyCounts["leftShift"] || keys.keyCounts["rightShift"]) {
					if (key == GLFW_KEY_MINUS) {
						inputString += "_";
					}
					else {
						inputString += glfwGetKeyName(key, 0)[0];
					}
				}
				else {
					if (glfwGetKeyName(key, 0)[0] > 64) {
						inputString += glfwGetKeyName(key, 0)[0] + 32;
					}
					else {
						if (key == GLFW_KEY_MINUS) {
							inputString += "-";
						}
						else {
							inputString += glfwGetKeyName(key, 0)[0];
						}
					}
				}
			}
			if (key == GLFW_KEY_SPACE) {
				inputString += " ";
			}
			if (key == GLFW_KEY_BACKSPACE && inputString.size() > 0) {
				inputString.resize(inputString.size() - 1);
				if (keys.keyCounts["leftCtrl"]) {
					inputString = "";
				}
			}
		}
	}

	switch (key)
	{
	case GLFW_KEY_1:
		keys.performAction(keys.keyCounts["n1"], action);
		break;
	case GLFW_KEY_2:
		keys.performAction(keys.keyCounts["n2"], action);
		break;
	case GLFW_KEY_3:
		keys.performAction(keys.keyCounts["n3"], action);
		break;
	case GLFW_KEY_4:
		keys.performAction(keys.keyCounts["n4"], action);
		break;
	case GLFW_KEY_5:
		keys.performAction(keys.keyCounts["n5"], action);
		break;
	case GLFW_KEY_6:
		keys.performAction(keys.keyCounts["n6"], action);
		break;
	case GLFW_KEY_7:
		keys.performAction(keys.keyCounts["n7"], action);
		break;
	case GLFW_KEY_8:
		keys.performAction(keys.keyCounts["n8"], action);
		break;
	case GLFW_KEY_9:
		keys.performAction(keys.keyCounts["n9"], action);
		break;
	case GLFW_KEY_0:
		keys.performAction(keys.keyCounts["n0"], action);
		break;
	case GLFW_KEY_LEFT_ALT:
		keys.performAction(keys.keyCounts["leftAlt"], action);
		break;
	case GLFW_KEY_ESCAPE:
		keys.performAction(keys.keyCounts["escape"], action);
		break;
	case GLFW_KEY_SPACE:
		keys.performAction(keys.keyCounts["space"], action);
		break;
	case GLFW_KEY_LEFT_SHIFT:
		keys.performAction(keys.keyCounts["leftShift"], action);
		break;
	case GLFW_KEY_RIGHT_SHIFT:
		keys.performAction(keys.keyCounts["rightShift"], action);
		break;
	case GLFW_KEY_LEFT_CONTROL:
		keys.performAction(keys.keyCounts["leftCtrl"], action);
		break;
	case GLFW_KEY_TAB:
		keys.performAction(keys.keyCounts["tab"], action);
		break;
	case GLFW_KEY_LEFT:
		keys.performAction(keys.keyCounts["leftArrow"], action);
		break;
	case GLFW_KEY_RIGHT:
		keys.performAction(keys.keyCounts["rightArrow"], action);
		break;
	case GLFW_KEY_UP:
		keys.performAction(keys.keyCounts["upArrow"], action);
		break;
	case GLFW_KEY_DOWN:
		keys.performAction(keys.keyCounts["downArrow"], action);
		break;
	case GLFW_KEY_A:
		keys.performAction(keys.keyCounts["a"], action);
		break;
	case GLFW_KEY_B:
		keys.performAction(keys.keyCounts["b"], action);
		break;
	case GLFW_KEY_C:
		keys.performAction(keys.keyCounts["c"], action);
		break;
	case GLFW_KEY_D:
		keys.performAction(keys.keyCounts["d"], action);
		break;
	case GLFW_KEY_E:
		keys.performAction(keys.keyCounts["e"], action);
		break;
	case GLFW_KEY_F:
		keys.performAction(keys.keyCounts["f"], action);
		break;
	case GLFW_KEY_G:
		keys.performAction(keys.keyCounts["g"], action);
		break;
	case GLFW_KEY_H:
		keys.performAction(keys.keyCounts["h"], action);
		break;
	case GLFW_KEY_I:
		keys.performAction(keys.keyCounts["i"], action);
		break;
	case GLFW_KEY_J:
		keys.performAction(keys.keyCounts["j"], action);
		break;
	case GLFW_KEY_K:
		keys.performAction(keys.keyCounts["k"], action);
		break;
	case GLFW_KEY_L:
		keys.performAction(keys.keyCounts["l"], action);
		break;
	case GLFW_KEY_M:
		keys.performAction(keys.keyCounts["m"], action);
		break;
	case GLFW_KEY_N:
		keys.performAction(keys.keyCounts["n"], action);
		break;
	case GLFW_KEY_O:
		keys.performAction(keys.keyCounts["o"], action);
		break;
	case GLFW_KEY_P:
		keys.performAction(keys.keyCounts["p"], action);
		break;
	case GLFW_KEY_Q:
		keys.performAction(keys.keyCounts["q"], action);
		break;
	case GLFW_KEY_R:
		keys.performAction(keys.keyCounts["r"], action);
		break;
	case GLFW_KEY_S:
		keys.performAction(keys.keyCounts["s"], action);
		break;
	case GLFW_KEY_T:
		keys.performAction(keys.keyCounts["t"], action);
		break;
	case GLFW_KEY_U:
		keys.performAction(keys.keyCounts["u"], action);
		break;
	case GLFW_KEY_V:
		keys.performAction(keys.keyCounts["v"], action);
		break;
	case GLFW_KEY_W:
		keys.performAction(keys.keyCounts["w"], action);
		break;
	case GLFW_KEY_X:
		keys.performAction(keys.keyCounts["x"], action);
		break;
	case GLFW_KEY_Y:
		keys.performAction(keys.keyCounts["y"], action);
		break;
	case GLFW_KEY_Z:
		keys.performAction(keys.keyCounts["z"], action);
		break;
	}
}

//Callback function for mouse click input
void Input::mouse_button_callback(int button, int action, int mods)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		//keys.mouseLeft = action & (GLFW_PRESS | GLFW_REPEAT);
		keys.performAction(keys.keyCounts["mouseLeft"], action);
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		keys.performAction(keys.keyCounts["mouseRight"], action);
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		keys.performAction(keys.keyCounts["mouseMiddle"], action);
		break;
	}
}

//Another callback, this time for detecting whether or not the window is in focus
void Input::window_focus_callback(int focused)
{
	if (focused)
	{
		inFocus = true;
	}
	else
	{
		inFocus = false;
	}
}