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

	//Delete Methods
	vector<Event> deleteEvent(int eventID, Event eventToBeDeleted);

	//Edit Methods
	vector<Event> editEvent(int eventID, Event eventToBeEdited, Event editedEvent);
		
	//getters
	vector<Event> getAllNormalEvents();
	vector<Event> getAllFloatingEvents();
	vector<Event> getshowDay(int day, int month, int year, vector<Event> currentContent);
	vector<Event> getshowMonth(int month, int year, vector<Event> currentContent);
	vector<Event> getshowWeek(int day, int month, int year, vector<Event> currentContent);

	//vector<Event> searchAllComponentsOfEvent(string informationToSearch); //search currentcontent
};


#endif