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
	static const string SHOW_ALL_NORMAL_EVENTS;
	static const string SHOW_ALL_FLOATING_EVENTS;
	static const string SHOW_EVENTS;
	static const string SHOW_DATES_FROM_NORMAL_CONTENT;
	static const string DATE_RANGE;
	static const string SHOW_DATE_RANGE;

	EventLog logger;

public:
	EventOrganiser(void);
	~EventOrganiser(void);
	
	//Show All methods
	vector<Event> showAllNormalEvent();

	//Show floating method
	vector<Event> showAllFloatingEvent();
	
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
};

#endif