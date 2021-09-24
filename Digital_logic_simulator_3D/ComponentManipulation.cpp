#include "ComponentManipulation.h"

ComponentManipulation::ComponentManipulation() {}

void ComponentManipulation::init(CircuitManager * _circuitManagerPointer){
	circuitManagerPointer = _circuitManagerPointer;
}

void ComponentManipulation::placeComponent(glm::vec3 _cameraPosition, glm::vec3 _cameraDirection, componentType _componentTypeSelected){
	glm::vec3 component = getSelectedComponent(_cameraPosition, _cameraDirection);
	int face = getSide(component, _cameraPosition, _cameraDirection);
	//FACES:
	//top XZ: 0
	//bottom XZ: 1
	//back ZY: 2
	//front ZY: 3
	//back XY: 4
	//front XY: 5
	if (component == nullComponent) {
		return;
	}
	switch (face) {
	case 0:
		circuitManagerPointer->addComponent(component.x, component.y + 1, component.z, _componentTypeSelected, positiveY);
		break;
	case 1:
		circuitManagerPointer->addComponent(component.x, component.y - 1, component.z, _componentTypeSelected, negativeY);
		break;
	case 2:
		circuitManagerPointer->addComponent(component.x + 1, component.y, component.z, _componentTypeSelected, positiveX);
		break;
	case 3:
		circuitManagerPointer->addComponent(component.x - 1, component.y, component.z, _componentTypeSelected, negativeX);
		break;
	case 4:
		circuitManagerPointer->addComponent(component.x, component.y, component.z + 1, _componentTypeSelected, positiveZ);
		break;
	case 5:
		circuitManagerPointer->addComponent(component.x, component.y, component.z - 1, _componentTypeSelected, negativeZ);
		break;
	}
}

void ComponentManipulation::deleteComponent(glm::vec3 _cameraPosition, glm::vec3 _cameraDirection){
	glm::vec3 component = getSelectedComponent(_cameraPosition, _cameraDirection);
	if (component != nullComponent) {
		circuitManagerPointer->removeComponent(component.x, component.y, component.z);
	}
}

glm::vec3 ComponentManipulation::getSelectedComponent(glm::vec3 _cameraPosition, glm::vec3 _cameraDirection){
	glm::vec3 temp = _cameraPosition;
	float radius = 150;
	for (int i = 0; i < radius; i++) {
		temp += glm::vec3(_cameraDirection.x / 25, _cameraDirection.y / 25, _cameraDirection.z / 25);
		if (circuitManagerPointer->getComponent(floor(temp.x), floor(temp.y), floor(temp.z)) != -1) {
			return glm::vec3(floor(temp.x), floor(temp.y), floor(temp.z));
		}
	}
	return nullComponent;
}

glm::vec3 ComponentManipulation::getLineFaceIntersect(glm::vec3 min, glm::vec3 max, glm::vec3 origin, glm::vec3 direction, int orientation) {
	//orientation 1: XZ, 2: ZY, 3: XY
	direction *= 100;
	direction += origin;
	glm::vec3 intersection = glm::vec3(1000000000, 1000000000, 1000000000);
	switch (orientation) {
	case 1:
		intersection.y = min.y;
		intersection.x = (min.y - origin.y) / (direction.y - origin.y)*(direction.x - origin.x) + origin.x;
		intersection.z = (min.y - origin.y) / (direction.y - origin.y)*(direction.z - origin.z) + origin.z;
		if (intersection.x <= max.x && intersection.x >= min.x && intersection.z <= max.z && intersection.z >= min.z) {
			return intersection;
		}
		break;
	case 2:
		intersection.x = min.x;
		intersection.y = (min.x - origin.x) / (direction.x - origin.x)*(direction.y - origin.y) + origin.y;
		intersection.z = (min.x - origin.x) / (direction.x - origin.x)*(direction.z - origin.z) + origin.z;

		if (intersection.y <= max.y && intersection.y >= min.y && intersection.z <= max.z && intersection.z >= min.z) {
			return intersection;
		}
		break;
	case 3:
		intersection.z = min.z;
		intersection.x = (min.z - origin.z) / (direction.z - origin.z)*(direction.x - origin.x) + origin.x;
		intersection.y = (min.z - origin.z) / (direction.z - origin.z)*(direction.y - origin.y) + origin.y;
		if (intersection.x <= max.x && intersection.x >= min.x && intersection.y <= max.y && intersection.y >= min.y) {
			return intersection;
		}
		break;
	default:
		std::cout << "No valid orientation passed in" << std::endl;
		return nullIntersection;
		break;
	}
	return nullIntersection;
}

int ComponentManipulation::getSide(glm::vec3 _component, glm::vec3 _cameraPosition, glm::vec3 _cameraDirection){
	std::vector<glm::vec3> intersections;
	//top XZ
	glm::vec3 min = glm::vec3(_component.x, _component.y + 1, _component.z);
	glm::vec3 max = glm::vec3(_component.x + 1, _component.y + 1, _component.z + 1);
	intersections.push_back(getLineFaceIntersect(min, max, _cameraPosition, _cameraDirection, 1));
	//bottom XZ
	min = glm::vec3(_component.x, _component.y, _component.z);
	max = glm::vec3(_component.x + 1, _component.y, _component.z + 1);
	intersections.push_back(getLineFaceIntersect(min, max, _cameraPosition, _cameraDirection, 1));
	//back ZY
	min = glm::vec3(_component.x + 1, _component.y, _component.z);
	max = glm::vec3(_component.x + 1, _component.y + 1, _component.z + 1);
	intersections.push_back(getLineFaceIntersect(min, max, _cameraPosition, _cameraDirection, 2));
	//front ZY
	min = glm::vec3(_component.x, _component.y, _component.z);
	max = glm::vec3(_component.x, _component.y + 1, _component.z + 1);
	intersections.push_back(getLineFaceIntersect(min, max, _cameraPosition, _cameraDirection, 2));
	//back XY
	min = glm::vec3(_component.x, _component.y, _component.z + 1);
	max = glm::vec3(_component.x + 1, _component.y + 1, _component.z + 1);
	intersections.push_back(getLineFaceIntersect(min, max, _cameraPosition, _cameraDirection, 3));
	//front XY
	min = glm::vec3(_component.x, _component.y, _component.z);
	max = glm::vec3(_component.x + 1, _component.y + 1, _component.z);
	intersections.push_back(getLineFaceIntersect(min, max, _cameraPosition, _cameraDirection, 3));

	int smallestDistanceIndex = 0;
	float smallestDistance = 1000000000;
	for (int i = 0; i < intersections.size(); i++) {
		if (intersections[i] != nullIntersection) {
			float temp = get3DDistance(_cameraPosition, intersections[i]);
			if (temp < smallestDistance && temp != NULL) {
				smallestDistance = temp;
				smallestDistanceIndex = i;
			}
		}
	}
	if (smallestDistance == 1000000000) {
		return NULL;
		std::cout << "No side intersection found" << std::endl;
	}
	return smallestDistanceIndex;
	//top XZ: 0
	//bottom XZ: 1
	//back ZY: 2
	//front ZY: 3
	//back XY: 4
	//front XY: 5
}

float ComponentManipulation::get3DDistance(glm::vec3 _p1, glm::vec3 _p2) {
	if (_p1 == nullIntersection || _p2 == nullIntersection) {
		return NULL;
	}
	return sqrt(pow((_p1.x - _p2.x), 2) + pow((_p1.y - _p2.y), 2) + pow((_p1.z - _p2.z), 2));
}

void ComponentManipulation::switchButton(glm::vec3 _cameraPosition, glm::vec3 _cameraDirection) {
	glm::vec3 component = getSelectedComponent(_cameraPosition, _cameraDirection);
	if (circuitManagerPointer->getComponentType(component.x, component.y, component.z) == button) {
		if (circuitManagerPointer->getComponentState(component.x, component.y, component.z) == true) {
			circuitManagerPointer->setComponentState(component.x, component.y, component.z, false);
		}
		else {
			circuitManagerPointer->setComponentState(component.x, component.y, component.z, true);
		}
	}
}

glm::vec3 ComponentManipulation::getNewComponentLocation(glm::vec3 _cameraPosition, glm::vec3 _cameraDirection){
	glm::vec3 component = getSelectedComponent(_cameraPosition, _cameraDirection);
	int face = getSide(component, _cameraPosition, _cameraDirection);
	//FACES:
	//top XZ: 0
	//bottom XZ: 1
	//back ZY: 2
	//front ZY: 3
	//back XY: 4
	//front XY: 5
	if (component == nullComponent) {
		return glm::vec3(-1000000, -1000000, -1000000);
	}
	switch (face) {
	case 0:
		return component + glm::vec3(0, 1, 0);
		break;
	case 1:
		return component + glm::vec3(0, -1, 0);
		break;
	case 2:
		return component + glm::vec3(1, 0, 0);
		break;
	case 3:
		return component + glm::vec3(-1, 0, 0);
		break;
	case 4:
		return component + glm::vec3(0, 0, 1);
		break;
	case 5:
		return component + glm::vec3(0, 0, -1);
		break;
	}
}
