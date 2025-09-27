/* Name: Emma Coleman
*  Purpose: This is the cpp for the wire class */
#include "Wire.h"

Wire::Wire(string& wireName, value& wireVal, int& wireIndex, type& wireType, string& wireHistory, Gate* nextGate) {
	setWireName(wireName);
	setWireVal(wireVal);
	setWireDrives(nextGate);
	index = wireIndex;
	t = wireType;
}
// Setters
void Wire::setWireName(const string& wireName) {
	name = wireName;
}
void Wire::setWireVal(const value& wireVal) {
	v = wireVal;
}
// Adds to wire history the value of the wire
void Wire::setWireHistory(const value& wireVal) {
	switch (wireVal) {
	case LO:
		history += "_";
		break;
	case HI:
		history += "-";
		break;
	case UNKNOWN:
		history += "X";
		break;
	}
}
// Connects input wire to next gate
void Wire::setWireDrives(Gate* nextGate) {
	drive = nextGate;
}

// Getters
string Wire::getWireName() const {
	return name;
}
value Wire::getWireVal() const {
	return v;
}
int Wire::getWireIndex() const {
	return index;
}
type Wire::getWireType() const {
	return t;
}
string Wire::getWireHistory() const {
	return history;
}
Gate* Wire::getWireGate() const {
	return drive;
}
// Print
void Wire::printHistory() const {
	cout << history << endl;
}