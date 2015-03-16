#pragma once

#ifndef LOGIC_H
#define LOGIC_H


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
	static const int INVALID_NUMBER;



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
	vector<string> getErrorString();

	//executors
	bool executeUserInput(string input);
	void executeCommand(Parser::commandType command, Event userEvent);
	void deleteParserPtr();


	//others
	bool isNumber(string s);
	int convertNameToID(string name);
	void setDisplay(bool isFloat, vector<Event> eventsToSet);
};

#endif