#pragma once
#include "DigitalLogic.h"

// returned by functions like setSelectedComponent that may need to return nothing, but 0,0,0 is still a valid component. the float values make this work at components can only have whole number coordinates


class ComponentManipulation {
public:
	ComponentManipulation();
	void init(DigitalLogic* _digitalLogicPointer);
	void placeComponent(glm::vec3 _cameraPosition, glm::vec3 _cameraDirection, componentType _componentTypeSelected);
	void deleteComponent(glm::vec3 _cameraPosition, glm::vec3 _cameraDirection);
	glm::vec3 getSelectedComponent(glm::vec3 _cameraPosition, glm::vec3 _cameraDirection);
	int getSide(glm::vec3 _component, glm::vec3 _cameraPosition, glm::vec3 _cameraDirection);

private:
	glm::vec3 getLineFaceIntersect(glm::vec3 _min, glm::vec3 _max, glm::vec3 _origin, glm::vec3 _direction, int _orientation);
	float get3DDistance(glm::vec3 _p1, glm::vec3 _p2);
	glm::vec3 nullComponent = glm::vec3(-0.1, -0.1, -0.1);

	DigitalLogic* digitalLogicPointer;

};