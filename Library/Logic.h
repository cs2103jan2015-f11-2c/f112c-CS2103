#pragma once

#ifndef LOGIC_H
#define LOGIC_H


#include <iostream>
#include <string>
#include <vector>
#include "Parser.h"
#include "EventStorage.h"
#include "Event.h"
#include "Display.h"


class Logic {
private:
	Parser* parserPtr;
	EventStorage eventStore;
	Display display;

public:
	//constructor, destructor
	Logic(void);
	~Logic();


	//getters
	Parser::commandType getCommand();
	Event getEvent();
	EventStorage getEventStorage();


	//executors
	vector<Event> executeUserInput(string input);
	vector<Event> executeCommand(Parser::commandType command, Event userEvent);
	void deleteParserPtr();

};

#endif