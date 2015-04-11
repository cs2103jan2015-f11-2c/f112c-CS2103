//@author A0111089L
#include "LogicLog.h"

const string LogicLog::LOG_FILE_NAME = "LogicLog.txt";

const string LogicLog::CREATED = "created ";
const string LogicLog::EXECUTED = "executed ";
const string LogicLog::ADD = "add command";
const string LogicLog::COMPLETE = "complete command";
const string LogicLog::UNCOMPLETE = "uncomplete command";
const string LogicLog::DELETE = "delete command";
const string LogicLog::EDIT = "edit command";
const string LogicLog::SHOW = "show command";
const string LogicLog::SHOWALL = "show all command";
const string LogicLog::SHOWALLIMPORTANT = "show all important command";
const string LogicLog::SHOWCOMPLETED = "show completed command";
const string LogicLog::SHOWFLOAT = "showfloat command";
const string LogicLog::SHOWIMPORTANCE = "show importance command";
const string LogicLog::SEARCH = "search command";
const string LogicLog::QUEUEING_UNDO = "queueing undo";
const string LogicLog::QUEUEING_REDO = "queueing redo";
const string LogicLog::ISNUMBER_INPUT_EMPTY = "isNumber input string empty";
const string LogicLog::CASE_0 = "entered case 0 for ";
const string LogicLog::CASE_1 = "entered case 1 for ";
const string LogicLog::DEFAULT = "entered default for ";
const string LogicLog::UNDOSTACK_SIZE = "undoStack size ";
const string LogicLog::REDOSTACK_SIZE = "redoStack size ";
const string LogicLog::SUCCEEDED = " succeeded";
const string LogicLog::ERROR = "error";


void LogicLog::log(string logString) {
	ofstream outFile;
	outFile.open(LOG_FILE_NAME, ios::app);
	outFile << logString << endl;
	outFile.close();
}

void LogicLog::log(int logInt) {
	ostringstream outString;
	outString << logInt;

	ofstream outFile;
	outFile.open(LOG_FILE_NAME, ios::app);
	outFile << outString.str() << endl;
	outFile.close();
}

void LogicLog::log(string logString, int logInt) {
	ostringstream outString;
	outString << logInt;

	ofstream outFile;
	outFile.open(LOG_FILE_NAME, ios::app);
	outFile << logString + outString.str() << endl;
	outFile.close();
}