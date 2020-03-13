#pragma once
#include "DigitalLogic.h"

class ComponentManipulation {
public:
	ComponentManipulation();
	void init(DigitalLogic* _digitalLogicPointer);
	void placeComponent(glm::vec3 cameraPosition, glm::vec3 cameraDirection, componentType _componentTypeSelected);
	glm::vec3 getSelectedComponent(glm::vec3 cameraPosition, glm::vec3 cameraDirection);
	int getSide(glm::vec3 _component, glm::vec3 cameraPosition, glm::vec3 cameraDirection);

private:
	glm::vec3 getLineFaceIntersect(glm::vec3 min, glm::vec3 max, glm::vec3 origin, glm::vec3 direction, int orientation);
	float get3DDistance(glm::vec3 p1, glm::vec3 p2);

	DigitalLogic* digitalLogicPointer;

};