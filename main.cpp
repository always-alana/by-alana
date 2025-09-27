/*Header
* Authors: Alana Durham && Emma Coleman
* Date: 4/25
* 
* File: main.cpp
*/
#include "Wire.h"
#include "Gate.h"
#include "Event.h"
#include <queue>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct EventCompare {
	bool operator()(Event* e1, Event* e2) {
		if (e1->getTime() == e2->getTime()) {
			return e1->getCount() > e2->getCount();
		}
		return e1->getTime() > e2->getTime();
	}
};

int main() {

    cout << "What is the name of the circuit test file (base name only):";
    string fileName;
    cin >> fileName;
    cout << endl;

    //Read in circuit file
    ifstream inCirc;

    //Open file
    inCirc.open(fileName + ".txt");

    //Check if file is open
    if (!inCirc.is_open()) {
        cerr << "Error: could not open circuit file." << endl;
        return 1;
    }

    //Wire variable declarations
    vector<Wire*> wires;
    string circInput;
    string wireName;
    int wireIndex;
    type wireType;
    value wireVal = UNKNOWN;
    string wireHistory = "";
    Gate* nextGate = nullptr;
    Wire* w = nullptr;

    //Gate variable declarations
    vector<Gate*> gates;
    string gateTypeStr;
    gateType t;
    string gateDelay;
    int gateInput1, gateInput2, gateOutput;
    Gate* g = nullptr;

    int ibIncrement = 1;

    //Skip over file name
    inCirc >> circInput;
    //Skip over circuit name
    inCirc >> circInput;

    while (!inCirc.eof()) {
        //Read in Wire type
        inCirc >> circInput;
        if (circInput == "INPUT") {
            wireType = INPUT;
        }
        else if (circInput == "OUTPUT") {
            wireType = OUTPUT;
        }
        else {
            wireType = NONE;    //Write code for gates

            for (int i = 0; i < wires.size(); i++) {
                // Check if the wireIndex is not sequential
                while (wires.at(i)->getWireIndex() != i + 1) {
                    // Create a placeholder Wire* object
                    string placeholderName = "PLACEHOLDER";
                    value placeholderVal = UNKNOWN;
                    int placeholderIndex = i + 1;
                    type placeholderType = NONE;
                    string placeholderHistory = "";
                    Gate* placeholderNextGate = nullptr;

                    Wire* placeholder = new Wire(placeholderName, placeholderVal, placeholderIndex, placeholderType, placeholderHistory, placeholderNextGate);

                    // Insert the placeholder into the correct position
                    wires.insert(wires.begin() + i, placeholder);
                }
            }

            //Read in gate type
            gateTypeStr = circInput;
            if (gateTypeStr == "AND") {
                t = AND;
            }
            else if (gateTypeStr == "OR") {
                t = OR;
            }
            else if (gateTypeStr == "NOT") {
                t = NOT;
            }
            else if (gateTypeStr == "NAND") {
                t = NAND;
            }
            else if (gateTypeStr == "NOR") {
                t = NOR;
            }
            else if (gateTypeStr == "XOR") {
                t = XOR;
            }
            else if (gateTypeStr == "XNOR") {
                t = XNOR;
            }

            //Read in gate delay
            inCirc >> gateDelay;

            //Read in input wire index
            inCirc >> gateInput1;
            if (t != NOT) {
                inCirc >> gateInput2;
            }
            inCirc >> gateOutput;

            int maxIndex;
            if (t != NOT) {
                maxIndex = max({ gateInput1, gateInput2, gateOutput });
            }
            else {
                if (gateInput1 > gateOutput) {
                    maxIndex = gateInput1;
                }
                else {
                    maxIndex = gateOutput;
                }
            }

            //Check for "in-between/NONE-type" wires
            if (wires.at(gateInput1 - 1)->getWireName() == "PLACEHOLDER") {
                wires.at(gateInput1 - 1)->setWireName(to_string(gateInput1));
                ibIncrement++;
            }
            if ((t != NOT) && (wires.at(gateInput2 - 1)->getWireName() == "PLACEHOLDER")) {
                wires.at(gateInput2 - 1)->setWireName(to_string(gateInput2));
                ibIncrement++;
            }
			if (wires.at(gateOutput - 1)->getWireName() == "PLACEHOLDER") {
				wires.at(gateOutput - 1)->setWireName(to_string(gateOutput));
				ibIncrement++;
			}

            //Construct gate object
            if (t != NOT) {
                g = new Gate(t, gateDelay, wires.at(gateInput1 - 1), wires.at(gateInput2 - 1), wires.at(gateOutput - 1));
            }
            else {
                g = new Gate(t, gateDelay, wires.at(gateInput1 - 1), nullptr, wires.at(gateOutput - 1));
            }

            //Initialize next gate for in-between wires
			if (wires.at(gateInput1 - 1)->getWireType() == NONE) {
				wires.at(gateInput1 - 1)->setWireDrives(g);
			}
            if ((t != NOT) && (wires.at(gateInput2 - 1)->getWireType() == NONE)) {
                wires.at(gateInput2 - 1)->setWireDrives(g);
            }
            if (wires.at(gateOutput - 1)->getWireType() == NONE) {
                wires.at(gateOutput - 1)->setWireDrives(g);
            }

            //Set input wires
            wires.at(gateInput1 - 1)->setWireDrives(g);
            if (t != NOT) {
                wires.at(gateInput2 - 1)->setWireDrives(g);
            }
            //Set output wire
            wires.at(gateOutput - 1)->setWireDrives(g);

            //Add gate to vector
            gates.push_back(g);
        }

        if (wireType != NONE) {
            //Read in wire name
            inCirc >> wireName;

            //Read in wire index
            inCirc >> wireIndex;

            //Construct wire object
            w = new Wire(wireName, wireVal, wireIndex, wireType, wireHistory, nextGate);

            //Add wire to vector
            wires.push_back(w);
        }
    }
    
    //Close file
    inCirc.close();

    //****************************************************

    //TODO: Parse vector file
      //Read in vector file
    ifstream inVec;

    //Open file
    inVec.open(fileName + "_v.txt");
    if (!inVec.is_open()) {
        cerr << "Error: could not open vector file." << endl;
        return 1;
    }

    //skips over initial VECTOR and vector name
    string vecInput;
    inVec >> vecInput;
    inVec >> vecInput;

    //TODO: Initialize Queue
    priority_queue<Event*, vector<Event*>, EventCompare> eventQueue;

    //Initialize variables
    string eventName;
    int eventTime;
    value eventVal;
    Event* e = nullptr;
    int count = 0;

    while (!inVec.eof()) {
        //Skip reading INPUT
        inVec >> vecInput;

        //Read in input name
        inVec >> eventName;

        //Read in input time
        inVec >> eventTime;

        //Read in input value
        inVec >> vecInput;
        if (vecInput == "0") {
            eventVal = LO;
        }
        else if (vecInput == "1") {
            eventVal = HI;
        }
        else {
            eventVal = UNKNOWN;
        }

        //Construct event object
        e = new Event(eventName, eventTime, eventVal, count);

        //Add event to queue
        eventQueue.push(e);
        count++;
    }

    //Close file
    inVec.close();

    int loopTracker = 0;
	int time = 0;
    while ((!eventQueue.empty()) && !(loopTracker >= 15)) {
        Event* e = nullptr;

        //Set name, time, and value
        wireName = eventQueue.top()->getName();
        eventTime = eventQueue.top()->getTime();
        value newVal = eventQueue.top()->getVal();

		//Check if event time is greater than current time
        if (eventTime > time) {
            time = eventTime;

            //Check wire histories
            int size;
            for (int i = 0; i < wires.size(); i++) {
                    if (wires.at(i)->getWireHistory().size() < time) {
                        size = wires.at(i)->getWireHistory().size();
                        for (int j = 0; j < time - size; j++) {
                            if (wires.at(i)->getWireName() != "PLACEHOLDER") {
                                wires.at(i)->setWireHistory(wires.at(i)->getWireVal());
                            }
                            else {
                                break;
                            }
                        }
                    }
            }
        }

        //Remove front
        eventQueue.pop();

        //Find wire
        Wire* currWire = wires.at(0);

        for (int i = 0; i < wires.size(); i++) {
            currWire = wires.at(i);
            if ((wireName == currWire->getWireName()) && (wireName != "PLACEHOLDER")) {
                break;
            }
        }

        //Set wire to new val only if value changes
        if (currWire->getWireVal() != newVal) {
            currWire->setWireVal(newVal);

            //Set wire history
            currWire->setWireHistory(newVal);
        }
        else {
            currWire->setWireHistory(currWire->getWireVal());
        }

        if (currWire->getWireGate()->returnVal() != currWire->getWireGate()->getOutput()->getWireVal()) {
            //Evaluate gates
            e = new Event(currWire->getWireGate()->getOutput()->getWireName(), eventTime + currWire->getWireGate()->getDelay(), currWire->getWireGate()->returnVal(), count);
            eventQueue.push(e);
            count++;
        }
        loopTracker++;
    }

    //Print out wire history
    for (int i = 0; i < wires.size(); i++) {
        if (wires.at(i)->getWireName() != "PLACEHOLDER") {
            cout << wires.at(i)->getWireName() << ": ";
            wires.at(i)->printHistory();
        }
    }

	//Delete all dynamically allocated memory
    for (int i = 0; i < wires.size(); i++) {
        delete wires.at(i);
    }
	for (int i = 0; i < gates.size(); i++) {
		delete gates.at(i);
	}
	for (int i = 0; i < eventQueue.size(); i++) {
		delete eventQueue.top();
		eventQueue.pop();
	}

    return 0;
}