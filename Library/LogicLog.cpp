#include "LogicLog.h"

const string LogicLog::LOG_FILE_NAME = "LogicLog.txt";

const string LogicLog::CREATED_ADD = "created add command";
const string LogicLog::CREATED_COMPLETE = "created complete command";
const string LogicLog::CREATED_DELETE = "created delete command";
const string LogicLog::CREATED_EDIT = "created edit command";
const string LogicLog::CREATED_SHOW = "created show command";
const string LogicLog::CREATED_SHOWALL = "created show all command";
const string LogicLog::CREATED_SHOWALLIMPORTANT = "created show all command";
const string LogicLog::CREATED_SHOWCOMPLETED = "created show completed command";
const string LogicLog::CREATED_SHOWFLOAT = "created showfloat command";
const string LogicLog::CREATED_SHOWIMPORTANCE = "created show importance command";
const string LogicLog::CREATED_SEARCH = "created search command";
const string LogicLog::QUEUEING_UNDO = "queueing undo";
const string LogicLog::QUEUEING_REDO = "queueing redo";
const string LogicLog::ISNUMBER_INPUT_EMPTY = "isNumber input string empty";


void LogicLog::log(string logString) {
	ofstream outFile;
	outFile.open(LOG_FILE_NAME, ios::app);
	outFile << logString;
	outFile.close();
}

void LogicLog::log(int logInt) {
	ostringstream outString;
	outString << logInt;

	ofstream outFile;
	outFile.open(LOG_FILE_NAME, ios::app);
	outFile << outString.str();
	outFile.close();
}

void LogicLog::log(string logString, int logInt) {
	ostringstream outString;
	outString << " " << logInt;

	ofstream outFile;
	outFile.open(LOG_FILE_NAME, ios::app);
	outFile << logString + outString.str();
	outFile.close();
}