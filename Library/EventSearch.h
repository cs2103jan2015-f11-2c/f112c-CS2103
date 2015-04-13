//@author A0113860M
//========================================================================================
//EventSearch class is responsible for locating an event in storage. Searches can be based
//on name, importance, or ID.
//
//Search by name and importance are the basic APIs for an external client to call through
//eventFacade. Search by ID on the other hand is mostly used within Storage.
//
//It also utilises EventOrganiser to obtain the necessary filtered data and to format the
//data by date.
//========================================================================================
#pragma once

#ifndef EVENTSEARCH_H
#define EVENTSEARCH_H

#include "EventOrganiser.h"

class EventSearch{
public:
	EventSearch(void);
	~EventSearch(void);
	
	//Main methods
	//2 main checks for multiple current event names
	vector<Event> searchCurrentNameOccurrence(string eventName);
	vector<Event> searchCurrentNameExact(string eventName);

	//2 main checks for multiple completed event names
	vector<Event> searchCompletedNameOccurrence(string eventName);	
	vector<Event> searchCompletedNameExact(string eventName);

	//Importance searches
	vector<Event> searchLevelImportance(int level);
	vector<Event> searchAllImportance();

	//general search method
	Event searchEventWithID(int eventID);
	Event searchCompletedEventWithID(int eventID);

	//Support methods for del and edit
	int searchIndexWithID(int eventID, vector<Event> eventVectorToSearch);

private:
	
	//These are results to improve readability
	static const int EventSearch::NOT_FOUND;
	static const int EventSearch::MAX_LEVEL;
	static const int EventSearch::MIN_LEVEL;
	static const string EventSearch::ERROR_1;
	
	EventOrganiser organiser;
	EventLog logger;

	//Support methods for APIs
	vector<Event> searchNameOccurrence(string eventName, vector<Event> normal, vector<Event> floating);
	vector<Event> searchNameExact(string eventName, vector<Event> normal, vector<Event> floating);
	vector<Event> searchEventWithName(string eventName, vector<Event> eventVectorToSearch);
	vector<Event> searchExactString(string eventName, vector<Event> eventVectorToSearch);
	vector<Event> searchEventWithImportance(int level, vector<Event> vectorToSearch);	
	vector<Event> searchEventWithAllImportance(vector<Event> vectorToSearch);	
	vector<Event> combineResults(vector<Event> floatingEvents, vector<Event> normalEvents);

};

#endif