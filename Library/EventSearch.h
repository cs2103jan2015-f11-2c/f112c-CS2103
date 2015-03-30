#pragma once

#ifndef EVENTSEARCH_H
#define EVENTSEARCH_H

#include "EventOrganiser.h"

class EventSearch{
private:
	
	//These are results to improve readability
	static const int EventSearch::NOT_FOUND;
	
	EventOrganiser organiser;
	//EventStorage storage;
	EventLog logger;

public:
	//Constructor, Destructor
	EventSearch(void);
	~EventSearch(void);
	
	//Search Methods
	vector<Event> searchNameOccurrence(string eventName);
	vector<Event> searchNameExact(string eventName);

	//Support methods for search
	vector<Event> searchEventWithName(string eventName, vector<Event> eventVectorToSearch);
	vector<Event> searchExactString(string eventName, vector<Event> eventVectorToSearch);

	//Support methods for del and edit
	int searchIndexWithID(int eventID, vector<Event> eventVectorToSearch);

	vector<Event> searchAllComponentsOfEvent(string informationToSearch, vector<Event> contentToSearch);

};

#endif