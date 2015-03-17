#include "EventOrganiser.h"


EventOrganiser::EventOrganiser(void)
{
}

EventOrganiser::~EventOrganiser(void)
{
}

vector<Event> EventOrganiser::showAllNormalEvent(vector<Event> currentContent){
	vector<Event> sortResults;
	sortResults = sortEventVectorByDate(currentContent);
	return sortResults; 
}
vector<Event> EventOrganiser::showAllFloatingEvent(vector<Event> currentFloatingContent){
	return currentFloatingContent;
}

vector<Event> EventOrganiser::showDay(int dayToShow, int monthToShow, int yearToShow, vector<Event> currentContent){
	
	vector<Event> showDayResults;
	vector<Event> sortResults;

	sortResults = sortEventVectorByDate(currentContent);

	for(auto i=0;i<sortResults.size();i++){
		if((sortResults[i].getStartDate().tm_year == yearToShow) && (sortResults[i].getStartDate().tm_mon == monthToShow) && (sortResults[i].getStartDate().tm_mday == dayToShow)){
			showDayResults.push_back(sortResults[i]);
		}
	}
	return showDayResults;
}

vector<Event> EventOrganiser::showMonth(int monthToShow, int yearToShow, vector<Event> eventsToFilter){

	vector<Event> showMonthResults;
	vector<Event> sortResults;

	sortResults = sortEventVectorByDate(eventsToFilter);

	for(auto i=0;i<sortResults.size();i++){
		if((sortResults[i].getStartDate().tm_year == yearToShow) && (sortResults[i].getStartDate().tm_mon == monthToShow)){
			showMonthResults.push_back(sortResults[i]);
		}
	}
	return showMonthResults;
}

vector<Event> EventOrganiser::showWeek(int dayToShow, int monthToShow, int yearToShow, vector<Event> eventsToFilter){ 

	vector<Event> showWeekResults;
	vector<Event> sortResults;

	sortResults = sortEventVectorByDate(eventsToFilter);
	
	for(auto j=0;j<7;j++){
		for(auto i=0;i<sortResults.size();i++){
			if((sortResults[i].getStartDate().tm_year == yearToShow) && (sortResults[i].getStartDate().tm_mon == monthToShow) && ((sortResults[i].getStartDate().tm_mday) == (dayToShow + j))){
				showWeekResults.push_back(sortResults[i]);
			}
		}
	}
	return showWeekResults;
}

vector<Event> EventOrganiser::sortEventVectorByDate(vector<Event> eventVectorToSort){

	Event tempEvent;
	if(eventVectorToSort.size()<=1){
		return eventVectorToSort;
	}
	else{
		for(auto i=0;i<(eventVectorToSort.size()-1);i++){
			for(int j=i+1;j<eventVectorToSort.size();j++){
				if(isLatterTimeSmaller(eventVectorToSort[i],eventVectorToSort[j])){
					tempEvent = eventVectorToSort[j];
					eventVectorToSort[j] = eventVectorToSort[i];
					eventVectorToSort[i] = tempEvent;
				}
			}
		}
	}
	return eventVectorToSort;
}
	
bool EventOrganiser::isLatterTimeSmaller(Event eventTime1,Event eventTime2) //returns true is latter time is smaller
{	
	bool isEarlier = false;

	if(eventTime1.getStartDate().tm_year != eventTime2.getStartDate().tm_year){
		return isLatterYearSmaller(eventTime1,eventTime2);
	}
	else if(eventTime1.getStartDate().tm_mon != eventTime2.getStartDate().tm_mon){
		return isLatterMonthSmaller(eventTime1,eventTime2);
	}
	else if(eventTime1.getStartDate().tm_mday != eventTime2.getStartDate().tm_mday){
		return isLatterDaySmaller(eventTime1,eventTime2);
	}
	else if(eventTime1.getStartDate().tm_hour != eventTime2.getStartDate().tm_hour){
		return isLatterHourSmaller(eventTime1,eventTime2);
	}
	else if(eventTime1.getStartDate().tm_min != eventTime2.getStartDate().tm_min){
		return isLatterMinSmaller(eventTime1,eventTime2);
	}
	else		//Start time is equal
		return isEarlier;
}
bool EventOrganiser::isLatterHourSmaller(Event eventTime1, Event eventTime2) //returns true is eT2 is earlier
{
	int startHour, endHour;
	bool isHourBigger = false;

	startHour = eventTime1.getStartDate().tm_hour;
	endHour = eventTime2.getStartDate().tm_hour;
	if(startHour > endHour)
		isHourBigger = true;

	return isHourBigger;
}

bool EventOrganiser::isLatterYearSmaller(Event eventTime1, Event eventTime2) //returns true is eT2 is earlier
{
	int startYear, endYear;
	bool isYearBigger = false;

	startYear = eventTime1.getStartDate().tm_year;
	endYear = eventTime2.getStartDate().tm_year;
	if(startYear > endYear){
		isYearBigger = true;
	}
	return isYearBigger;
}

bool EventOrganiser::isLatterMonthSmaller(Event eventTime1, Event eventTime2)  //returns true is eT2 is earlier
{
	int startMonth, endMonth;
	bool isMonthBigger = false;

	startMonth = eventTime1.getStartDate().tm_mon;
	endMonth = eventTime2.getStartDate().tm_mon;
	if(startMonth > endMonth)
		isMonthBigger = true;

	return isMonthBigger;
}

bool EventOrganiser::isLatterDaySmaller(Event eventTime1, Event eventTime2)  //returns true is eT2 is earlier
{
	int startDay, endDay;
	bool isDayBigger = false;

	startDay = eventTime1.getStartDate().tm_mday;
	endDay = eventTime2.getStartDate().tm_mday;
	if(startDay > endDay)
		isDayBigger = true;

	return isDayBigger;
}

bool EventOrganiser::isLatterMinSmaller(Event eventTime1, Event eventTime2) //returns true is eT2 is earlier
{
	int startMin, endMin;
	bool isMinBigger = false;

	startMin = eventTime1.getStartDate().tm_min;
	endMin = eventTime2.getStartDate().tm_min;
	if(startMin > endMin)
		isMinBigger = true;

	return isMinBigger;
}
