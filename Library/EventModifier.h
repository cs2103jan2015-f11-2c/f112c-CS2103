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
	/*Add support methods*/
	void addNormal(Event newEvent);
	void addfloat(Event newEvent);

	/*Delete Method*/
	vector<Event> del(int eventID, Event eventToBeDeleted);
	/*delete support methods*/
	vector<Event> deletefloat(int index);
	vector<Event> deleteNormal(int index);

	/*Edit Method*/
	vector<Event> edit(int eventID, Event eventToBeEdited, Event editedEvent);	

	/*Edit support methods*/
	vector<Event> editNormal(int index, Event editedEvent);
	vector<Event> editFloating(int index, Event editedEvent);

	/*delete edit support methods*/
	int findNormalIndex(int eventID);
	int findFloatingIndex(int eventID);
};


#endif