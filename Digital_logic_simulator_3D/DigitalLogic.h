#pragma once
#include <vector>
struct WireNode {
	//size
	int size;
	//array of wire components
	void** components;
	//state
	bool state;
	//last state, used for checking if something changed (needs to be drawn differently now)
	bool lastState;
};

enum gateType { _not, _or , _and, _xor };

struct Gate {
	//mode 0 = 2 inputs, 1 = 3 inputs
	int mode3;
	//inputs
	WireNode** inputs;
	//output
	WireNode* output;
	//state
	bool state;
	//type
	gateType type;
	//fully connected ie are all the inputs present as well as the output
	bool fullyConnected;
};

class DigitalLogic {
public:
	DigitalLogic();
	void run();
	std::vector<Gate*> gates;
	std::vector<WireNode*> wires;
private:

};