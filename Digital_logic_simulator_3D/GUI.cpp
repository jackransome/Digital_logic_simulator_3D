#include "GUI.h"

GUI::GUI(){}

void GUI::init(DigitalLogic* _digitalLogic){
	digitalLogic = _digitalLogic;
}

void GUI::updateButtons(){
	if (buttons.checkButtons(globals::input.mousePosInWindow)) {
		switch (buttons.getButtonCommand(globals::input.mousePosInWindow)) {
		case exitCommand:
			EXIT = true;
			break;
		case saveCommand:
			if (currentFileName != "") {
				loadAndSaveWorkspace.saveWorkSpace(digitalLogic->getComponentsPointer(), currentFileName);
			}
			break;
		case saveAsCommand:
			loadAndSaveWorkspace.saveWorkSpace(digitalLogic->getComponentsPointer(), textBoxs[0].text);
			currentFileName = textBoxs[0].text;
			loadMainMenu();
			break;
		case loadCommand:
			digitalLogic->clearComponents();
			loadAndSaveWorkspace.loadWorkSpace(digitalLogic, textBoxs[0].text);
			currentFileName = textBoxs[0].text;
			loadMainMenu();
			break;
		case loadMenuCommand:
			loadLoadMenu();
			textBoxs[0].text = "";
			loadAndSaveWorkspace.indexFiles("savedWorkspaces/");
			savedFiles = loadAndSaveWorkspace.getFileNames();
			break;
		case saveMenuCommand:
			loadSaveMenu();
			textBoxs[0].text = "";
			loadAndSaveWorkspace.indexFiles("savedWorkspaces/");
			savedFiles = loadAndSaveWorkspace.getFileNames();
			break;
		case mainMenuCommand:
			loadMainMenu();
			break;
		case helpMenuCommand:
			loadHelpMenu();
			break;
		}
	}
}

void GUI::checkTextBoxs() {
	for (int i = 0; i < textBoxs.size(); i++) {
		if (globals::input.mousePosInWindow.x > textBoxs[i].position.x && globals::input.mousePosInWindow.x < textBoxs[i].position.x + textBoxs[i].size.x && globals::input.mousePosInWindow.y > textBoxs[i].position.y && globals::input.mousePosInWindow.y < textBoxs[i].position.y + textBoxs[i].size.y) {
			textBoxs[i].infocus = true;
		}
		else {
			textBoxs[i].infocus = false;
		}
	}
}

void GUI::updateTextBoxs(){
	for (int i = 0; i < textBoxs.size(); i++) {
		updateTextBox(&textBoxs[i]);
	}
}

void GUI::updateTextBox(Textbox* _textBox) {
	if (_textBox->infocus) {
		globals::input.stringInputEnabled = true;
		_textBox->text = globals::input.inputString;
	}
	else {
		globals::input.stringInputEnabled = false;
	}
}

void GUI::loadMainMenu(){
	menuState = mainMenu;
	buttons.buttons.clear();
	textBoxs.clear();
	buttons.addButton(92, glm::vec2(-200, -300), glm::vec2(400, 100), loadMenuCommand);
	buttons.addButton(95, glm::vec2(-200, -150), glm::vec2(400, 100), saveCommand);
	buttons.addButton(93, glm::vec2(-200, 0), glm::vec2(400, 100), saveMenuCommand);
	buttons.addButton(97, glm::vec2(-200, 150), glm::vec2(400, 100), helpMenuCommand);
	buttons.addButton(94, glm::vec2(-200, 300), glm::vec2(400, 100), exitCommand);
}

void GUI::loadSaveMenu() {
	menuState = saveMenu;
	buttons.buttons.clear();
	textBoxs.clear();
	Textbox temp;
	temp.text = "";
	temp.position = glm::vec2(-400, -150);
	temp.size = glm::vec2(800, 75);
	temp.infocus = false;
	textBoxs.push_back(temp);
	globals::input.clearInputString();
	buttons.addButton(95, glm::vec2(-200, 0), glm::vec2(400, 100), saveAsCommand);
	buttons.addButton(99, glm::vec2(-200, 150), glm::vec2(400, 100), mainMenuCommand);
}
void GUI::loadLoadMenu() {
	menuState = loadMenu;
	buttons.buttons.clear();
	textBoxs.clear();
	Textbox temp;
	temp.text = "";
	temp.position = glm::vec2(-400, -150);
	temp.size = glm::vec2(800, 75);
	temp.infocus = false;
	textBoxs.push_back(temp);
	globals::input.clearInputString();
	buttons.addButton(98, glm::vec2(-200, 0), glm::vec2(400, 100), loadCommand);
	buttons.addButton(99, glm::vec2(-200, 150), glm::vec2(400, 100), mainMenuCommand);
}
void GUI::loadHelpMenu() {
	menuState = helpMenu;
	buttons.buttons.clear();
	textBoxs.clear();
	buttons.addButton(99, glm::vec2(-200, 0), glm::vec2(40, 100), mainMenuCommand);
}

void GUI::drawGUI(){
	//headers
	switch (menuState) {
	case mainMenu:
		globals::gfx.quickDrawPixelCoordinates(glm::vec3(0 - 1940 / 4, -450, 0), glm::vec3(0.5, 0.5, 1), 23);
		break;
	case saveMenu:
		globals::gfx.quickDrawPixelCoordinates(glm::vec3(0 - 1940 / 4, -450, 0), glm::vec3(0.5, 0.5, 1), 24);
		break;
	case loadMenu:
		globals::gfx.quickDrawPixelCoordinates(glm::vec3(0 - 1940 / 4, -450, 0), glm::vec3(0.5, 0.5, 1), 25);
		break;
	case helpMenu:
		globals::gfx.quickDrawPixelCoordinates(glm::vec3(-1596/4, -1308/4, 0), glm::vec3(0.5, 0.5, 1), 26);
		break;
	}
	//buttons
	for (int i = 0; i < buttons.buttons.size(); i++) {
		globals::gfx.quickDrawPixelCoordinates(glm::vec3(buttons.buttons[i]->position.x, buttons.buttons[i]->position.y, 0), glm::vec3(0.5, 0.5, 1), buttons.buttons[i]->modelIndex);
	}
	//textBox:
	for (int i = 0; i < textBoxs.size(); i++) {
		drawTextBox(textBoxs[i]);
	}
}


void GUI::drawTextBox(Textbox _textBox) {
	if (_textBox.text == "") {
		globals::gfx.quickDrawPixelCoordinates(glm::vec3(_textBox.position.x + _textBox.size.x / 2 - 637 / 4, _textBox.position.y + _textBox.size.y / 2 - 67 / 4, 0), glm::vec3(0.5, 0.5, 1), 22);
		//drawFlatImage(_Textbox.position.x + _Textbox.size.x / 2 - 637 / 2, _Textbox.position.y + _Textbox.size.y / 2 - 67 / 2, 637, 67, glm::vec2(286, 749), glm::vec2(286 + 637, 749 + 67));
	}
	globals::gfx.drawString(_textBox.text, _textBox.position.x + _textBox.size.x / 2 - (_textBox.text.size() / 2) * 20, _textBox.position.y + _textBox.size.y / 2 - 55 / 4, 0.5);
	//drawString(_textBox.text, glm::vec2(_textBox.position.x + _textBox.size.x / 2 - (_textBox.text.size() / 2) * 40, _textBox.position.y + _textBox.size.y / 2 - 55 / 2));
	globals::gfx.quickDrawPixelCoordinates(glm::vec3(_textBox.position.x, _textBox.position.y, 0), glm::vec3(_textBox.size.x, _textBox.size.y, 1), 101);
	if (_textBox.infocus) {
		globals::gfx.quickDrawPixelCoordinates(glm::vec3(_textBox.position.x - 4, _textBox.position.y - 4, 0), glm::vec3(_textBox.size.x + 8, _textBox.size.y + 8, 1), 100);
	}
	else {
		globals::gfx.quickDrawPixelCoordinates(glm::vec3(_textBox.position.x - 4, _textBox.position.y - 4, 0), glm::vec3(_textBox.size.x + 8, _textBox.size.y + 8, 1), 102);
	}
	
	//drawRect(_textBox.position.x, _textBox.position.y, _textBox.size.x, _textBox.size.y, 1, 1, 1);
	
	//drawRect(_textBox.position.x - 8, _textBox.position.y - 8, _textBox.size.x + 16, _textBox.size.y + 16, 0, 0, 0);
}