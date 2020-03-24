#include "Component.h"

Component::Component(int x, int y, int z, componentType _type, componentDirection _direction){
	position = glm::vec3(x, y, z);
	type = _type;
	direction = _direction;
}

Component::~Component(){}
