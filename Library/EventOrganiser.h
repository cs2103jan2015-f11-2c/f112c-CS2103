#pragma once

#ifndef EVENTORGANISER_H
#define EVENTORGANISER_H

#include "Event.h"
#include "Conversion.h"
#include "EventLog.h"

class EventOrganiser{
private:
	//vector<Event> organisedEventToReturn;
	static const int TOTAL_MONTHS_IN_A_YEAR;
	static const int UNIQUE_ID;
	static const string MARKER_CODE;
	EventLog logger;

public:
	EventOrganiser(void);
	~EventOrganiser(void);
	
	vector<Event> showAllNormalEvent(vector<Event> currentContent);
	vector<Event> showAllFloatingEvent(vector<Event> currentFloatingContent);
	vector<Event> showDay(int dayToShow, int monthToShow, int yearToShow, vector<Event> currentContent);
	//vector<Event> showWeek(int dayToShow, int monthToShow, int yearToShow, vector<Event> eventsToFilter);
	//vector<Event> showMonth(int monthToShow, int yearToShow, vector<Event> eventsToFilter);

	vector<Event> sortEventVectorByDate(vector<Event> eventVectorToSort);
	bool isLatterTimeSmaller(const Event eventTime1,const Event EventTime2);
	bool isLatterYearSmaller(Event eventTime1, Event EventTime2);
	bool isLatterMonthSmaller(Event eventTime1, Event EventTime2);
	bool isLatterDaySmaller(Event eventTime1, Event EventTime2);
	bool isLatterHourSmaller(Event eventTime1, Event EventTime2);
	bool isLatterMinSmaller(Event eventTime1, Event EventTime2);

	vector<struct tm> eventDateToVector(Event showEventDates);
	vector<Event> showDateRange(Event eventWithStartEndTimes, vector<Event> eventsToFilter);
	vector<Event> sortMarker(vector<Event> showResult);
	vector<Event> sortEventVectorByEndDate(vector<Event> eventsToSort);
	Event dateRange(vector<Event> eventsToFilter);
	int findTimeDiff(tm startDay, tm endDay);

};

#endif