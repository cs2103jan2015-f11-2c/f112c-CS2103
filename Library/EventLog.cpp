#include "EventLog.h"

const std::string EventLog::textFile = "EventLog.txt";

EventLog::EventLog(){
}

void EventLog::logStoragePosition(std::string functionName){
	std::ofstream writeFile;
	writeFile.open(textFile,std::ios::app);
	writeFile << "Entered " << functionName << std::endl;
	writeFile.close();
}

void EventLog::logStorageIntData(std::string location, int data){
	std::ofstream writeFile;
	writeFile.open(textFile,std::ios::app);
	writeFile << "Data: " << data << " at location: " << location << std::endl;
	writeFile.close();
}

void EventLog::logStorageStringData(std::string location, std::string data){
	std::ofstream writeFile;
	writeFile.open(textFile,std::ios::app);
	writeFile << "Data: " << data << " at location: " << location << std::endl;
	writeFile.close();
}