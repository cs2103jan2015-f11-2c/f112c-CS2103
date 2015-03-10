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

class EventStorage{
private:

	//These are messages to give the user feedback on what the program is doing.
	static const string ADDED_FLOATING_EVENT;
	static const string ADDED_NORMAL_EVENT;

	//These are results to improve readability
	static const int EventStorage::INVALID;

	//These are vectors that store information
	vector<Event> currentContent;
	vector<Event> currentFloatingContent;
	vector<EventArchive> archiveContent;
	vector<Event> undoVector;
	vector<Event> redoVector;
	EventArchive archiveObject; 
	static const std::string currentFile;

public:
	//Constructor, Destructor
	EventStorage(void); //will read the currentFile into the currentContent vector 
	~EventStorage(void);

	//Methods
	void writeToCurrentFile();
	void readToCurrentContent();
	vector<Event> addEvent(Event newEvent);

	//delete mths
	vector<Event> deleteEvent(int eventID, string eventName);

	string tmToString(Event convertEvent);
	string boolToString(bool isFloatingBool);

	vector<Event> showAllNormalEvent();
	vector<Event> showAllFloatingEvent();
	vector<Event> sortEventVectorByDate(vector<Event> eventVectorToSort);
	vector<Event> showDay(int dayToShow, int monthToShow, int yearToShow);
	bool isLatterTimeSmaller(const Event eventTime1,const Event EventTime2);
	bool isLatterYearSmaller(Event eventTime1, Event EventTime2);
	bool isLatterMonthSmaller(Event eventTime1, Event EventTime2);
	bool isLatterDaySmaller(Event eventTime1, Event EventTime2);
	bool isLatterHourSmaller(Event eventTime1, Event EventTime2);
	bool isLatterMinSmaller(Event eventTime1, Event EventTime2);
	
	vector<Event> editEvent(int eventID, string eventName, Event editedEvent);
	//vector<Event> searchAllComponentsOfEvent(string informationToSearch); //search currentcontent
	
};


#endif