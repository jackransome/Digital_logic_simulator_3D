#pragma once
#include "glm\glm.hpp"
//enum for all the different things a button can do
enum buttonCommand { exitCommand, saveCommand, loadCommand, saveMenuCommand, loadMenuCommand, mainMenuCommand, saveAsCommand, helpMenuCommand };
class Button {
public:
	Button(int _modelIndex, glm::vec2 _position, glm::vec2 _dimensions, buttonCommand _command);
	int modelIndex;
	glm::vec2 position;
	glm::vec2 dimensions;
	buttonCommand command;
};