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

class LogicLog {
private:
	static const string LOG_FILE_NAME;

public:
	static const string CREATED_ADD;
	static const string CREATED_COMPLETE;
	static const string CREATED_DELETE;
	static const string CREATED_EDIT;
	static const string CREATED_SHOW;
	static const string CREATED_SHOWALL;
	static const string CREATED_SHOWALLIMPORTANT;
	static const string CREATED_SHOWCOMPLETED;
	static const string CREATED_SHOWFLOAT;
	static const string CREATED_SHOWIMPORTANCE;
	static const string CREATED_SEARCH;
	static const string QUEUEING_UNDO;
	static const string QUEUEING_REDO;
	static const string ISNUMBER_INPUT_EMPTY;


	void log(string logString);
	void log(int logInt);
	void log(string logString, int logInt);
};

#endif