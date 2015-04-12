//@author A0113860M

#include "EventOrganiser.h"

const int EventOrganiser::TOTAL_MONTHS_IN_A_YEAR = 12;

//Marker info
const int EventOrganiser::UNIQUE_ID = -123;
const string EventOrganiser::MARKER_CODE = "-MSmsgjyw-";

EventOrganiser::EventOrganiser(void)
{
}

EventOrganiser::~EventOrganiser(void)
{
}

//show all Methods
vector<Event> EventOrganiser::showAllNormalCurrent(){
	vector<Event> tempContent =	allNormalCurrent();
	tempContent = showEvents(tempContent);
	logger.log(EventLog::ORGANISER + EventLog::SHOW_ALL_NORMAL_CURRENT, tempContent.size());
	return tempContent;
}

vector<Event> EventOrganiser::showAllNormalCompleted(){
	vector<Event> tempContent = allNormalCompleted();
	tempContent = showEvents(tempContent);
	logger.log(EventLog::ORGANISER + EventLog::SHOW_ALL_NORMAL_COMPLETED, tempContent.size());
	return tempContent;
}

vector<Event> EventOrganiser::showAllFloatingCurrent(){
	logger.log(EventLog::ORGANISER + EventLog::SHOW_ALL_FLOATING_CURRENT);
	return allFloatingCurrent();
}

vector<Event> EventOrganiser::showAllFloatingCompleted(){
	logger.log(EventLog::ORGANISER + EventLog::SHOW_ALL_FLOATING_COMPLETED);
	return allFloatingCompleted();
}

//==================================================================================================
//shows the range of given eventVector, sorted and marked
vector<Event> EventOrganiser::showEvents(vector<Event> eventsToShow){
	logger.log(EventLog::ORGANISER + EventLog::SHOW_EVENTS, eventsToShow.size());
	
	Event eventWithStartEndTime = dateRange(eventsToShow);
	eventsToShow = showDateRange(eventWithStartEndTime,eventsToShow);

	return eventsToShow;
}

//shows the range from currentContent of given event, sorted and marked
vector<Event> EventOrganiser::showDatesFromNormalContent(Event eventWithStartEndTimes){
	logger.log(EventLog::ORGANISER + EventLog::SHOW_DATES_FROM_NORMAL_CONTENT);

	vector<Event> tempContent = allNormalCurrent();
	tempContent = showDateRange(eventWithStartEndTimes, tempContent);

	return tempContent;
}

//==================================================================================================
//Filters  uncompleted / completed Events
//get from internal storage vectors and returns filtered events
vector<Event> EventOrganiser::allNormalCurrent(){
	vector<Event> tempContent = EventStorage::storage().getNormalContent();
	vector<Event> results;

	for(auto i=0;i<tempContent.size();i++){
		if(tempContent[i].getIsCompleted() == false){
			results.push_back(tempContent[i]);
		}
	}

	logger.log(EventLog::ORGANISER + EventLog::SHOW_ALL_NORMAL_CURRENT, results.size());
	return results;
}

vector<Event> EventOrganiser::allFloatingCurrent(){
	vector<Event> tempContent = EventStorage::storage().getFloatingContent();
	vector<Event> results;

	for(auto i=0;i<tempContent.size();i++){
		if(tempContent[i].getIsCompleted() == false){
			results.push_back(tempContent[i]);
		}
	}

	results = sortFloatingByID(results);
	logger.log(EventLog::ORGANISER + EventLog::SHOW_ALL_FLOATING_CURRENT, results.size());
	return results;
}

vector<Event> EventOrganiser::allNormalCompleted(){
	vector<Event> tempContent = EventStorage::storage().getNormalContent();
	vector<Event> results;

	for(auto i=0;i<tempContent.size();i++){
		if(tempContent[i].getIsCompleted() == true){
			results.push_back(tempContent[i]);
		}
	}
	
	logger.log(EventLog::ORGANISER + EventLog::SHOW_ALL_NORMAL_COMPLETED, results.size());
	return results;
}

vector<Event> EventOrganiser::allFloatingCompleted(){
	vector<Event> tempContent = EventStorage::storage().getFloatingContent();
	vector<Event> results;

	for(auto i=0;i<tempContent.size();i++){
		if(tempContent[i].getIsCompleted() == true){
			results.push_back(tempContent[i]);
		}
	}

	results = sortFloatingByID(results);
	logger.log(EventLog::ORGANISER + EventLog::SHOW_ALL_FLOATING_COMPLETED, results.size());
	return results;
}

//Setters
void EventOrganiser::saveNormal(vector<Event> normalCurrent){
	vector<Event> tempNormalCompleted = allNormalCompleted();
	normalCurrent.insert( normalCurrent.end(), tempNormalCompleted.begin(), tempNormalCompleted.end() );
	EventStorage::storage().setNormalContent(normalCurrent);
}

void EventOrganiser::saveFloating(vector<Event> floatingCurrent){
	vector<Event> tempFloatingCompleted = allFloatingCompleted();
	floatingCurrent.insert( floatingCurrent.end(), tempFloatingCompleted.begin(), tempFloatingCompleted.end() );
	EventStorage::storage().setFloatingContent(floatingCurrent);
}

void EventOrganiser::saveNormalCompleted(vector<Event> normalCompleted){
	vector<Event> tempNormalCurrent = allNormalCurrent();
	tempNormalCurrent.insert( tempNormalCurrent.end(), normalCompleted.begin(), normalCompleted.end() );
	EventStorage::storage().setNormalContent(tempNormalCurrent);
}

void EventOrganiser::saveFloatingCompleted(vector<Event> floatingCompleted){
	vector<Event> tempFloatingCurrent = allFloatingCurrent();
	tempFloatingCurrent.insert( tempFloatingCurrent.end(), floatingCompleted.begin(), floatingCompleted.end() );
	EventStorage::storage().setFloatingContent(tempFloatingCurrent);
}

//==================================================================================================
//Show dates support methods
//shows date range for vector items, sorted and marked
vector<Event> EventOrganiser::showDateRange(Event eventWithStartEndTimes, vector<Event> eventsToFilter){
	logger.log(EventLog::ORGANISER + EventLog::SHOW_DATE_RANGE);

	vector<Event> returnVector, sortResults;
	vector<struct tm> wantedEventDates;
	vector<struct tm> exisitngEventDates;
	bool isPushed = false;
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
					//check ALLDAY.. set starttime and endtime
					if(eventsToFilter[j].getStartDate().tm_mday != eventsToFilter[j].getEndDate().tm_mday){ //if multi day event
						tempEvent = eventsToFilter[j];
						if(wantedEventDates[i].tm_mday == tempEvent.getStartDate().tm_mday){ //start of multiday
							tempEvent.setEndTime(23,59);
						} else if(wantedEventDates[i].tm_mday == tempEvent.getEndDate().tm_mday){ //end of multiday
							tempEvent.setStartTime(0,0);
						} else{ //days between multiday
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
	logger.log(EventLog::ORGANISER + EventLog::SHOW_DATE_RANGE + EventLog::EXIT, returnVector.size());
	return returnVector;
}

//returns a vector of days for the wanted range of dates.
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
				} 
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

//shift marker up to before events
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

//Finds the earliest and latest day among all events in a vector of Events
Event EventOrganiser::dateRange(vector<Event> eventsToFilter){
	logger.log(EventLog::ORGANISER + EventLog::DATE_RANGE);
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

//Sorting methods
//sort events by start date, earliest to latest
vector<Event> EventOrganiser::sortEventVectorByDate(vector<Event> eventsToSort){ 
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

 //sort events by end date, earliest to latest
vector<Event> EventOrganiser::sortEventVectorByEndDate(vector<Event> eventsToSort){
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

//time difference in seconds
int EventOrganiser::findTimeDiff(tm startDay, tm endDay){
	time_t start = mktime(&startDay);
	time_t end = mktime(&endDay);

	int difference = difftime(end,start);
	return difference;
}

//sorts floating with ID in ascending order 
vector<Event> EventOrganiser::sortFloatingByID(vector<Event> floating){
	Event temp;

	if(floating.size()<=1){
		return floating;
	} else{
		for(auto i=0;i<(floating.size()-1);i++){
			for(int j=i+1;j<floating.size();j++){
				if(floating[i].getID() > floating[j].getID()){ 
					temp = floating[i];
					floating[i] = floating[j];
					floating[j] = temp;
				}
			}
		}
	}
	return floating;
}

