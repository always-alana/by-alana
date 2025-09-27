#pragma once
#include <iostream>
#include <string>
#include "enum.h"

using namespace std;

//Initialize Event class and member functions
class Event {
public:
    //Constructors
    Event() : inName(""), inTime(-1), inVal(UNKNOWN), count(0) {};
    Event(string n, int t, value v, int c = 0) : inName(n), inTime(t), inVal(v), count(c) {};

    //Getters
    string getName() { return inName; };
    int    getTime() { return inTime; };
    value  getVal() {  return  inVal; };
	int    getCount() { return count; };

    //Setters
    void setName(string n) { inName = n; };
    void setTime(int t) { inTime = t; };
    void setVal(value v) { inVal = v; };
	void setCount(int c) { count = c; };

private:
    string inName;
    int    inTime;
    value   inVal;
    int count;
};