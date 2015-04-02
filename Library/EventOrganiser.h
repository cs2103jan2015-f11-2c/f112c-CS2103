#pragma once

#ifndef EVENTORGANISER_H
#define EVENTORGANISER_H

#include "EventStorage.h"

class EventOrganiser{
private:
	static const int TOTAL_MONTHS_IN_A_YEAR;
	static const int UNIQUE_ID;
	static const string MARKER_CODE;
	
	//For logging
	static const string SHOW_ALL_NORMAL_CURRENT;
	static const string SHOW_ALL_NORMAL_COMPLETED;
	static const string SHOW_ALL_FLOATING_CURRENT;
	static const string SHOW_ALL_FLOATING_COMPLETED;
	static const string SHOW_EVENTS;
	static const string SHOW_DATES_FROM_NORMAL_CONTENT;
	static const string DATE_RANGE;
	static const string SHOW_DATE_RANGE;

	EventLog logger;

public:
	EventOrganiser(void);
	~EventOrganiser(void);
	
	//Show All methods
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
	vector<Event> allNormalCurrent();
	vector<Event> allFloatingCurrent();
	vector<Event> allNormalCompleted();
	vector<Event> allFloatingCompleted();

	//appends completed task and set
	void saveNormal(vector<Event> normalCurrent);//, vector<Event> normalCompleted);
	void saveFloating(vector<Event> floatingCurrent);//, vector<Event> floatingCompleted);
};

#endif