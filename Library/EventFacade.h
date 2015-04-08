#pragma once

#ifndef EVENTFACADE_H
#define EVENTFACADE_H

#include "EventModifier.h"

class EventFacade{
public:
	/*Constructor, Destructor*/
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