#pragma once

#ifndef EVENTFACADE_H
#define EVENTFACADE_H

#include "EventModifier.h"
#include "EventStorage.h"

class EventFacade{
private:

	EventModifier modifier;
	EventOrganiser organiser;
	EventSearch searcher;
	EventLog logger;

public:
	/*Constructor, Destructor*/
	EventFacade(void);
	~EventFacade(void);

	/*Redirection to appropriate destination*/
	/*To EventModifer*/
	vector<Event> addEvent(Event newEvent);
	vector<Event> deleteEvent(int eventID, Event eventToBeDeleted);
	vector<Event> editEvent(int eventID, Event eventToBeEdited, Event editedEvent);
	//vector<Event> completeEvent();

	/*To EventSearch*/
	vector<Event> findNameOccurrence(string eventName); //checkMultipleResults
	vector<Event> findNameExact(string eventName); //checkExactString
	vector<Event> findLevelImportance(int level);
	vector<Event> findAllImportance();	
	//vector<Event> searchAllComponents(string infoToSearch, vector<Event> contentToSearch);
	//vector<Event> findCompleted();

	/*To EventOrganiser*/
	vector<Event> showDates(Event eventWithStartEndTimes);
	vector<Event> showAllFloatingEvents();
	vector<Event> showAllNormalEvents();
	

	/*To be done*/
	//complete to eventarchive
	//bool is completed -- event modifer
	//is deadline - storage changes
	//unit testing
	//exception for reading
};

#endif