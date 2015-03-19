#pragma once

#ifndef LOGIC_H
#define LOGIC_H


#include <fstream>
#include "Parser.h"
#include "EventStorage.h"
#include "Event.h"
#include "Display.h"

using std::ifstream;
using std::ofstream;
using std::cerr;

class Logic {
private:
	Parser* parserPtr;
	EventStorage eventStore;
	Display display;
	vector<string> logStrings;

public:
	//for logging
	static const string LOG_FILE_NAME;
	static const string ADDFLOAT_STRING;
	static const string ADD_STRING;
	static const string DELETE_STRING;
	static const string EDIT_STRING;
	static const string SHOW_STRING;
	static const string SEARCH_STRING;
	static const string ERROR_STRING;

	//for exceptions
	static const string EXCEPTION_WRONG_ISFLOATING;

	static const int INVALID_NUMBER;


	//constructor, destructor
	Logic(void);
	~Logic();


	//getters
	Parser::commandType getCommand();
	Event getEvent();
	EventStorage getEventStorage();

	vector<Display::EVENT_STRING> getFloatingStrings();
	vector<Display::EVENT_STRING> getMainStrings();
	vector<string> getFeedbackStrings();
	vector<string> getErrorString();
	string getMainDisplayLabel();


	//executorss
	bool executeUserInput(string input);
	void executeCommand(Parser::commandType command, Event userEvent, bool& isDone);
	void deleteParserPtr();


	//others
	bool isNumber(string s);
	int convertNameToID(string name);
	void setDisplay(bool isFloat, vector<Event> eventsToSet, int id);
	string commandToString(Parser::commandType command);

	//log
	void log(string logString);
};

#endif