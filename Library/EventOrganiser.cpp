#include "EventOrganiser.h"

const int EventOrganiser::TOTAL_MONTHS_IN_A_YEAR = 12;

//Marker info
const int EventOrganiser::UNIQUE_ID = -123;
const string EventOrganiser::MARKER_CODE = "-MSmsgjyw-";

//For logging
const string EventOrganiser::SHOW_ALL_NORMAL_EVENTS = "showAllNormalEvent";
const string EventOrganiser::SHOW_ALL_FLOATING_EVENTS = "showAllFloatingEvent";
const string EventOrganiser::SHOW_EVENTS = "showEvents";
const string EventOrganiser::SHOW_DATES_FROM_NORMAL_CONTENT = "showDatesFromNormalContent";
const string EventOrganiser::DATE_RANGE = "dateRange";
const string EventOrganiser::SHOW_DATE_RANGE = "showDateRange";

EventOrganiser::EventOrganiser(void)
{
}

EventOrganiser::~EventOrganiser(void)
{
}

//returns all events with marker
vector<Event> EventOrganiser::showAllNormalEvent(){
	vector<Event> tempContent = EventStorage::storage().getNormalContent();
	tempContent = showEvents(tempContent);
	logger.logStorageIntData(SHOW_ALL_NORMAL_EVENTS,tempContent.size());
	return tempContent;
}

//returns all floating events
vector<Event> EventOrganiser::showAllFloatingEvent(){
	logger.logStoragePosition(SHOW_ALL_FLOATING_EVENTS);
	return EventStorage::storage().getFloatingContent();
}

//show event Vector items, sorted and marked
vector<Event> EventOrganiser::showEvents(vector<Event> eventsToShow){
	logger.logStorageIntData(SHOW_EVENTS,eventsToShow.size());
	
	Event eventWithStartEndTime = dateRange(eventsToShow);
	eventsToShow = showDateRange(eventWithStartEndTime,eventsToShow);
	return eventsToShow;
}

//show events from current content within range, sorted and marked
vector<Event> EventOrganiser::showDatesFromNormalContent(Event eventWithStartEndTimes){
	logger.logStoragePosition(SHOW_DATES_FROM_NORMAL_CONTENT);

	vector<Event> tempContent = EventStorage::storage().getNormalContent();
	tempContent = showDateRange(eventWithStartEndTimes, tempContent);
	return tempContent;
}

//Finds the earliest and latest day among all events in normalContent
Event EventOrganiser::dateRange(vector<Event> eventsToFilter){
	logger.logStoragePosition(DATE_RANGE);
	struct tm earliestDate, latestDate;
	Event returnEvent;

	if(!eventsToFilter.empty()){
		eventsToFilter = sortEventVectorByDate(eventsToFilter);
		earliestDate = eventsToFilter[0].getStartDate();
		eventsToFilter = sortEventVectorByEndDate(eventsToFilter);
		int lastIndex = eventsToFilter.size()-1;
		latestDate = eventsToFilter[lastIndex].getEndDate();
	
		returnEvent.setStartDate(earliestDate.tm_mday,earliestDate.tm_mon,earliestDate.tm_year);	
		returnEvent.setEndDate(latestDate.tm_mday,latestDate.tm_mon,latestDate.tm_year);
	}

	return returnEvent;
}

//shows date range for vector items, sorted and marked
vector<Event> EventOrganiser::showDateRange(Event eventWithStartEndTimes, vector<Event> eventsToFilter){
	logger.logStoragePosition(SHOW_DATE_RANGE);
	vector<Event> returnVector;
	vector<struct tm> wantedEventDates;
	vector<struct tm> exisitngEventDates;
	bool isPushed = false;
	vector<Event> sortResults;
	time_t t = time(0);
	struct tm* temp = localtime(&t);
	Event tempEvent;

	Event marker;
	marker.setName(MARKER_CODE);
	marker.setID(UNIQUE_ID);
	marker.setIsFloating(false);

	sortResults = sortEventVectorByDate(eventsToFilter);
	eventsToFilter = sortResults;

	wantedEventDates = eventDateToVector(eventWithStartEndTimes);

	for(int i=0;i<wantedEventDates.size();i++){
		for(int j=0; j<eventsToFilter.size();j++){
			exisitngEventDates = eventDateToVector(eventsToFilter[j]);
			for(int k=0; k<exisitngEventDates.size();k++){
				if((wantedEventDates[i].tm_year == exisitngEventDates[k].tm_year) && (wantedEventDates[i].tm_mon == exisitngEventDates[k].tm_mon) && (wantedEventDates[i].tm_mday == exisitngEventDates[k].tm_mday)){
					//check all day.. set starttime and endtime
					if(eventsToFilter[j].getStartDate().tm_mday != eventsToFilter[j].getEndDate().tm_mday){ //if multi day event
						tempEvent = eventsToFilter[j];
						if(wantedEventDates[i].tm_mday == tempEvent.getStartDate().tm_mday){ //start of multiday
							tempEvent.setEndTime(23,59);
						} else if(wantedEventDates[i].tm_mday == tempEvent.getEndDate().tm_mday){ //end of multiday
							tempEvent.setStartTime(0,0);
						} else{ //between multiday
							tempEvent.setStartTime(0,0);
							tempEvent.setEndTime(23,59);
						}
						returnVector.push_back(tempEvent);
						isPushed = true;
					} else{
						returnVector.push_back(eventsToFilter[j]);
						isPushed = true;
					}
				}
			}
		}
		if(isPushed){
			temp->tm_mday = wantedEventDates[i].tm_mday;
			temp->tm_mon = wantedEventDates[i].tm_mon;
			temp->tm_year = wantedEventDates[i].tm_year;
			mktime(temp);
			marker.setStartDate(temp->tm_mday, temp->tm_mon, temp->tm_year);
			marker.setStartWeekday(temp->tm_wday);		
			returnVector.push_back(marker);
			isPushed = false;  //reset bool
		}
	}
	returnVector = sortMarker(returnVector);
	logger.logStorageIntData("leaving showDateRange",returnVector.size());
	return returnVector;
}

//returns a vector of days for wanted date range.
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

//brings marker up to before events
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

//Sorting methods
vector<Event> EventOrganiser::sortEventVectorByDate(vector<Event> eventsToSort){ //sort events be endDate, earliest to latest
	Event temp;
	
	if(eventsToSort.size()<=1){
		return eventsToSort;
	} else{
		for(auto i=0;i<(eventsToSort.size()-1);i++){
			for(int j=i+1;j<eventsToSort.size();j++){
				int difference = findTimeDiff(eventsToSort[j].getStartDate(),eventsToSort[i].getStartDate());
				if(difference >= 0 ){ 
					temp = eventsToSort[i];
					eventsToSort[i] = eventsToSort[j];
					eventsToSort[j] = temp;
				}
			}
		}
	}
	return eventsToSort;
}

vector<Event> EventOrganiser::sortEventVectorByEndDate(vector<Event> eventsToSort){ //sort events be endDate, earliest to latest
	Event temp;
	
	if(eventsToSort.size()<=1){
		return eventsToSort;
	} else{
		for(auto i=0;i<(eventsToSort.size()-1);i++){
			for(int j=i+1;j<eventsToSort.size();j++){
				int difference = findTimeDiff(eventsToSort[j].getEndDate(),eventsToSort[i].getEndDate());
				if(difference >= 0 ){ 
					temp = eventsToSort[i];
					eventsToSort[i] = eventsToSort[j];
					eventsToSort[j] = temp;
				}
			}
		}
	}
	return eventsToSort;
}

int EventOrganiser::findTimeDiff(tm startDay, tm endDay){
	time_t start = mktime(&startDay);
	time_t end = mktime(&endDay);

	int difference = difftime(end,start);
	return difference;
}