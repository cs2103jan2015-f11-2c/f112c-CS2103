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

	//These are results to improve readability
	static const int Search::NOT_FOUND;

public:
	//Constructor, Destructor
	Search(void);
	~Search(void);

	//Methods
	int searchIndexWithID(int eventID, vector<Event> eventVectorToSearch);
	vector<Event> searchEventWithName(string eventName, vector<Event> eventVectorToSearch);
	vector<Event> searchAllComponentsOfEvent(string informationToSearch, vector<Event> contentToSearch);
	vector<Event> searchExactName(string eventName, vector<Event> eventVectorToSearch);

//	vector<int> searchForIdWithEventName(string eventName, vector<Event> eventVectorToSearch);

};

#endif