#pragma once

#ifndef LOGICLOG_H
#define LOGICLOG_H

#include <iostream>
#include <fstream>
#include <sstream>

using std::string;
using std::ofstream;
using std::ostringstream;
using std::ios;
using std::endl;

class LogicLog {
private:
	static const string LOG_FILE_NAME;

public:
	static const string CREATED;
	static const string EXECUTED;
	static const string ADD;
	static const string COMPLETE;
	static const string DELETE;
	static const string EDIT;
	static const string SHOW;
	static const string SHOWALL;
	static const string SHOWALLIMPORTANT;
	static const string SHOWCOMPLETED;
	static const string SHOWFLOAT;
	static const string SHOWIMPORTANCE;
	static const string SEARCH;
	static const string QUEUEING_UNDO;
	static const string QUEUEING_REDO;
	static const string ISNUMBER_INPUT_EMPTY;

	static const string CASE_0;
	static const string CASE_1;
	static const string DEFAULT;

	void log(string logString);
	void log(int logInt);
	void log(string logString, int logInt);
};

#endif