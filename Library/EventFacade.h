#pragma once

#ifndef EVENTFACADE_H
#define EVENTFACADE_H

#include "EventModifier.h"

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
	vector<Event> completeEvent(int eventID, Event completedEvent);

	/*To EventSearch*/
	vector<Event> findNameOccurrence(string eventName); //checkMultipleResults
	vector<Event> findNameExact(string eventName); //checkExactString
	vector<Event> findLevelImportance(int level);
	vector<Event> findAllImportance();
	//vector<Event> searchAllComponents(string infoToSearch, vector<Event> contentToSearch);
	//vector<Event> findCompleted();

	/*To EventOrganiser*/
	vector<Event> showDates(Event eventWithStartEndTimes);
	vector<Event> showAllNormalEvents();	
	vector<Event> showAllFloatingEvents();
	vector<Event> showAllNormalCompleted();
	vector<Event> showAllFloatingCompleted();

	/*To be done*/
	//unit testing
	//exception for reading

	//vector<Event> completeEvent(int eventID, Event eventToBeCompleted)  push to completed vector
	//set isCompleted true;
	//return day with the eventtobecomplete marked to true
	//is complete file
	//showCompleted

};

#endif