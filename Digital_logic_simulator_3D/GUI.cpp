#include "GUI.h"

GUI::GUI(){}

void GUI::init(DigitalLogic* _digitalLogic){
	digitalLogic = _digitalLogic;
	textBox.text = "test";
	textBox.position = glm::vec2(0, 0);
	textBox.size = glm::vec2(800, 200);
}

void GUI::updateButtons(glm::vec2 mousePosInWindow){
	if (buttons.checkButtons(mousePosInWindow)) {
		switch (buttons.getButtonCommand(mousePosInWindow)) {
		case exitCommand:
			EXIT = true;
			break;
		case saveCommand:
			if (currentFileName != "") {
				loadAndSaveWorkspace.saveWorkSpace(digitalLogic->getComponentsPointer(), currentFileName);
			}
			break;
		case saveAsCommand:
			loadAndSaveWorkspace.saveWorkSpace(digitalLogic->getComponentsPointer(), textBox.text);
			loadMainMenu();
			currentFileName = textBox.text;
			menuState = mainMenu;
			break;
		case loadCommand:
			digitalLogic->clearComponents();
			loadAndSaveWorkspace.loadWorkSpace(digitalLogic->getComponentsPointer(), textBox.text);
			loadMainMenu();
			currentFileName = textBox.text;
			menuState = mainMenu;
			break;
		case loadMenuCommand:
			menuState = loadMenu;
			loadLoadMenu();
			textBox.text = "";
			inputString = "";
			loadAndSaveWorkspace.indexFiles("savedWorkspaces/");
			savedFiles = loadAndSaveWorkspace.getFileNames();
			break;
		case saveMenuCommand:
			loadSaveMenu();
			menuState = saveMenu;
			textBox.text = "";
			inputString = "";
			loadAndSaveWorkspace.indexFiles("savedWorkspaces/");
			savedFiles = loadAndSaveWorkspace.getFileNames();
			break;
		case mainMenuCommand:
			loadMainMenu();
			menuState = mainMenu;
			break;
		case helpMenuCommand:
			loadHelpMenu();
			menuState = helpMenu;
			break;
		}
	}
}

void GUI::updateTextBox() {
	textBox.text = globals::input.inputString;
}

void GUI::loadMainMenu(){
	buttons.buttons.clear();
	buttons.addButton(90, glm::vec2(0, -400), glm::vec2(800, 200), loadMenuCommand);
	buttons.addButton(93, glm::vec2(0, -200), glm::vec2(800, 200), saveCommand);
	buttons.addButton(91, glm::vec2(0, 100), glm::vec2(800, 200), saveMenuCommand);
	buttons.addButton(95, glm::vec2(0, 200), glm::vec2(800, 200), helpMenuCommand);
	buttons.addButton(92, glm::vec2(0, 400), glm::vec2(800, 200), exitCommand);
}

void GUI::loadSaveMenu() {
	buttons.buttons.clear();
	buttons.addButton(93, glm::vec2(0, 0), glm::vec2(800, 200), saveAsCommand);
	buttons.addButton(97, glm::vec2(0, 200), glm::vec2(800, 200), mainMenuCommand);
}
void GUI::loadLoadMenu() {
	buttons.buttons.clear();

	buttons.addButton(96, glm::vec2(0, 0), glm::vec2(800, 200), loadCommand);
	buttons.addButton(97, glm::vec2(0, 200), glm::vec2(800, 200), mainMenuCommand);
}
void GUI::loadHelpMenu() {
	buttons.buttons.clear();
	buttons.addButton(97, glm::vec2(0, 0), glm::vec2(800, 200), mainMenuCommand);
}

void GUI::drawGUI(){
	//buttons
	for (int i = 0; i < buttons.buttons.size(); i++) {
		globals::gfx.quickDrawPixelCoordinates(glm::vec3(buttons.buttons[i]->position.x, buttons.buttons[i]->position.y, 0), buttons.buttons[i]->modelIndex);
	}
	//textBox:
	globals::gfx.drawString(textBox.text, textBox.position.x, textBox.position.y);
}
