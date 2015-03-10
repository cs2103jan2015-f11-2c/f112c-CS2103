#pragma once

#ifndef SEARCH_H
#define SEARCH_H

#include "Event.h"

class Search{
private:
	vector<Event> searchResultsToReturn;

public:
	//Constructor, Destructor
	Search(void);
	~Search(void);

	//Methods
	int searchForIndexWithEventID(int eventID, vector<Event> eventVectorToSearch);
	vector<int> searchForIdWithEventName(string eventName, vector<Event> eventVectorToSearch);

};

#endif