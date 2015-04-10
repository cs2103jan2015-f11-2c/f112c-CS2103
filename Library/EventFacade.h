//==================================================================================================
//EventFacade is a thin class which provides a simple interface to the client, hiding the internal
//complexity of the storage. It purely redirects desired function calls to the appropriate destination.
//
//The 4 main destinations are:
// 1) EventModifier
// 2) EventSearch
// 3) EventOrgansier
// 4) EventStorage
//
//When an EventFacade object is first created, it will construct the first storage instance. Establising
//the internal and external(text file) storages.
//
//All redirections are logged.
//==================================================================================================

#pragma once

#ifndef EVENTFACADE_H
#define EVENTFACADE_H

#include "EventModifier.h"

class EventFacade{
public:
	EventFacade(void);
	~EventFacade(void);

	/*Redirection to appropriate destination*/
	/*To EventModifer*/
	vector<Event> addEvent(Event newEvent);
	vector<Event> deleteEvent(Event deletedEvent);
	vector<Event> editEvent(Event beforeEdit, Event afterEdit);
	vector<Event> completeEvent(Event completedEvent);
	vector<Event> uncompleteEvent(Event uncompletedEvent);

	/*To EventSearch*/
	vector<Event> findNameOccurrence(string eventName); 
	vector<Event> findNameExact(string eventName); 
	vector<Event> findCompletedNameOccurrence(string eventName);
	vector<Event> findCompletedNameExact(string eventName);
	vector<Event> findLevelImportance(int level);
	vector<Event> findAllImportance();
	Event findEventWithID(int eventID);
	Event findCompletedEventWithID(int eventID);

	/*To EventOrganiser*/
	vector<Event> showDates(Event eventWithStartEndTimes);
	vector<Event> showAllNormalEvents();	
	vector<Event> showAllFloatingEvents();
	vector<Event> showAllNormalCompleted();
	vector<Event> showAllFloatingCompleted();

	/*To EventStorage*/
	bool dataRead();
	int getDataID();

private:

	EventModifier modifier;
	EventOrganiser organiser;
	EventSearch searcher;
	EventLog logger;
};

#endif