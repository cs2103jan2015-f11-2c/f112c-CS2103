#pragma once

#ifndef SEARCH_H
#define SEARCH_H

#include "Event.h"
#include <assert.h>
#include "EventLog.h"

class Search{
private:
	vector<Event> searchResultsToReturn;
	EventLog logger;
public:
	//Constructor, Destructor
	Search(void);
	~Search(void);

	//Methods
	int searchForIndexWithEventID(int eventID, vector<Event> eventVectorToSearch);
	vector<Event> searchForEventWithEventName(string eventName, vector<Event> eventVectorToSearch);
	vector<Event> searchAllComponentsOfEvent(string informationToSearch, vector<Event> contentToSearch);

//	vector<int> searchForIdWithEventName(string eventName, vector<Event> eventVectorToSearch);

};

#endif