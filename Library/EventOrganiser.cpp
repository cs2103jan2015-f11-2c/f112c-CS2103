#include "EventOrganiser.h"

const int EventOrganiser::TOTAL_MONTHS_IN_A_YEAR = 12;
const string EventOrganiser::MARKER_CODE = "-MSmsgjyw-";

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
/*
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
*/
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

vector<struct tm> EventOrganiser::eventDateToVector(Event showEventDates){
	
	struct tm tempStartDate = showEventDates.getStartDate();
	int startday = tempStartDate.tm_mday;
	int startmonth = tempStartDate.tm_mon;
	int startyear = tempStartDate.tm_year;
	
	struct tm tempEndDate = showEventDates.getEndDate();
	int endday = tempEndDate.tm_mday;
	int endmonth = tempEndDate.tm_mon;
	int endyear = tempEndDate.tm_year;

	vector<struct tm> datesToShow;
	struct tm tempTM;
	Conversion convertor;

	int i, j, k;
	for(k = startyear; k <= endyear; k++){
		tempTM.tm_year = k;
		if(k == endyear){
			for(j = startmonth; j <= endmonth; j++){
				tempTM.tm_mon = j;
				if(j < endmonth){
					for(i = startday; i <= convertor.determineLastDayOfMth(j,k); i++){
						tempTM.tm_mday = i;
						datesToShow.push_back(tempTM);
					}
					//reset startday count to start of month
					startday = 1;
				} else if(j == endmonth){
					for(i = startday; i <= endday; i++){
						tempTM.tm_mday = i;
						datesToShow.push_back(tempTM);
					}
				} //else {
				//	throw
				//}
			}
		} else if(k < endyear){
			for(j = startmonth; j <= TOTAL_MONTHS_IN_A_YEAR; j++){
				tempTM.tm_mon = j;
				for(i = startday; i <= convertor.determineLastDayOfMth(j,k); i++){
					tempTM.tm_mday = i;
					datesToShow.push_back(tempTM);
				}
				//reset startday count to start of month
				startday = 1;
			}
			//reset startmonth to start of year
			startmonth = 0;
		}
	}

	return datesToShow;
}

vector<Event> EventOrganiser::showDateRange(Event eventWithStartEndTimes, vector<Event> eventsToFilter){

	vector<Event> returnVector;
	vector<struct tm> wantedEventDates;
	vector<struct tm> exisitngEventDates;
	bool isPushed = false;
	Event marker;
	marker.setName(MARKER_CODE);
	vector<Event> sortResults;

	sortResults = sortEventVectorByDate(eventsToFilter);
	eventsToFilter = sortResults;

	wantedEventDates = eventDateToVector(eventWithStartEndTimes);
	for(int i=0;i<wantedEventDates.size();i++){
		for(int j=0; j<eventsToFilter.size();j++){
			exisitngEventDates = eventDateToVector(eventsToFilter[j]);
			for(int k=0; k<exisitngEventDates.size();k++){
				if((wantedEventDates[i].tm_year == exisitngEventDates[k].tm_year) && (wantedEventDates[i].tm_mon == exisitngEventDates[k].tm_mon) && (wantedEventDates[i].tm_mday == exisitngEventDates[k].tm_mday)){
					returnVector.push_back(eventsToFilter[j]);
					isPushed = true;
				}
			}
		}
		if(isPushed){
			marker.setStartDate(wantedEventDates[i].tm_mday, wantedEventDates[i].tm_mon, wantedEventDates[i].tm_year);
			returnVector.push_back(marker);
			isPushed = false;  //reset bool
		}
	}
	returnVector = sortMarker(returnVector);
	return returnVector;
}

vector<Event> EventOrganiser::sortMarker(vector<Event> showResult){
	vector<Event> returnVector;
	vector<Event> tempVector;

	for(int i=0;i<showResult.size();i++){
		if(showResult[i].getName() != MARKER_CODE){
			tempVector.push_back(showResult[i]);
		} else if(showResult[i].getName() == MARKER_CODE){
			returnVector.push_back(showResult[i]);
			for(int j=0;j<tempVector.size();j++){
				returnVector.push_back(tempVector[j]);
			}
			tempVector.clear();
		}
	}

	return returnVector;	
}