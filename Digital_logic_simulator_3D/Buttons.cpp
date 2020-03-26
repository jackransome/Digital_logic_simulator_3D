#include "Buttons.h"

void Buttons::addButton(int _modelIndex, glm::vec2 _position, glm::vec2 _dimensions, buttonCommand _command) {
	buttons.push_back(new Button(_modelIndex, _position, _dimensions, _command));
}

bool Buttons::checkButtons(glm::vec2 _mousePos) {
	for (int i = 0; i < buttons.size(); i++) {
		if (_mousePos.x >= buttons[i]->position.x && _mousePos.y >= buttons[i]->position.y && _mousePos.x <= buttons[i]->position.x + buttons[i]->dimensions.x && _mousePos.y <= buttons[i]->position.y + buttons[i]->dimensions.y) {
			return true;
		}
	}
	return false;
}

buttonCommand Buttons::getButtonCommand(glm::vec2 _mousePos) {
	for (int i = 0; i < buttons.size(); i++) {
		if (_mousePos.x >= buttons[i]->position.x && _mousePos.y >= buttons[i]->position.y && _mousePos.x <= buttons[i]->position.x + buttons[i]->dimensions.x && _mousePos.y <= buttons[i]->position.y + buttons[i]->dimensions.y) {
			return buttons[i]->command;
		}
	}
	//Why is this here?? \/
	return exitCommand;
}
