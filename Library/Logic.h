#pragma once

#ifndef LOGIC_H
#define LOGIC_H


#include <cassert>
#include <fstream>
#include <sstream>
#include "Parser.h"
#include "EventFacade.h"
#include "LogicUpdater.h"
#include "Command.h"
#include "Executor.h"

using std::ifstream;
using std::ofstream;
using std::ostringstream;

class Logic {
private:
	Parser* parserPtr;
	EventFacade eventStore;
	LogicUpdater updater;
	Executor executor;
	vector<string> logStrings;

public:
	//for logging
	static const string LOG_FILE_NAME;
	static const string CREATING_ADD;
	static const string CREATED_ADD;
	static const string CREATING_DELETE;
	static const string CREATED_DELETE;
	static const string CREATING_EDIT;
	static const string CREATED_EDIT;
	static const string CREATING_SHOW;
	static const string CREATED_SHOW;
	static const string CREATING_SHOWALL;
	static const string CREATED_SHOWALL;
	static const string CREATING_SHOWFLOAT;
	static const string CREATED_SHOWFLOAT;
	static const string CREATING_SEARCH;
	static const string CREATED_SEARCH;
	static const string QUEUEING_UNDO;
	static const string QUEUEING_REDO;
	static const string CASE_0;
	static const string CASE_1;

	static const int INVALID_NUMBER;
	static const string EMPTY_STRING;


	//constructor, destructor
	Logic(void);
	~Logic();


	//getters
	EventFacade getEventStorage();
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
	bool isNumber(string s);
	string convertUserInputToName(string input);
	

	//log
	void log(string logString);
	void log(int logInt);
	void log(string logString, int logInt);
};

#endif