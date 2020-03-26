#include "DigitalLogic.h"

DigitalLogic::DigitalLogic() {}
//initialises the DigitalLogic object
void DigitalLogic::init() {
	//addComponent(((double)rand() / (RAND_MAX)) * 120, ((double)rand() / (RAND_MAX)) * 120, ((double)rand() / (RAND_MAX)) * 120, inverter);
}
//adds a block to the vector with direction
void DigitalLogic::addComponent(int x, int y, int z, componentType type) {
	addComponent(x, y, z, type, positiveX);
}
//adds a block to the vector
void DigitalLogic::addComponent(int x, int y, int z, componentType type, componentDirection direction) {
	if (!doesComponentExist(x, y, z)) {
		components.push_back(new Component(x, y, z, type, direction));
		//DIRECTION HERE \/\/\/\/
		glm::vec3 rotation;
		switch (direction) {
		case positiveX:
			rotation = glm::vec3(0, 3.1415, 0);
			break;
		case negativeX:
			rotation = glm::vec3(0, 0, 0);
			break;
		case positiveY:
			rotation = glm::vec3(0, 0, -3.1415/2);
			break;
		case negativeY:
			rotation = glm::vec3(0, 0, 3.1415 / 2);
			break;
		case positiveZ:
			rotation = glm::vec3(0, 3.1415 / 2, 0);
			break;
		case negativeZ:
			rotation = glm::vec3(0, -3.1415 / 2, 0);
			break;
		}
	if (type == wire) {
			//center:
			components[components.size() - 1]->offGraphicsObjectIndex = globals::gfx.addObject(components[components.size() - 1]->position, glm::vec3(1, 1, 1), 16, rotation);
			components[components.size() - 1]->onGraphicsObjectIndex = globals::gfx.addObject(components[components.size() - 1]->position, glm::vec3(1, 1, 1), 17, rotation);
			//PX
			rotation = glm::vec3(0, 3.1415, 0);
			components[components.size() - 1]->wireObjects[0] = globals::gfx.addObject(components[components.size() - 1]->position, glm::vec3(1, 1, 1), getModelIndex(type, false), rotation);
			components[components.size() - 1]->wireObjects[1] = globals::gfx.addObject(components[components.size() - 1]->position, glm::vec3(1, 1, 1), getModelIndex(type, true), rotation);
			//NX
			rotation = glm::vec3(0, 0, 0);
			components[components.size() - 1]->wireObjects[2] = globals::gfx.addObject(components[components.size() - 1]->position, glm::vec3(1, 1, 1), getModelIndex(type, false), rotation);
			components[components.size() - 1]->wireObjects[3] = globals::gfx.addObject(components[components.size() - 1]->position, glm::vec3(1, 1, 1), getModelIndex(type, true), rotation);
			//PY
			rotation = glm::vec3(0, 0, -3.1415 / 2);
			components[components.size() - 1]->wireObjects[4] = globals::gfx.addObject(components[components.size() - 1]->position, glm::vec3(1, 1, 1), getModelIndex(type, false), rotation);
			components[components.size() - 1]->wireObjects[5] = globals::gfx.addObject(components[components.size() - 1]->position, glm::vec3(1, 1, 1), getModelIndex(type, true), rotation);
			//NY
			rotation = glm::vec3(0, 0, 3.1415 / 2);
			components[components.size() - 1]->wireObjects[6] = globals::gfx.addObject(components[components.size() - 1]->position, glm::vec3(1, 1, 1), getModelIndex(type, false), rotation);
			components[components.size() - 1]->wireObjects[7] = globals::gfx.addObject(components[components.size() - 1]->position, glm::vec3(1, 1, 1), getModelIndex(type, true), rotation);
			//PZ
			rotation = glm::vec3(0, 3.1415 / 2, 0);
			components[components.size() - 1]->wireObjects[8] = globals::gfx.addObject(components[components.size() - 1]->position, glm::vec3(1, 1, 1), getModelIndex(type, false), rotation);
			components[components.size() - 1]->wireObjects[9] = globals::gfx.addObject(components[components.size() - 1]->position, glm::vec3(1, 1, 1), getModelIndex(type, true), rotation);
			//NZ
			rotation = glm::vec3(0, -3.1415 / 2, 0);
			components[components.size() - 1]->wireObjects[10] = globals::gfx.addObject(components[components.size() - 1]->position, glm::vec3(1, 1, 1), getModelIndex(type, false), rotation);
			components[components.size() - 1]->wireObjects[11] = globals::gfx.addObject(components[components.size() - 1]->position, glm::vec3(1, 1, 1), getModelIndex(type, true), rotation);
		}
		else {
			components[components.size() - 1]->offGraphicsObjectIndex = globals::gfx.addObject(components[components.size() - 1]->position, glm::vec3(1, 1, 1), getModelIndex(type, false), rotation);
			components[components.size() - 1]->onGraphicsObjectIndex = globals::gfx.addObject(components[components.size() - 1]->position, glm::vec3(1, 1, 1), getModelIndex(type, true), rotation);
		}
	}
}
//gets the seize of the vector
int DigitalLogic::getVectorSize() {
	return components.size();
}
//removes a block from the vector
bool DigitalLogic::removeComponent(int x, int y, int z) {
	if (doesComponentExist(x, y, z)) {
		int index = getComponent(x, y, z);
		globals::gfx.removeObject(components[index]->offGraphicsObjectIndex);
		globals::gfx.removeObject(components[index]->onGraphicsObjectIndex);
		if (components[index]->type == wire) {
			for (int i = 0; i < 12; i++) {
				globals::gfx.removeObject(components[index]->wireObjects[i]);
			}
		}
		components.erase(components.begin() + index);
		return true;
	}
	return false;
}
bool DigitalLogic::removeComponent(int _index)
{
	if (_index >= components.size()) {
		return false;
	}
	globals::gfx.removeObject(components[_index]->offGraphicsObjectIndex);
	globals::gfx.removeObject(components[_index]->onGraphicsObjectIndex);
	if (components[_index]->type == wire) {
		for (int i = 0; i < 12; i++) {
			globals::gfx.removeObject(components[_index]->wireObjects[i]);
		}
	}
	components.erase(components.begin() + _index);
	return true;
}
//checks if a block of a particular position exists in the vector
bool DigitalLogic::doesComponentExist(int x, int y, int z) {
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->position == glm::vec3(x, y, z)) {
			return true;
		}
	}
	return false;
}
//returns the index of the block of a particular position
int DigitalLogic::getComponent(int x, int y, int z) {
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->position == glm::vec3(x, y, z)) {
			return i;
		}
	}
	return -1;
}

void DigitalLogic::updateModels(){
	bool onValue;
	bool offValue;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->state) {
			offValue = false;
			onValue = true;
		}
		else {
			offValue = true;
			onValue = false;
		}
		if (components[i]->type == wire) {
			int componentsConnected = 0;
			if (getComponent(components[i]->position.x - 1, components[i]->position.y, components[i]->position.z) != -1) {
				globals::gfx.setObjectVisible(components[i]->wireObjects[0], offValue);
				globals::gfx.setObjectVisible(components[i]->wireObjects[1], onValue);
				componentsConnected++;
			} else {
				globals::gfx.setObjectVisible(components[i]->wireObjects[0], false);
				globals::gfx.setObjectVisible(components[i]->wireObjects[1], false);
			}
			if (getComponent(components[i]->position.x + 1, components[i]->position.y, components[i]->position.z) != -1) {
				globals::gfx.setObjectVisible(components[i]->wireObjects[2], offValue);
				globals::gfx.setObjectVisible(components[i]->wireObjects[3], onValue);
				componentsConnected++;
			} else {
				globals::gfx.setObjectVisible(components[i]->wireObjects[2], false);
				globals::gfx.setObjectVisible(components[i]->wireObjects[3], false);
			}
			if (getComponent(components[i]->position.x, components[i]->position.y - 1, components[i]->position.z) != -1) {
				globals::gfx.setObjectVisible(components[i]->wireObjects[4], offValue);
				globals::gfx.setObjectVisible(components[i]->wireObjects[5], onValue);
				componentsConnected++;
			} else {
				globals::gfx.setObjectVisible(components[i]->wireObjects[4], false);
				globals::gfx.setObjectVisible(components[i]->wireObjects[5], false);
			}
			if (getComponent(components[i]->position.x, components[i]->position.y + 1, components[i]->position.z) != -1) {
				globals::gfx.setObjectVisible(components[i]->wireObjects[6], offValue);
				globals::gfx.setObjectVisible(components[i]->wireObjects[7], onValue);
				componentsConnected++;
			} else {
				globals::gfx.setObjectVisible(components[i]->wireObjects[6], false);
				globals::gfx.setObjectVisible(components[i]->wireObjects[7], false);
			}
			if (getComponent(components[i]->position.x, components[i]->position.y, components[i]->position.z - 1) != -1) {
				globals::gfx.setObjectVisible(components[i]->wireObjects[8], offValue);
				globals::gfx.setObjectVisible(components[i]->wireObjects[9], onValue);
				componentsConnected++;
			} else {
				globals::gfx.setObjectVisible(components[i]->wireObjects[8], false);
				globals::gfx.setObjectVisible(components[i]->wireObjects[9], false);
			}
			if (getComponent(components[i]->position.x, components[i]->position.y, components[i]->position.z + 1) != -1) {
				globals::gfx.setObjectVisible(components[i]->wireObjects[10], offValue);
				globals::gfx.setObjectVisible(components[i]->wireObjects[11], onValue);
				componentsConnected++;
			} else {
				globals::gfx.setObjectVisible(components[i]->wireObjects[10], false);
				globals::gfx.setObjectVisible(components[i]->wireObjects[11], false);
			}
			if (componentsConnected == 0) {
				globals::gfx.setObjectVisible(components[i]->offGraphicsObjectIndex, true);
				globals::gfx.setObjectVisible(components[i]->onGraphicsObjectIndex, true);
			}
			else {
				globals::gfx.setObjectVisible(components[i]->offGraphicsObjectIndex, false);
				globals::gfx.setObjectVisible(components[i]->onGraphicsObjectIndex, false);
			}
		}
		else {
			globals::gfx.setObjectVisible(components[i]->offGraphicsObjectIndex, offValue);
			globals::gfx.setObjectVisible(components[i]->onGraphicsObjectIndex, onValue);
		}
	}
}

//the function that recurses
void DigitalLogic::checkSurroundingComponents(glm::vec3 block) {
	if (doesComponentExist(block.x + 1, block.y, block.z) && components[getComponent(block.x + 1, block.y, block.z)]->type == wire && components[getComponent(block.x + 1, block.y, block.z)]->state == false) {
		components[getComponent(block.x + 1, block.y, block.z)]->state = true;
		checkSurroundingComponents(glm::vec3(block.x + 1, block.y, block.z));
	}
	if (doesComponentExist(block.x - 1, block.y, block.z) && components[getComponent(block.x - 1, block.y, block.z)]->type == wire && components[getComponent(block.x - 1, block.y, block.z)]->state == false) {
		components[getComponent(block.x - 1, block.y, block.z)]->state = true;
		checkSurroundingComponents(glm::vec3(block.x - 1, block.y, block.z));
	}
	if (doesComponentExist(block.x, block.y + 1, block.z) && components[getComponent(block.x, block.y + 1, block.z)]->type == wire && components[getComponent(block.x, block.y + 1, block.z)]->state == false) {
		components[getComponent(block.x, block.y + 1, block.z)]->state = true;
		checkSurroundingComponents(glm::vec3(block.x, block.y + 1, block.z));
	}
	if (doesComponentExist(block.x, block.y - 1, block.z) && components[getComponent(block.x, block.y - 1, block.z)]->type == wire && components[getComponent(block.x, block.y - 1, block.z)]->state == false) {
		components[getComponent(block.x, block.y - 1, block.z)]->state = true;
		checkSurroundingComponents(glm::vec3(block.x, block.y - 1, block.z));
	}
	if (doesComponentExist(block.x, block.y, block.z + 1) && components[getComponent(block.x, block.y, block.z + 1)]->type == wire && components[getComponent(block.x, block.y, block.z + 1)]->state == false) {
		components[getComponent(block.x, block.y, block.z + 1)]->state = true;
		checkSurroundingComponents(glm::vec3(block.x, block.y, block.z + 1));
	}
	if (doesComponentExist(block.x, block.y, block.z - 1) && components[getComponent(block.x, block.y, block.z - 1)]->type == wire && components[getComponent(block.x, block.y, block.z - 1)]->state == false) {
		components[getComponent(block.x, block.y, block.z - 1)]->state = true;
		checkSurroundingComponents(glm::vec3(block.x, block.y, block.z - 1));
	}
}
//getting the position of the input block, for an inverter
void DigitalLogic::getInput(int blockIndex, glm::vec3 * input)
{
	switch (components[blockIndex]->direction) {
	case positiveX:
		*input = components[blockIndex]->position + glm::vec3(1, 0, 0);
		break;
	case negativeX:
		*input = components[blockIndex]->position + glm::vec3(-1, 0, 0);
		break;
	case positiveY:
		*input = components[blockIndex]->position + glm::vec3(0, 1, 0);
		break;
	case negativeY:
		*input = components[blockIndex]->position + glm::vec3(0, -1, 0);
		break;
	case positiveZ:
		*input = components[blockIndex]->position + glm::vec3(0, 0, 1);
		break;
	case negativeZ:
		*input = components[blockIndex]->position + glm::vec3(0, 0, -1);
		break;
	}
}

//getting the output position of a component, needed as components can have different orientations
void DigitalLogic::getOutput(int blockIndex, glm::vec3 * output)
{
	switch (components[blockIndex]->direction) {
	case positiveX:
		*output = components[blockIndex]->position + glm::vec3(-1, 0, 0);
		break;
	case negativeX:
		*output = components[blockIndex]->position + glm::vec3(1, 0, 0);
		break;
	case positiveY:
		*output = components[blockIndex]->position + glm::vec3(0, -1, 0);
		break;
	case negativeY:
		*output = components[blockIndex]->position + glm::vec3(0, 1, 0);
		break;
	case positiveZ:
		*output = components[blockIndex]->position + glm::vec3(0, 0, -1);
		break;
	case negativeZ:
		*output = components[blockIndex]->position + glm::vec3(0, 0, 1);
		break;
	}
}

//get inputs for gates with 2 inputs
void DigitalLogic::getInputs(int blockIndex, glm::vec3* input1, glm::vec3* input2)
{
	switch (components[blockIndex]->direction) {
	case positiveX:
		*input1 = components[blockIndex]->position + glm::vec3(0, 0, 1);
		*input2 = components[blockIndex]->position + glm::vec3(0, 0, -1);
		break;
	case negativeX:
		*input1 = components[blockIndex]->position + glm::vec3(0, 0, 1);
		*input2 = components[blockIndex]->position + glm::vec3(0, 0, -1);
		break;
	case positiveY:
		*input1 = components[blockIndex]->position + glm::vec3(0, 0, 1);
		*input2 = components[blockIndex]->position + glm::vec3(0, 0, -1);
		break;
	case negativeY:
		*input1 = components[blockIndex]->position + glm::vec3(0, 0, 1);
		*input2 = components[blockIndex]->position + glm::vec3(0, 0, -1);
		break;
	case positiveZ:
		*input1 = components[blockIndex]->position + glm::vec3(1, 0, 0);
		*input2 = components[blockIndex]->position + glm::vec3(-1, 0, 0);
		break;
	case negativeZ:
		*input1 = components[blockIndex]->position + glm::vec3(1, 0, 0);
		*input2 = components[blockIndex]->position + glm::vec3(-1, 0, 0);
		break;
	}
}

//getting the index of the model for each type of component, + state as the on variant will be the next index after the off index
int DigitalLogic::getModelIndex(componentType type, bool state)
{
	switch (type) {
	case inverter:
		return 8 + state;
	case button:
		return 6 + state;
	case andGate:
		return 10 + state;
	case orGate:
		return 12 + state;
	case xorGate:
		return 18 + state;
	case wire:
		return 14 + state;
	}
}

//running the digital logic simulation for every block
void DigitalLogic::runLogic()
{
	glm::vec3 input;
	glm::vec3 input2;
	glm::vec3 output;

	//STEP 1: setting all wires to the off state
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->type == wire) {
			components[i]->state = false;
		}
	}
	//STEP 2: propogating signal from the outputs of all gates that are already in the on state
	for (int i = 0; i < components.size(); i++) {
		//getting the output block of this block

		if (//make sure this block is on and either a wire, gate or button
			components[i]->state && components[i]->type != LED && components[i]->type != wire
			)
		{
			getOutput(i, &output);
			if (//checking if the output of this block exists
				doesComponentExist(output.x, output.y, output.z) &&
				//checking if the output of this block is a wire
				components[getComponent(output.x, output.y, output.z)]->type == wire
				)
			{
				//propogates the signal from the output block through all connected wire components
				components[getComponent(output.x, output.y, output.z)]->state = true;
				checkSurroundingComponents(output);
			}
		}

	}

	//STEP 3: checking the inputs of all components and setting the state of the component accordingly
	for (int i = 0; i < components.size(); i++) {
		//setting the state for all inverters
		if (components[i]->type == inverter) {
			//getting the input for an inverter
			getInput(i, &input);
			//checking if the input exixts, is a wire, and is on
			if (doesComponentExist(input.x, input.y, input.z))
			{
				int tempIndex = getComponent(input.x, input.y, input.z);
				if (components[tempIndex]->type == wire && components[tempIndex]->state) {
					components[i]->state = false;
				}
				else {
					components[i]->state = true;
				}
			}
		}
		//setting the state for all LED's
		else if (components[i]->type == LED) {
			//checking if all components surrounding the LED, exist, are a wire, and are on
			if (doesComponentExist(components[i]->position.x + 1, components[i]->position.y, components[i]->position.z) && components[getComponent(components[i]->position.x + 1, components[i]->position.y, components[i]->position.z)]->type == wire && components[getComponent(components[i]->position.x + 1, components[i]->position.y, components[i]->position.z)]->state) {
				components[i]->state = true;
			}
			else if (doesComponentExist(components[i]->position.x - 1, components[i]->position.y, components[i]->position.z) && components[getComponent(components[i]->position.x - 1, components[i]->position.y, components[i]->position.z)]->type == wire && components[getComponent(components[i]->position.x - 1, components[i]->position.y, components[i]->position.z)]->state) {
				components[i]->state = true;
			}
			else if (doesComponentExist(components[i]->position.x, components[i]->position.y + 1, components[i]->position.z) && components[getComponent(components[i]->position.x, components[i]->position.y + 1, components[i]->position.z)]->type == wire && components[getComponent(components[i]->position.x, components[i]->position.y + 1, components[i]->position.z)]->state) {
				components[i]->state = true;
			}
			else if (doesComponentExist(components[i]->position.x, components[i]->position.y - 1, components[i]->position.z) && components[getComponent(components[i]->position.x, components[i]->position.y - 1, components[i]->position.z)]->type == wire && components[getComponent(components[i]->position.x, components[i]->position.y - 1, components[i]->position.z)]->state) {
				components[i]->state = true;
			}
			else if (doesComponentExist(components[i]->position.x, components[i]->position.y, components[i]->position.z - 1) && components[getComponent(components[i]->position.x, components[i]->position.y, components[i]->position.z - 1)]->type == wire && components[getComponent(components[i]->position.x, components[i]->position.y, components[i]->position.z - 1)]->state) {
				components[i]->state = true;
			}
			else if (doesComponentExist(components[i]->position.x, components[i]->position.y, components[i]->position.z + 1) && components[getComponent(components[i]->position.x, components[i]->position.y, components[i]->position.z + 1)]->type == wire && components[getComponent(components[i]->position.x, components[i]->position.y, components[i]->position.z + 1)]->state) {
				components[i]->state = true;
			}
			else {
				components[i]->state = false;
			}
		}
		//setting the state for all gates depending on inputs
		else if (components[i]->type != wire) {
			//getting the locations of the input components
			getInputs(i, &input, &input2);
			int value = 0;
			//check if first input exists, is a wire, and is on
			if (doesComponentExist(input.x, input.y, input.z) && components[getComponent(input.x, input.y, input.z)]->type == wire && components[getComponent(input.x, input.y, input.z)]->state) {
				value++;
			}
			//check if second input exists, is a wire, and is on
			if (doesComponentExist(input2.x, input2.y, input2.z) && components[getComponent(input2.x, input2.y, input2.z)]->type == wire && components[getComponent(input2.x, input2.y, input2.z)]->state) {
				value++;
			}
			//behavior of the gates
			switch (components[i]->type) {
			case andGate:
				if (value == 2) {
					components[i]->state = true;
				}
				else {
					components[i]->state = false;
				}
				break;
			case orGate:
				if (value > 0) {
					components[i]->state = true;
				}
				else {
					components[i]->state = false;
				}
				break;
			case xorGate:
				if (value == 1) {
					components[i]->state = true;
				}
				else {
					components[i]->state = false;
				}
				break;
			}
		}
	}
}

void DigitalLogic::clearComponents(){
	for (int i = 0; i < components.size(); i++) {
		removeComponent(i);
	}
}

std::vector<Component*>* DigitalLogic::getComponentsPointer() {
	return &components;
}
