#pragma once

#ifndef EVENTORGANISER_H
#define EVENTORGANISER_H

#include "EventStorage.h"

class EventOrganiser{
public:
	EventOrganiser(void);
	~EventOrganiser(void);
	
	//Show normal API
	vector<Event> showAllNormalCurrent();
	vector<Event> showAllNormalCompleted();

	//Show floating API
	vector<Event> showAllFloatingCurrent();
	vector<Event> showAllFloatingCompleted();
	
	//Show dates API
	vector<Event> showEvents(vector<Event> eventsToShow);
	vector<Event> showDatesFromNormalContent(Event eventWithStartEndTimes);

	//getters -- filters complete / uncompleted 
	vector<Event> allNormalCurrent();
	vector<Event> allFloatingCurrent();
	vector<Event> allNormalCompleted();
	vector<Event> allFloatingCompleted();

	//setters -- merges complete / uncompleted
	void saveNormal(vector<Event> normalCurrent);
	void saveFloating(vector<Event> floatingCurrent);	
	void saveNormalCompleted(vector<Event> normalCompleted);
	void saveFloatingCompleted(vector<Event> floatingCompleted);

private:
	static const int TOTAL_MONTHS_IN_A_YEAR;
	static const int UNIQUE_ID;
	static const string MARKER_CODE;
	
	EventLog logger;
	Conversion convertor;

	//Show support methods
	vector<Event> showDateRange(Event eventWithStartEndTimes, vector<Event> eventsToFilter);
	vector<struct tm> eventDateToVector(Event showEventDates);
	vector<Event> sortMarker(vector<Event> showResult);
	Event dateRange(vector<Event> eventsToFilter);

	//Sorting methods
	vector<Event> sortEventVectorByDate(vector<Event> eventsToSort);
	vector<Event> sortEventVectorByEndDate(vector<Event> eventsToSort);
	int findTimeDiff(tm startDay, tm endDay);
	vector<Event> sortFloatingByID(vector<Event> floating);

};

#endif