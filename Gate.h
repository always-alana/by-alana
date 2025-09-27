/* Name: Alana Durham
*  Purpose: This is the header for the gate class */
#pragma once
#include <string>
#include "enum.h"

using namespace std;

// Forward declare wire class
class Wire;


class Gate {
public:
	Gate(gateType g, string d, Wire* iW1, Wire* iW2, Wire* oW);
	int getDelay() const;
	Wire* getInput(int i) const;//value for i refers to value of wire1 or wire2
	Wire* getOutput() const;
	value returnVal(/*add parms*/) const; //exercise Gate logic
private:
	Wire* input1, * input2;
	Wire* output;
	gateType gate;
	int delay;
};