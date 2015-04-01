#pragma once

#ifndef EVENTSEARCH_H
#define EVENTSEARCH_H

#include "EventOrganiser.h"

class EventSearch{
private:
	
	//These are results to improve readability
	static const int EventSearch::NOT_FOUND;
	static const int EventSearch::MAX_LEVEL;
	static const int EventSearch::MIN_LEVEL;
	
	EventOrganiser organiser;
	EventLog logger;

public:
	//Constructor, Destructor
	EventSearch(void);
	~EventSearch(void);
	
	//Search Methods
	vector<Event> searchNameOccurrence(string eventName);
	vector<Event> searchNameExact(string eventName);
	vector<Event> searchLevelImportance(int level);
	vector<Event> searchAllImportance();

	//Support methods for search
	vector<Event> searchEventWithName(string eventName, vector<Event> eventVectorToSearch);
	vector<Event> searchExactString(string eventName, vector<Event> eventVectorToSearch);
	vector<Event> searchEventWithImportance(int level, vector<Event> vectorToSearch);	
	vector<Event> searchEventWithAllImportance(vector<Event> vectorToSearch);	
	vector<Event> combineResults(vector<Event> floatingEvents, vector<Event> normalEvents);

	//Support methods for del and edit
	int searchIndexWithID(int eventID, vector<Event> eventVectorToSearch);

	vector<Event> searchAllComponentsOfEvent(string informationToSearch, vector<Event> contentToSearch);

};

#endif