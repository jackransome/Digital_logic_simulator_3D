#pragma once
#include <vector>
#include "Component.h"
#include "Globals.h"
//blocks class
class DigitalLogic {
public:
	DigitalLogic();
	void init();
	void addComponent(int x, int y, int z, componentType type);
	void addComponent(int x, int y, int z, componentType type, componentDirection direction);
	bool removeComponent(int x, int y, int z);
	bool removeComponent(int _index);
	int getVectorSize();
	int getComponent(int x, int y, int z);
	void updateModels();
	void runLogic();
	void clearComponents();
	std::vector<Component*>* getComponentsPointer();

private:
	
	bool doesComponentExist(int x, int y, int z);
	void checkSurroundingComponents(glm::vec3 block);
	void getInput(int blockIndex, glm::vec3* input);
	void getOutput(int blockIndex, glm::vec3* output);
	void getInputs(int blockIndex, glm::vec3* input1, glm::vec3* input2);
	int getModelIndex(componentType type, bool on);
	std::vector<Component*> components;
};