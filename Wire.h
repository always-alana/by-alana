/* Name: Emma Coleman
*  Purpose: This is the header for the wire class */
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "enum.h"

using namespace std;

// Forward declare Gate class
class Gate;
// Declare Wire class
class Wire {
	// Getters and setters
public:

	// Constructors
	Wire(string& wireName, value& wireVal, int& wireIndex, type& wireType, string& wireHistory, Gate* nextGate);
	// Setters
	void setWireName(const string& wireName);
	void setWireVal(const value& wireVal);
	// Takes in a value and starts or adds to existing string of history
	void setWireHistory(const value& wireVal);
	// Connects an input wire to the next gate
	void setWireDrives(Gate* nextGate);
	// Getters
	string getWireName() const;
	value getWireVal() const;
	int getWireIndex() const;
	type getWireType() const;
	string getWireHistory() const;
	Gate* getWireGate() const;
	// Print
	void printHistory() const;

	// Data members
private:
	string name;
	value v;
	int index;
	type t;
	string history;
	Gate* drive;
};