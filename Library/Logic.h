#pragma once

#ifndef LOGIC_H
#define LOGIC_H


#include <iostream>
#include <string>
#include <vector>
//#include "Parser.h"
#include "EventStorage.h"
#include "Event.h"

using std::string;
using std::vector;


class Logic {
private:
	//Parser* parserPtr;
	EventStorage eventStore;


public:
	//constructor
	Logic();
	

	//getters
	//Parser::commandType getCommand();
	//Event getEvent();


	//executors
	vector<Event> executeUserInput(string input);
	//vector<Event> executeCommand(Parser::commandType command, Event userEvent);
	//void deleteParserPtr();

};

#endif