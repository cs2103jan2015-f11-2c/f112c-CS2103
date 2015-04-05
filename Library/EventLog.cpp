#include "EventLog.h"

const string EventLog::LOG_FILE_NAME = "EventLog.txt";

const string EventLog::MODIFIER = "EventModifier";
const string EventLog::ADD = "Adding";
const string EventLog::DELETE = "deleting";
const string EventLog::EDIT = "editing";
const string EventLog::COMPLETE = "completing";
const string EventLog::UNCOMPLETE = "uncompleting";


EventLog::EventLog(){
}

void EventLog::logStoragePosition(string functionName){
	std::ofstream writeFile;
	writeFile.open(LOG_FILE_NAME, ios::app);
	writeFile << functionName << endl;
	writeFile.close();
}

void EventLog::logStorageIntData(string location, int data){
	std::ofstream writeFile;
	writeFile.open(LOG_FILE_NAME, ios::app);
	writeFile << location << " " << data <<  endl;
	writeFile.close();
}

void EventLog::logStorageStringData(string location, string data){
	std::ofstream writeFile;
	writeFile.open(LOG_FILE_NAME, ios::app);
	writeFile << location << " " << data << endl;
	writeFile.close();
}