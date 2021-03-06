//@author A0111089L
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
	

	//supporting api
	bool isProperCommand(Parser::CommandType commandType);
	bool isSameDate(tm date1, tm date2);
	bool isNumber(string s);
	void removeLabel(string& feedback);


private:
	//main private methods
	bool isDataRead();
	Command* queueCommand(Parser::CommandType command, Event& userEvent, string nameOfEvent);
	void setUpdater(Command* commandPtr, Parser::CommandType, Event userEvent, string nameOfEvent);
	void setEventVectors(vector<Event>& normal, vector<Event>& floating, vector<Event> original);
	void setOneEventVector(vector<Event>& normal, vector<Event>& floating, Command* commandPtr, vector<tm>& tmVec);
	vector<tm> getTmVecFromEvents(vector<Event> normalEvents);
	void deleteParserPtr();


	//other private methods
	int convertNameToID(string input);
	bool isEventsCompleted(vector<Event>);
	string showTypeToString(Parser::CommandType cmd, int importance);	
	void setNewID(Event& userEvent);
	void clearRedo();
	Event createTempEvent(string name, int id);
	vector<Event> getExactMatches(string name);
};

#endif