/* Name: Alana Durham
*  Purpose: This is the cpp for the gate class */
#include <iostream>
#include <sstream>
#include "Gate.h"
#include "Wire.h"


Gate::Gate(gateType g, string d, Wire* iW1, Wire* iW2, Wire* oW) {
	int intDelay;
	stringstream(d) >> intDelay;
	delay = intDelay;

	gate = g;
	input1 = iW1;
	input2 = iW2;
	output = oW;
}

int Gate::getDelay() const {
	return delay;
}

Wire* Gate::getInput(int i) const {
	if (i == 1) {
		return input1;
	}
	else if (i == 2) {
		return input2;
	}
}

Wire* Gate::getOutput() const {
	return output;
}

value Gate::returnVal() const {
	//exercise Gate logic
	//implement AND
	if (gate == AND) {
		if (input1->getWireVal() == LO || input2->getWireVal() == LO) {
			return LO;
		}
		else if ((input1->getWireVal() == HI) && (input2->getWireVal() == HI)) {
			return HI;
		}
	}

	//implement OR
	else if (gate == OR) {
		if (input1->getWireVal() == HI || input2->getWireVal() == HI) {
			return HI;
		}
		else if ((input1->getWireVal() == LO) && (input2->getWireVal() == LO)){
			return LO;
		}
	}

	//implement NOT
	else if (gate == NOT) {
		if (input1->getWireVal() == LO) {
			return HI;
		}
		else {
			return LO;
		}
	}

	//implement NAND
	else if (gate == NAND) {
		if (input1->getWireVal() == LO || input2->getWireVal() == LO) {
			return HI;
		}
		else if ((input1->getWireVal() == HI) && (input2->getWireVal() == HI)) {
			return LO;
		}
	}

	//implement NOR
	else if (gate == NOR) {
		if (input1->getWireVal() == HI || input2->getWireVal() == HI) {
			return LO;
		}
		else if ((input1->getWireVal() == LO) && (input2->getWireVal() == LO)) {
			return HI;
		}
	}

	//implement XOR
	else if (gate == XOR) {
		if (input1->getWireVal() == HI && input2->getWireVal() == LO) {
			return HI;
		}
		else if (input1->getWireVal() == LO && input2->getWireVal() == HI) {
			return HI;
		}
		else if ((input1->getWireVal() == input2->getWireVal()) && (input1->getWireVal() != UNKNOWN)) {
			return LO;
		}
	}

	//implement XNOR
	else if (gate == XNOR) {
		if (input1->getWireVal() == HI && input2->getWireVal() == LO) {
			return LO;
		}
		else if (input1->getWireVal() == LO && input2->getWireVal() == HI) {
			return LO;
		}
		else if ((input1->getWireVal() == input2->getWireVal()) && (input1->getWireVal() != UNKNOWN)) {
			return HI;
		}
	}

	//implement UNKNOWN
	return UNKNOWN;
}