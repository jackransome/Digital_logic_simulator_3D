#pragma once

#include <GLFW\glfw3.h>
#include <string>
#include <glm\glm.hpp>
#include <iostream>
#include <algorithm>
#include <map>

struct KeyCounts
{
	std::map<std::string, int> keyCounts;

	explicit KeyCounts()
	{
		keyCounts["a"] = 0;
		keyCounts["b"] = 0;
		keyCounts["c"] = 0;
		keyCounts["d"] = 0;
		keyCounts["e"] = 0;
		keyCounts["f"] = 0;
		keyCounts["g"] = 0;
		keyCounts["h"] = 0;
		keyCounts["i"] = 0;
		keyCounts["j"] = 0;
		keyCounts["k"] = 0;
		keyCounts["l"] = 0;
		keyCounts["m"] = 0;
		keyCounts["n"] = 0;
		keyCounts["o"] = 0;
		keyCounts["p"] = 0;
		keyCounts["q"] = 0;
		keyCounts["r"] = 0;
		keyCounts["s"] = 0;
		keyCounts["t"] = 0;
		keyCounts["u"] = 0;
		keyCounts["v"] = 0;
		keyCounts["w"] = 0;
		keyCounts["x"] = 0;
		keyCounts["y"] = 0;
		keyCounts["z"] = 0;

		keyCounts["n1"] = 0;
		keyCounts["n2"] = 0;
		keyCounts["n3"] = 0;
		keyCounts["n4"] = 0;
		keyCounts["n5"] = 0;
		keyCounts["n6"] = 0;
		keyCounts["n7"] = 0;
		keyCounts["n8"] = 0;
		keyCounts["n9"] = 0;
		keyCounts["n0"] = 0;

		keyCounts["leftShift"] = 0;
		keyCounts["rightShift"] = 0;
		keyCounts["space"] = 0;
		keyCounts["leftCtrl"] = 0;
		keyCounts["tab"] = 0;
		keyCounts["leftAlt"] = 0;
		keyCounts["escape"] = 0;

		keyCounts["mouseLeft"] = 0;
		keyCounts["mouseRight"] = 0;
		keyCounts["mouseMiddle"] = 0;

		keyCounts["leftArrow"] = 0;
		keyCounts["rightArrow"] = 0;
		keyCounts["upArrow"] = 0;
		keyCounts["downArrow"] = 0;
	}

	void performAction(int& keyCount, int action)
	{
		if (action & (GLFW_PRESS | GLFW_REPEAT))
		{
			if (keyCount == 0)
			{
				keyCount = -1;
			}
		}
		else
		{
			keyCount = 0;
		}
	}

	void updateCounts()
	{
		for (auto& keyValuePair : keyCounts)
		{
			if (keyValuePair.second == -1)
			{
				keyValuePair.second = 1;
			}
			else if (keyValuePair.second > 0)
			{
				keyValuePair.second++;
			}
		}
	}
};

class Input
{
public:
	std::string inputString = "";
	KeyCounts keys;
	bool stringInputEnabled = true;
	bool EXIT = false;
	void run();
	double xpos, ypos;
	glm::vec3 cameraAngle = glm::vec3(0, 0, 0);
	int windowWidth, windowHeight;
	glm::vec2 mousePosInWindow;
	void init(GLFWwindow* window);
	GLFWwindow* windowPointer;
	void clearInputString();
	void scroll_callback(double xoffset, double yoffset);
	void key_callback(int key, int scancode, int action, int mods);
	void mouse_button_callback(int button, int action, int mods);
	bool inFocus = true;
	void window_focus_callback(int focused);
private:
	int mouseScrollValue = 0;
};
