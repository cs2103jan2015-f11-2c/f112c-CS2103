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


class EventStorage{
private:
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
	bool deleteEvent(int userIndex, vector<Event> userDisplayedVector);
	int searchWithEventID(int eventID, vector<Event> eventVectorToSearch);
	Event userInputIndexToEvent(int userIndex, vector<Event> userDisplayedVector);

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
	
	//void EditEvent(int ID, Event newEvent);
	//vector<Event> searchAllComponentsOfEvent(string informationToSearch); //search currentcontent
	
};


#endif