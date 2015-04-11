//@author A0113860M

#include "EventLog.h"

const string EventLog::LOG_FILE_NAME = "EventLog.txt";

const string EventLog::FACADE = "EventFacade ";

const string EventLog::MODIFIER = "EventModifier ";
const string EventLog::ADD = "Add ";
const string EventLog::DELETE = "Delete ";
const string EventLog::EDIT = "Edit ";
const string EventLog::COMPLETE = "Complete ";
const string EventLog::UNCOMPLETE = "Uncomplete ";
const string EventLog::FLOAT_TO_NORMAL = "floatingToNormal ";
const string EventLog::NORMAL_TO_FLOAT = "normalToFLoating ";
const string EventLog::CORRECT_DATE = "correctDate ";

const string EventLog::SEARCH = "EventSearch ";
const string EventLog::SEARCH_NAME_OCCURRENCE = "searchNameOccurrence ";
const string EventLog::SEARCH_NAME_EXACT = "searchNameExact ";
const string EventLog::SEARCH_LEVEL_IMPORTANCE = "searchLevelImportance ";
const string EventLog::SEARCH_ALL_IMPORTANCE = "searchAllImportance ";
const string EventLog::SEARCH_INDEX_WITH_ID = "searchIndexWithID ";
const string EventLog::SEARCH_EVENT_WITH_ID = "searchEventWithID ";
const string EventLog::SEARCH_COMPLETED_EVENT_WITH_ID = "searchCompletedEventWithID ";

const string EventLog::ORGANISER = "EventOrgansier ";
const string EventLog::SHOW_DATES = "showDates ";
const string EventLog::SHOW_ALL_NORMAL_CURRENT = "showAllNormalCurrent ";
const string EventLog::SHOW_ALL_NORMAL_COMPLETED = "showAllNormalCompleted ";
const string EventLog::SHOW_ALL_FLOATING_CURRENT = "showAllFloatingCurrent ";
const string EventLog::SHOW_ALL_FLOATING_COMPLETED = "showAllFloatingCompleted ";
const string EventLog::SHOW_EVENTS = "showEvents ";
const string EventLog::SHOW_DATES_FROM_NORMAL_CONTENT = "showDatesFromNormalContent ";
const string EventLog::DATE_RANGE = "dateRange ";
const string EventLog::SHOW_DATE_RANGE = "showDateRange ";

const string EventLog::STORAGE = "EventStorage ";
const string EventLog::START_UP = "...Syncing with storages...";
const string EventLog::READING_ERROR = "ERROR IN READING ";
const string EventLog::GET_NORMAL_CONTENT = "getNormalContent ";
const string EventLog::GET_FLOATING_CONTENT = "getFloatingContent ";
const string EventLog::DATA_READ = "dataRead ";
const string EventLog::DATA_ID = "dataID ";


const string EventLog::NORMAL = "Normal "; 
const string EventLog::FLOATING = "Floating ";
const string EventLog::EXIT = "Exit ";
const string EventLog::ERROR = "ERROR: ";

EventLog::EventLog(){
}

void EventLog::log(string functionName){
	std::ofstream writeFile;
	writeFile.open(LOG_FILE_NAME, ios::app);
	writeFile << functionName << endl;
	writeFile.close();
}

void EventLog::log(string location, int data){
	std::ofstream writeFile;
	writeFile.open(LOG_FILE_NAME, ios::app);
	writeFile << location << " " << data <<  endl;
	writeFile.close();
}

void EventLog::log(int data){
	std::ofstream writeFile;
	writeFile.open(LOG_FILE_NAME, ios::app);
	writeFile << data << endl;
	writeFile.close();
}