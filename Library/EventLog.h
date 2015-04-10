//==================================================================================================
//EventLog is responsible for writing logs onto a text file(EventLog.txt) for reference and debugging.
//Combinations of log messages are used liberally throughout the storage component
//==================================================================================================
#pragma once

#ifndef EVENTLOG_H
#define EVENTLOG_H

#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::ofstream;
using std::ostringstream;
using std::ios;
using std::endl;

class EventLog {
public:
	EventLog();

	/*EventFacade*/
	static const string FACADE;
	
	/*EventModifier*/
	static const string MODIFIER;
	static const string ADD;
	static const string DELETE;
	static const string EDIT;
	static const string COMPLETE;
	static const string UNCOMPLETE;
	static const string FLOAT_TO_NORMAL;
	static const string NORMAL_TO_FLOAT;
	static const string CORRECT_DATE;

	/*EventSearch*/
	static const string SEARCH;
	static const string SEARCH_NAME_OCCURRENCE;
	static const string SEARCH_NAME_EXACT;
	static const string SEARCH_LEVEL_IMPORTANCE;
	static const string SEARCH_ALL_IMPORTANCE;
	static const string SEARCH_INDEX_WITH_ID;
	static const string SEARCH_EVENT_WITH_ID;
	static const string SEARCH_COMPLETED_EVENT_WITH_ID;

	/*EventOrgansier*/
	static const string ORGANISER;
	static const string SHOW_DATES;
	static const string SHOW_ALL_NORMAL_CURRENT;
	static const string SHOW_ALL_NORMAL_COMPLETED;
	static const string SHOW_ALL_FLOATING_CURRENT;
	static const string SHOW_ALL_FLOATING_COMPLETED;
	static const string SHOW_EVENTS;
	static const string SHOW_DATES_FROM_NORMAL_CONTENT;
	static const string DATE_RANGE;
	static const string SHOW_DATE_RANGE;

	/*EventStorage*/
	static const string STORAGE;
	static const string START_UP;
	static const string READING_ERROR;
	static const string GET_NORMAL_CONTENT;
	static const string GET_FLOATING_CONTENT;
	static const string DATA_READ;
	static const string DATA_ID;

	static const string NORMAL;
	static const string FLOATING;
	static const string EXIT;
	
	//Methods
	void log(string functionName);
	void log(string location, int data);
	void log(int data);

private:
	static const std::string LOG_FILE_NAME;

};

#endif