#pragma once

#ifndef LOGIC_H
#define LOGIC_H


#include <cassert>
#include <fstream>
#include <sstream>
#include "Parser.h"
#include "EventStorage.h"
#include "LogicUpdater.h"
#include "ICommand.h"
#include "Executor.h"

using std::ifstream;
using std::ofstream;
using std::ostringstream;

class Logic {
private:
	Parser* parserPtr;
	EventStorage eventStore;
	LogicUpdater updater;
	Executor executor;
	vector<string> logStrings;

public:
	//for logging
	static const string LOG_FILE_NAME;
	static const string CREATING_ADD;
	static const string CREATING_DELETE;
	static const string CREATING_EDIT;
	static const string CREATING_SHOW;
	static const string CREATING_SHOWALL;
	static const string CREATING_SHOWFLOAT;
	static const string CREATING_SEARCH;
	static const string CREATING_UNDO;
	static const string CREATING_REDO;
	static const string CASE_0;
	static const string CASE_1;

	static const int INVALID_NUMBER;


	//constructor, destructor
	Logic(void);
	~Logic();


	//getters
	EventStorage getEventStorage();

	vector<LogicUpdater::EVENT_STRING> getFloatingStrings();
	vector<LogicUpdater::EVENT_STRING> getMainStrings();
	vector<string> getFeedbackStrings();
	vector<string> getErrorString();
	string getMainDisplayLabel();
	vector<tm> getTempMainDisplayLabel();


	//executors
	bool executeUserInput(string input);
	ICommand* queueCommand(Executor& executor, Parser::commandType command, Event userEvent, string nameOfEvent);
	void setDisplay(ICommand* commandPtr, Parser::commandType, Event userEvent, string nameOfEvent, bool& isDone);
	void setEventVector(vector<Event>& normal, vector<Event>& floating, vector<Event> original);
	void deleteParserPtr();


	//others
	bool isNumber(string s);
	int convertNameToID(string name);
	void setDisplay(bool isFloat, vector<Event> eventsToSet, int id);

	//log
	void log(string logString);
};

#endif