#pragma once

#ifndef LOGIC_H
#define LOGIC_H


#include <cassert>
#include <fstream>
#include "Parser.h"
#include "EventStorage.h"
#include "Display.h"
#include "ICommand.h"
#include "Executor.h"

using std::ifstream;
using std::ofstream;

class Logic {
private:
	Parser* parserPtr;
	EventStorage eventStore;
	Display display;
	Executor executor;
	vector<string> logStrings;

public:
	//for logging
	static const string LOG_FILE_NAME;
	static const string ADDFLOAT_EXECUTING;
	static const string ADD_EXECUTING;
	static const string DELETE_EXECUTING;
	static const string EDIT_EXECUTING;
	static const string SHOW_EXECUTING;
	static const string SEARCH_EXECUTING;
	static const string ERROR_EXECUTING;
	static const string CASE_0;
	static const string CASE_1;

	//for exceptions
	static const string EXCEPTION_WRONG_ISFLOATING;

	static const int INVALID_NUMBER;


	//constructor, destructor
	Logic(void);
	~Logic();


	//getters
	EventStorage getEventStorage();

	vector<Display::EVENT_STRING> getFloatingStrings();
	vector<Display::EVENT_STRING> getMainStrings();
	vector<string> getFeedbackStrings();
	vector<string> getErrorString();
	string getMainDisplayLabel();


	//executors
	bool executeUserInput(string input);
	void executeCommand(Parser::commandType command, Event userEvent, bool& isDone);
	ICommand* queueCommand(Executor& executor, Parser::commandType command, Event userEvent, string nameOfEvent);
	void setDisplay(ICommand* commandPtr, Parser::commandType, Event userEvent);
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