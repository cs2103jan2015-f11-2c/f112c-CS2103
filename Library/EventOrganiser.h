#pragma once

#ifndef EVENTORGANISER_H
#define EVENTORGANISER_H

#include "EventStorage.h"

class EventOrganiser{
private:
	static const int TOTAL_MONTHS_IN_A_YEAR;
	static const int UNIQUE_ID;
	static const string MARKER_CODE;
	
	EventLog logger;

public:
	EventOrganiser(void);
	~EventOrganiser(void);
	
	//Show normal methods
	vector<Event> showAllNormalCurrent();
	vector<Event> showAllNormalCompleted();

	//Show floating method
	vector<Event> showAllFloatingCurrent();
	vector<Event> showAllFloatingCompleted();
	
	//Show method
	vector<Event> showEvents(vector<Event> eventsToShow);
	vector<Event> showDatesFromNormalContent(Event eventWithStartEndTimes);

	//Show support methods
	Event dateRange(vector<Event> eventsToFilter);
	vector<Event> showDateRange(Event eventWithStartEndTimes, vector<Event> eventsToFilter);
	vector<struct tm> eventDateToVector(Event showEventDates);
	vector<Event> sortMarker(vector<Event> showResult);
	
	//Sort methods
	vector<Event> sortEventVectorByDate(vector<Event> eventsToSort);
	vector<Event> sortEventVectorByEndDate(vector<Event> eventsToSort);
	int findTimeDiff(tm startDay, tm endDay);

	//filter complete / uncompleted 
	vector<Event> sortFloatingByID(vector<Event> floating);
	vector<Event> allNormalCurrent();
	vector<Event> allFloatingCurrent();
	vector<Event> allNormalCompleted();
	vector<Event> allFloatingCompleted();

	//appends completed task and set
	void saveNormal(vector<Event> normalCurrent);//, vector<Event> normalCompleted);
	void saveFloating(vector<Event> floatingCurrent);//, vector<Event> floatingCompleted);	
	void saveNormalCompleted(vector<Event> normalCompleted);
	void saveFloatingCompleted(vector<Event> floatingCompleted);
};

#endif