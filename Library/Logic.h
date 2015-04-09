#pragma once

#ifndef LOGIC_H
#define LOGIC_H


#include <cassert>
#include "Parser.h"
#include "LogicUpdater.h"
#include "Executor.h"


class Logic {
private:
	Parser* parserPtr;
	EventFacade eventFacade;
	LogicUpdater updater;
	Executor executor;

	int lastID;
	string lastShowType;

	LogicLog logger;

public:
	static const string EMPTY_STRING;
	static const string COMMA_SPACE;
	static const string EXCLAMATION_MARK;
	static const char CHAR_OPEN_SQUARE_BRACKET;
	static const char CHAR_CLOSE_SQUARE_BRACKET;


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


	//main api
	bool executeUserInput(string input);
	bool isDataRead();
	Command* queueCommand(Parser::commandType command, Event& userEvent, string nameOfEvent);
	void setUpdater(Command* commandPtr, Parser::commandType, Event userEvent, string nameOfEvent);
	void setEventVectors(vector<Event>& normal, vector<Event>& floating, vector<Event> original);
	void setOneEventVector(vector<Event>& normal, vector<Event>& floating, Command* commandPtr, vector<tm>& tmVec);
	vector<tm> getTmVecFromEvents(vector<Event> normalEvents);
	void deleteParserPtr();


	//supporting methods
	bool isProperCommand(Parser::commandType commandType);
	bool isNumber(string s);
	bool isSameDate(tm date1, tm date2);
	int convertNameToID(string input);
	string showTypeToString(Parser::commandType cmd, int importance);	
	void removeLabel(string& feedback);
	void setNewID(Event& userEvent);
	Event createTempEvent(string name, int id);
};

#endif