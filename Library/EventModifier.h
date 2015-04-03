#pragma once

#ifndef EVENTMODIFIER_H
#define EVENTMODIFIER_H

#include "EventSearch.h"
#include "EventOrganiser.h"
#include <assert.h>

//Logging Positions
const string ADD = "Adding..";
const string DELETE = "deleting..";
const string EDIT = "editing..";
const string COMPLETE = "completing..";

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
	vector<Event> del(int eventID, Event eventToBeDeleted);
	vector<Event> deletefloat(int index);
	vector<Event> deleteNormal(int index);

	/*Edit Method*/
	vector<Event> edit(int eventID, Event eventToBeEdited, Event editedEvent);	
	vector<Event> editNormal(int index, Event editedEvent);
	vector<Event> editFloating(int index, Event editedEvent);
	
	/*Complete Method*/
	vector<Event> complete(int eventID, Event completedEvent);
	vector<Event> completeNormal(int index, int eventID);
	vector<Event> completeFloat(int index);
	vector<Event> markCompleted(int eventID, vector<Event> completedEventDates);
	
	/*Uncomplete Method*/
	vector<Event> uncomplete(int eventID, Event UncompletedEvent);
	vector<Event> uncompleteNormal(int index, int eventID);
	vector<Event> uncompleteFloat(int index);

	/*delete/edit/complete support methods*/
	int findNormalIndex(int eventID);
	int findFloatingIndex(int eventID);	
	int findNormalCompletedIndex(int eventID);
	int findFloatingCompletedIndex(int eventID);

};


#endif