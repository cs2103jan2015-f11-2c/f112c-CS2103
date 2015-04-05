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
private:
	static const std::string LOG_FILE_NAME;

public:
	EventLog();
	
	/*EventModifier*/
	static const string MODIFIER;
	static const string ADD;
	static const string DELETE;
	static const string EDIT;
	static const string COMPLETE;
	static const string UNCOMPLETE;


	void logStoragePosition(string functionName);
	void logStorageIntData(string location, int data);
	void logStorageStringData(string location, string data);

};

#endif