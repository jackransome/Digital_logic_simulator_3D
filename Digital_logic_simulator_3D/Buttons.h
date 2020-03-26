#pragma once
#include "Button.h"
#include <vector>

class Buttons {
public:
	void addButton(int _modelIndex, glm::vec2 _position, glm::vec2 _dimensions, buttonCommand _command);
	bool checkButtons(glm::vec2 _mousePos);
	buttonCommand getButtonCommand(glm::vec2 _mousePos);
	std::vector<Button*> buttons;
};