#pragma once
#include <vector>
#include "Component.h"
#include "Globals.h"
#include "DigitalLogic.h"

//TODO
//adding a component should create a wiregroup or gate for it
//deleting a component should remove it from its wiregroup / gate and remove that wiregroup / gate if it was the last component in it
//finish checkDrawChanges

class CircuitManager {
public:
	CircuitManager();
	void init();
	void addComponent(int _x, int _y, int _z, componentType _type);
	void addComponent(int _x, int _y, int _z, componentType _type, componentDirection _direction);
	bool removeComponent(int _x, int _y, int _z);
	bool removeComponent(int _index);
	int getVectorSize();
	int getComponent(int _x, int _y, int _z);
	void updateModels();
	void runLogic();
	void checkDrawChanges();
	void clearComponents();
	componentType getComponentType(int _x, int _y, int _z);
	bool getComponentState(int _x, int _y, int _z);
	void setComponentState(int _x, int _y, int _z, bool _state);
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