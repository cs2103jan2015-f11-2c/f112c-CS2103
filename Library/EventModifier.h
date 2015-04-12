//@author A0113860M
//==================================================================================================
//EventModifier is a class that deals with the modification of an event or its attributes.
//The internal and external storages are then updated based on the action executed.
//
//EventModifier comprises of 5 main methods:
// 1)Adding an event
// 2)Deleting an event
// 3)Editing an event
// 4)completing an event
// 5)uncompleting an event
//
//The returning vectors varies according to the type of event modified:
//		Event Modified			::			Output
//	Current Normal Event		:: returns uncompleted events within the start and end date of the modified event.
//	Current Floating Event		:: returns all uncompleted floating events.
//	Completed Normal Event		:: returns completed events within the start and end date of the modified event.
//	Completed Floating Event	:: returns all completed floating events.
//
//==================================================================================================
#pragma once

#ifndef EVENTMODIFIER_H
#define EVENTMODIFIER_H

#include "EventSearch.h"
#include "EventOrganiser.h"
#include <assert.h>

class EventModifier{
public:
	EventModifier(void);
	~EventModifier(void);
	
	/*Main Methods*/
	vector<Event> add(Event newEvent);
	vector<Event> del(Event deletedEvent);
	vector<Event> edit(Event beforeEdit, Event afterEdit);	
	vector<Event> complete(Event completedEvent);
	vector<Event> uncomplete(Event uncompletedEvent);

private:

	//These are variables to improve readability
	static const int EventModifier::NOT_FOUND;
	static const int EventModifier::DEFAULT;

	EventOrganiser organiser;
	EventSearch searcher;
	EventLog logger;

	/*Add Method*/
	void addNormal(Event newEvent);
	void addFloat(Event newEvent);

	/*Delete Method*/
	vector<Event> deleteFloat(int index);
	vector<Event> deleteNormal(int index);

	/*Edit Method*/
	vector<Event> editNormal(int index, Event afterEdit);
	vector<Event> editFloating(int index, Event afterEdit);
	vector<Event> editFloatingToNormal(int index, Event afterEdit);
	vector<Event> editNormalToFloating(int index, Event afterEdit);
	void correctDate(Event *tempEvent);

	/*Complete Method*/
	vector<Event> completeNormal(int index, Event completedEvent);
	vector<Event> completeFloat(int index);
	vector<Event> markCompleted(Event completedEvent, vector<Event> completedEventDate);
	
	/*Uncomplete Method*/
	vector<Event> uncompleteNormal(int index);
	vector<Event> uncompleteFloat(int index);

	/*delete/edit/complete support methods*/
	int findNormalIndex(int eventID);
	int findFloatingIndex(int eventID);	
	int findNormalCompletedIndex(int eventID);
	int findFloatingCompletedIndex(int eventID);

};

#endif