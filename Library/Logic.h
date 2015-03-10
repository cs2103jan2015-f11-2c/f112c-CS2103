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

	vector<string> getFloatingStrings();
	vector<Display::MAIN_EVENT> getMainStrings();
	vector<string> getFeedbackStrings();


	//executors
	bool executeUserInput(string input);
	void executeCommand(Parser::commandType command, Event userEvent);
	void deleteParserPtr();


	//others
	bool isNumber(string s);
};

#endif