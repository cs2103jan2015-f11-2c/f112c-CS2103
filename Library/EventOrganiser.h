#pragma once

#ifndef EVENTORGANISER_H
#define EVENTORGANISER_H

#include "Event.h"

class EventOrganiser{
private:
	//vector<Event> organisedEventToReturn;

public:
	EventOrganiser(void);
	~EventOrganiser(void);
	
	vector<Event> showAllNormalEvent(vector<Event> currentContent);
	vector<Event> showAllFloatingEvent(vector<Event> currentFloatingContent);
	vector<Event> sortEventVectorByDate(vector<Event> eventVectorToSort);
	vector<Event> showDay(int dayToShow, int monthToShow, int yearToShow, vector<Event> currentContent);
	bool isLatterTimeSmaller(const Event eventTime1,const Event EventTime2);
	bool isLatterYearSmaller(Event eventTime1, Event EventTime2);
	bool isLatterMonthSmaller(Event eventTime1, Event EventTime2);
	bool isLatterDaySmaller(Event eventTime1, Event EventTime2);
	bool isLatterHourSmaller(Event eventTime1, Event EventTime2);
	bool isLatterMinSmaller(Event eventTime1, Event EventTime2);

};

#endif