#include "DigitalLogic.h"

DigitalLogic::DigitalLogic(){}

void DigitalLogic::run(){
	//reset all wires while setting their lastState
	for (int i = 0; i < wires.size(); i++) {
		wires[i]->lastState = wires[i]->state;
		wires[i]->state = false;
	}
	//propogate output of gates
	for (int i = 0; i < gates.size(); i++) {
		if (gates[i]->fullyConnected) {
			if (gates[i]->state) {
				gates[i]->output->state = true;
			}
		}
	}
	//evaluate value of gates
	for (int i = 0; i < gates.size(); i++) {
		if (gates[i]->fullyConnected) {
			if (gates[i]->type == _not) {
				gates[i]->state = !gates[i]->inputs[0]->state;
			}
			else {
				//generating sum of all inputs
				int sum = 0;
				sum += gates[i]->inputs[0]->state;
				sum += gates[i]->inputs[1]->state;
				if (gates[i]->mode3) {
					sum += gates[i]->inputs[2]->state;
				}
				//or gate
				if (gates[i]->type == _or) {
					if (sum > 0) {
						gates[i]->state = 1;
					}
					else {
						gates[i]->state = 0;
					}
				}
				//and gate
				else if (gates[i]->type == _and) {
					if (!gates[i]->mode3 && sum == 2) {
						gates[i]->state = 1;
					}
					else if (gates[i]->mode3 && sum == 3) {
						gates[i]->state = 1;
					}
					else {
						gates[i]->state = 0;
					}
				}
				//xor gate
				else if (gates[i]->type == _xor) {
					if (!gates[i]->mode3 && sum == 1) {
						gates[i]->state = 1;
					}
					else if (gates[i]->mode3 && (sum == 3 || sum == 1)) {
						gates[i]->state = 1;
					}
					else {
						gates[i]->state = 0;
					}
				}
			}
		}
	}
}
