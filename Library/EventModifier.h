#pragma once

#ifndef EVENTMODIFIER_H
#define EVENTMODIFIER_H

#include "EventSearch.h"
#include "EventOrganiser.h"
#include <assert.h>

class EventModifier{
private:

	//These are variables to improve readability
	static const int EventModifier::NOT_FOUND;
	static const int EventModifier::DEFAULT;

	EventOrganiser organiser;
	EventSearch searcher;
	EventLog logger;




public:
	/*Constructor, Destructor*/
	EventModifier(void);
	~EventModifier(void);

	/*Add Method*/
	vector<Event> add(Event newEvent);
	void addNormal(Event newEvent);
	void addfloat(Event newEvent);

	/*Delete Method*/
	vector<Event> del(Event deletedEvent);
	vector<Event> deletefloat(int index);
	vector<Event> deleteNormal(int index);

	/*Edit Method*/
	vector<Event> edit(Event beforeEdit, Event afterEdit);	
	vector<Event> editNormal(int index, Event afterEdit);
	vector<Event> editFloating(int index, Event afterEdit);
	vector<Event> editFloatingToNormal(int index, Event afterEdit);
	vector<Event> editNormalToFloating(int index, Event afterEdit);

	/*Complete Method*/
	vector<Event> complete(Event completedEvent);
	vector<Event> completeNormal(int index, Event completedEvent);
	vector<Event> completeFloat(int index);
	vector<Event> markCompleted(Event completedEvent, vector<Event> completedEventDate);
	
	/*Uncomplete Method*/
	vector<Event> uncomplete(Event uncompletedEvent);
	vector<Event> uncompleteNormal(int index);
	vector<Event> uncompleteFloat(int index);

	/*delete/edit/complete support methods*/
	int findNormalIndex(int eventID);
	int findFloatingIndex(int eventID);	
	int findNormalCompletedIndex(int eventID);
	int findFloatingCompletedIndex(int eventID);

};


#endif