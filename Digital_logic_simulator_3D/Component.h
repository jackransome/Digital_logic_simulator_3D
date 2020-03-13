#pragma once
#include <glm/glm.hpp>
enum componentType { wire, inverter, andGate, orGate, xorGate, LED, button };
enum componentDirection { positiveX, negativeX, positiveY, negativeY, positiveZ, negativeZ };
class Component {
public:
	Component(int x, int y, int z, componentType _type, componentDirection _direction) { position = glm::vec3(x, y, z); type = _type; direction = _direction; };
	~Component() {};
	glm::vec3 position;
	componentType type;
	componentDirection direction;
	glm::vec3 colour;
	int onGraphicsObjectIndex;
	int offGraphicsObjectIndex;
	bool state = false;
};