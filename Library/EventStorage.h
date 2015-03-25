#pragma once

#ifndef EVENTSTORAGE_H
#define EVENTSTORAGE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include "Event.h"
#include "EventArchive.h"
#include "Search.h"
#include "EventOrganiser.h"
#include "Conversion.h"
#include "EventLog.h"
#include <assert.h>

class EventStorage{
private:

	//These are variables to improve readability
	static const int EventStorage::INVALID;

	//These are vectors that store information
	vector<Event> currentContent;
	vector<Event> currentFloatingContent;
	static const std::string currentFile;
	EventOrganiser eventOrganiser;
	Search search;
	Conversion conversion;
	EventLog logger;

	vector<EventArchive> archiveContent;
	EventArchive archiveObject; 
	vector<Event> undoVector;
	vector<Event> redoVector;

public:
	//Constructor, Destructor
	EventStorage(void); //will read the currentFile into the currentContent vector 
	~EventStorage(void);

	//Methods
	void writeToCurrentFile();
	void readToCurrentContent();

	//Add Methods
	vector<Event> addEvent(Event newEvent);

	//Support Methods
	vector<Event> checkMultipleResults(string eventName);
	vector<Event> checkExactString(string eventName);

	//Delete Methods
	vector<Event> deleteEvent(int eventID, Event eventToBeDeleted);

	//Edit Methods
	vector<Event> editEvent(int eventID, Event eventToBeEdited, Event editedEvent);
		
	//getters
	vector<Event> getAllNormalEvents();
	vector<Event> getAllFloatingEvents();
	vector<Event> getShowDay(int day, int month, int year, vector<Event> currentContent);
	
	vector<Event> searchAllComponents(string infoToSearch, vector<Event> contentToSearch);
	vector<Event> showDates(Event eventWithStartEndTimes);

};


#endif