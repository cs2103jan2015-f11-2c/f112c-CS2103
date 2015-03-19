#pragma once

#ifndef EVENTLOG_H
#define EVENTLOG_H

#include <iostream>
#include <fstream>
#include <string>

class EventLog {
private:
	static const std::string textFile;

public:
	EventLog();
	
	void logStoragePosition(std::string functionName);
	void logStorageIntData(std::string location, int data);
	void logStorageStringData(std::string location, std::string data);

};

#endif