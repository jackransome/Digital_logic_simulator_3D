#pragma once
#include "Buttons.h"
#include "Textbox.h"
#include "loadAndSaveWorkSpace.h"
#include "DigitalLogic.h"
#include "Globals.h"

enum MenuState { loadMenu, saveMenu, mainMenu, helpMenu };

class GUI {
public:
	GUI();
	void init(DigitalLogic* _digitalLogic);
	void updateButtons();
	void checkTextBoxs();
	void updateTextBoxs();
	void updateTextBox(Textbox* _textBox);
	void loadMainMenu();
	void loadLoadMenu();
	void loadSaveMenu();
	void loadHelpMenu();
	void drawGUI();

	bool EXIT;
private:
	void drawTextBox(Textbox _textBox);
	void drawDisplayTextBox(int x, int y, int width, int height);
	Buttons buttons;
	LoadAndSaveWorkspace loadAndSaveWorkspace;
	std::string currentFileName = "";
	MenuState menuState = mainMenu;
	DigitalLogic* digitalLogic;
	std::vector<Textbox> textBoxs;
	//vector containing the filename's of all saved workspaces
	std::vector<std::string> savedFiles;

};