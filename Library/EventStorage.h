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
//#include parser.h

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
	void deleteEvent(int userIndex); 
	void EditEvent(int ID, Event newEvent);
	vector<Event> searchAllComponentsOfEvent(string informationToSearch); //search currentcontent
	int searchCurrentContentWithEventID(int eventID);
	void searchEventname();
	string tmToString(Event convertEvent);
	string boolToString(bool isFloatingBool);

	Event userInputIndexToEvent(int userIndex);

	//void createFloatingEvent();
	//void createEvent();
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

};


#endif