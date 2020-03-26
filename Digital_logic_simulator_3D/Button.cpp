#include "Button.h"

//initialises the button
Button::Button(int _modelIndex, glm::vec2 _position, glm::vec2 _dimensions, buttonCommand _command) {
	modelIndex = _modelIndex;
	position = _position;
	dimensions = _dimensions;
	command = _command;
}