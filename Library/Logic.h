#pragma once

#ifndef LOGIC_H
#define LOGIC_H


#include <cassert>
#include <fstream>
#include <sstream>
#include "Parser.h"
#include "LogicUpdater.h"
#include "Executor.h"

using std::ifstream;
using std::ofstream;
using std::ostringstream;

class Logic {
private:
	Parser* parserPtr;
	EventFacade eventFacade;
	LogicUpdater updater;
	Executor executor;
	LogicLog logger;

public:
	static const int INVALID_NUMBER;
	static const string EMPTY_STRING;
	static const string COLON_SPACE;


	//constructor, destructor
	Logic(void);
	~Logic();


	//getters
	EventFacade getEventFacade();
	vector<LogicUpdater::EVENT_STRING> getFloatingStrings();
	vector<LogicUpdater::EVENT_STRING> getMainStrings();
	vector<string> getFeedbackStrings();
	vector<string> getErrorString();
	string getMainDisplayLabel();
	vector<tm> getTempMainDisplayLabel();


	//main executors
	bool executeUserInput(string input);
	Command* queueCommand(Executor& executor, Parser::commandType command, Event userEvent, string nameOfEvent);
	void setUpdater(Command* commandPtr, Parser::commandType, Event userEvent, string nameOfEvent);
	void setEventVectors(vector<Event>& normal, vector<Event>& floating, vector<Event> original);
	void setOneEventVector(vector<Event>& normal, vector<Event>& floating, Command* commandPtr, LogicUpdater updater);
	vector<tm> getTmVecFromEvents(vector<Event> normalEvents, LogicUpdater updater);
	void deleteParserPtr();


	//others
	bool isProperCommand(Parser::commandType commandType);
	bool isNumber(string s);
	bool isSameDate(tm date1, tm date2);
	int convertNameToID(string input);
};

#endif