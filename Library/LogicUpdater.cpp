#include "LogicUpdater.h"


const int LogicUpdater::GARBAGE_INT = -12345;
const int LogicUpdater::INVALID_NUMBER = -1;
const string LogicUpdater::EMPTY_STRING = "";

const string LogicUpdater::NO_EVENTS_MESSAGE = "Currently no task";
const string LogicUpdater::ADDED_MESSAGE = " added";
const string LogicUpdater::EDITED_MESSAGE = " edited";
const string LogicUpdater::DELETED_MESSAGE = " deleted";
const string LogicUpdater::SHOW_MESSAGE = "showing ";
const string LogicUpdater::EVENT_NOT_FOUND_MESSAGE = " not found";
const string LogicUpdater::PARTIAL_EVENT_FOUND_MESSAGE = " not found, showing partial matches";
const string LogicUpdater::CHOOSE_EVENT_MESSAGE = "More than 1 result found, please select one from above via index.";
const string LogicUpdater::NEW_DAY_MESSAGE = "-MSmsgjyw-";
const string LogicUpdater::UNDO_MESSAGE = "undo";
const string LogicUpdater::REDO_MESSAGE = "redo";
const string LogicUpdater::COMPLETED_MESSEAGE = "completed";


const string LogicUpdater::WORD_TODAY = "Today";
const string LogicUpdater::WORD_TOMORROW = "Tomorrow";
const string LogicUpdater::WORD_MONTH = "Month";
const string LogicUpdater::WORD_WEEK = "Week";


const string LogicUpdater::WORD_ALLDAY = "All Day";

const int LogicUpdater::SHIFT_BY_ONE = 1;
const int LogicUpdater::MAX_LENGTH_EVENT_NAME = 42;

//constructor
LogicUpdater::LogicUpdater() {
	normalEvents.clear();
	floatingEvents.clear();
	feedbackEvents.clear();
	mainDisplayStrings.clear();
	floatingDisplayStrings.clear();
	feedbackDisplayStrings.clear();

	time_t timeNow;
	tm* tmNow;
	time(&timeNow);
	tmNow = localtime(&timeNow);
	tempMainDisplayLabel.push_back(*tmNow);
	tempMainDisplayLabel.push_back(*tmNow);
}

//getters
vector<Event> LogicUpdater::getNormalEvents() {
	return normalEvents;
}

vector<Event> LogicUpdater::getFloatingEvents() {
	return floatingEvents;
}

vector<Event> LogicUpdater::getFeedbackEvents() {
	return feedbackEvents;
}

vector<tm> LogicUpdater::getTempMainDisplayLabel() {
	return tempMainDisplayLabel;
}

vector<LogicUpdater::EVENT_STRING> LogicUpdater::getMainDisplayStrings() {
	return mainDisplayStrings;
}

vector<LogicUpdater::EVENT_STRING> LogicUpdater::getFloatingDisplayStrings() {
	return floatingDisplayStrings;
}

vector<string> LogicUpdater::getFeedbackDisplayStrings() {
	return feedbackDisplayStrings;
}

vector<string> LogicUpdater::getErrorStrings() {
	return errorStrings;
}

string LogicUpdater::getMainDisplayLabel() {
	return mainDisplayLabel;
}

int LogicUpdater::getTotalNumEvents() {
	int normalCount = 0;
	for (int i = 0 ; i < normalEvents.size() ; i++) {
		if (normalEvents[i].getName() != NEW_DAY_MESSAGE) {
			normalCount++;
		}
	}
	return floatingEvents.size() + normalCount;
}

int LogicUpdater::getTotalFloatingEvents() {
	return floatingEvents.size();
}

int LogicUpdater::getTotalNormalEvents() {
	return normalEvents.size();
}

int LogicUpdater::getIDFromIndex(int index) {
	if (index > getTotalNumEvents()) {
		return INVALID_NUMBER;
	} else {
		if (index <= getTotalFloatingEvents()) {
			return floatingEvents[index-1].getID();
		} else {
			int normalIndex = index - getTotalFloatingEvents();
			int count = 0;

			while (count != normalIndex) {
				if (normalEvents[count].getName() == NEW_DAY_MESSAGE) {
					normalIndex++;
				}
				count++;
			}
			count--;

			return normalEvents[count].getID();
		}
	}
}

string LogicUpdater::getNameFromIndex (int index) {
	if (index > getTotalNumEvents()) {
		return EMPTY_STRING;
	} else {
		if (index <= getTotalFloatingEvents()) {
			return floatingEvents[index-1].getName();
		} else {
			int normalIndex = index - getTotalFloatingEvents();
			int count = 0;

			while (count != normalIndex) {
				if (normalEvents[count].getName() == NEW_DAY_MESSAGE) {
					normalIndex++;
				}
				count++;
			}
			count--;

			return normalEvents[count].getName();
		}
	}
}

int LogicUpdater::getIDFromName(string name) {
	for (int i = 0 ; i < getTotalFloatingEvents(); i++) {
		if (floatingEvents[i].getName() == name) {
			return floatingEvents[i].getID();
		}
	}

	for (int i = 0 ; i < getTotalNormalEvents(); i++) {
		if (normalEvents[i].getName() == name) {
			return normalEvents[i].getID();
		}
	}
	return INVALID_NUMBER;
}

int LogicUpdater::getNewID() {
	return newID;
}


bool LogicUpdater::getIsFloatingFromID(int id) {
	for (int i = 0 ; i < getTotalFloatingEvents(); i++) {
		if (floatingEvents[i].getID() == id) {
			return floatingEvents[i].getIsFloating();
		}
	}

	for (int i = 0 ; i < getTotalNormalEvents(); i++) {
		if (normalEvents[i].getID() == id) {
			return normalEvents[i].getIsFloating();
		}
	}
}

Event LogicUpdater::getEventFromID(int id) {
	for (int i = 0 ; i < getTotalFloatingEvents(); i++) {
		if (floatingEvents[i].getID() == id) {
			return floatingEvents[i];
		}
	}

	for (int i = 0 ; i < getTotalNormalEvents(); i++) {
		if (normalEvents[i].getID() == id) {
			return normalEvents[i];
		}
	}
}


//setters
void LogicUpdater::setAllEvents(vector<Event> normalEvents,vector<Event> floatingEvents, string feedback, vector<tm> label, int id, string weekMonthOrNothing){
	newID = id;
	setWeekMonthOrNothing (weekMonthOrNothing);
	setFeedbackStrings(feedback);
	setFloatingEvents(floatingEvents);
	setNormalEvents(normalEvents, label);
}

void LogicUpdater::setFeedbackStrings(string newFeedback) {
	if (newFeedback != ""){
		feedbackDisplayStrings.push_back(newFeedback);
	}

	while (feedbackDisplayStrings.size()>3){
		feedbackDisplayStrings.erase(feedbackDisplayStrings.begin());
	}

	assert (feedbackDisplayStrings.size()<=3);
}


void LogicUpdater::setNoEventsMessage(vector<EVENT_STRING>& displayVec) {
	EVENT_STRING noEvent;
	noEvent.dateString = "";
	noEvent.eventString = NO_EVENTS_MESSAGE;
	noEvent.isNew = false;
	noEvent.isClash= false;
	noEvent.isMarker = false;
	noEvent.isCompleted = false;
	noEvent.importanceLevel= 0;
	displayVec.push_back(noEvent);

	assert(displayVec.size()==1);
}

void LogicUpdater::initializeEventString(LogicUpdater::EVENT_STRING &item){
	item.dateString = "";
	item.eventString = "";
	item.isNew = false;
	item.isClash = false;
	item.isMarker = false;
	item.isCompleted = false;
	item.importanceLevel = 0;
}



void LogicUpdater::setFloatingEvents(vector<Event> events) {
	floatingEvents = events;
	floatingEventsToString();
}

void LogicUpdater::floatingEventsToString() {
	floatingDisplayStrings.clear();

	if (floatingEvents.empty()) {
		setNoEventsMessage(floatingDisplayStrings);
		return;
	}
	
	for (int i = 0; i < floatingEvents.size(); i++) {
		EVENT_STRING temp;
		initializeEventString(temp);
		
		ostringstream outDate;
		outDate << (i + SHIFT_BY_ONE) << ".";
		temp.dateString = outDate.str();
		outDate.clear();

		ostringstream outEvent;
		outEvent << floatingEvents[i].getName();
		temp.eventString = outEvent.str();
		outEvent.clear();
		
		temp.isCompleted = floatingEvents[i].getIsCompleted();
		temp.importanceLevel = floatingEvents[i].getImportanceLevel();

		temp.isNew = setFloatingIsNew (i);
		
		floatingDisplayStrings.push_back(temp);
	}

	assert(floatingDisplayStrings.size()>=1);
}

bool LogicUpdater::setFloatingIsNew(int vectorIndex){
	assert(floatingEvents.size() > vectorIndex);

	bool isNew;

	if ( floatingEvents[vectorIndex].getID() == newID){
		isNew = true;
		} else{
			isNew = false;
		}

	return isNew;
}


void LogicUpdater::setMainDisplayLabel (vector<tm> label){
	assert(label.size()==2);

	mainDisplayLabel = "";

	if (isSingleDay(label)){
		if (isToday (label[0])){
			string commandToday = "[" + WORD_TODAY + "] ";
			mainDisplayLabel += commandToday;
		} else if (isTomorrow (label[0])){
			string commandTomorrow = "[" + WORD_TOMORROW + "] ";
			mainDisplayLabel += commandTomorrow;
		}
			
		std::string dateInString = setSingleDayString(label[0]);
		
		mainDisplayLabel += dateInString;
	} else {
		mainDisplayLabel = setMultipleDaysString(label[0],label[1]);
	}
}

void LogicUpdater::setWeekMonthOrNothing(string identity){
	weekMonthOrNothing = identity;
}

bool LogicUpdater::isSingleDay(vector<tm> label){
	assert(label.size()==2);

	bool isSingle;

	if (label[0].tm_mday == label[1].tm_mday && label[0].tm_mon == label[1].tm_mon && label[0].tm_year == label[1].tm_year){
		isSingle = true;
	} else{
		isSingle = false;
	}

	return isSingle;
}

bool LogicUpdater::isToday(tm date){
	bool isDateToday = false;

	//Initialize date & time to today according to system
	time_t now = time(0);
	struct tm today = *localtime(&now);

	if (today.tm_mday == date.tm_mday && today.tm_mon == date.tm_mon && today.tm_year == date.tm_year){
		isDateToday = true;
	}

	return isDateToday;
}

bool LogicUpdater::isTomorrow(tm date){
	bool isDateTomorrow = false;

	//Initialize date to tomorrow
	time_t now = time(0);
	struct tm tomorrow = *localtime(&now);
	tomorrow.tm_mday ++;

	mktime(&tomorrow);

	if (tomorrow.tm_mday == date.tm_mday && tomorrow.tm_mon == date.tm_mon && tomorrow.tm_year == date.tm_year){
		isDateTomorrow = true;
	}

	return isDateTomorrow;
}

bool LogicUpdater::isDisplayMonth(tm frontDate,tm backDate){
	bool isMonth = false;

	if (isFirstDayOfMonth(frontDate) && isLastDayOfMonth(backDate) && isSameMonth(frontDate,backDate) && isSameYear(frontDate,backDate)){
		isMonth = true;
	}

	if (weekMonthOrNothing == WORD_MONTH){
		isMonth = true;
	}

	return isMonth;
}

bool LogicUpdater::isFirstDayOfMonth(tm frontDate){
	bool isFirstDay;
	
	int monthBefore = frontDate.tm_mon;

	frontDate.tm_mday--;
	std::mktime(&frontDate);
	int monthAfter = frontDate.tm_mon;

	if (monthBefore != monthAfter){
		isFirstDay = true;
	} else {
		isFirstDay = false;
	}

	return isFirstDay;
}

bool LogicUpdater::isLastDayOfMonth(tm backDate){
	bool isLastDay;
	
	int monthBefore = backDate.tm_mon;

	backDate.tm_mday++;
	std::mktime(&backDate);
	int monthAfter = backDate.tm_mon;

	if (monthBefore != monthAfter){
		isLastDay = true;
	} else {
		isLastDay = false;
	}

	return isLastDay;
}

std::string LogicUpdater::setSingleDayString(tm label){
	string dayOfMonth = intToString(label.tm_mday);
	string month = intToMonth(label.tm_mon);
	string dayOfWeek = intToDayOfWeek(label.tm_wday);
	string dateInString = dayOfMonth + " " + month + ", " + dayOfWeek;

	return dateInString;
}

std::string LogicUpdater::setMultipleDaysString(tm start,tm end){
	std::string multipleDaysString = "";

	if (isDisplayMonth(start,end)){
		string commandMonth = "[" + WORD_MONTH + "] ";
		multipleDaysString += commandMonth;
	} else if (isDisplayWeek(start,end)){
		string commandWeek = "[" + WORD_WEEK + "] ";
		multipleDaysString += commandWeek;
	}

	string startDayOfMonth = intToString(start.tm_mday);
	string startMonth = intToMonth(start.tm_mon);

	multipleDaysString += startDayOfMonth + " " + startMonth;

	if (start.tm_year != end.tm_year){
		string startYear = intToString(start.tm_year + 1900) ;
		multipleDaysString += " " + startYear;
	}

	multipleDaysString += " - ";

	string endDayOfMonth = intToString(end.tm_mday);
	string endMonth = intToMonth(end.tm_mon);

	multipleDaysString += endDayOfMonth + " " + endMonth;

	string endYear = intToString(end.tm_year + 1900);
	multipleDaysString += " " +endYear;

	return multipleDaysString;
}



void LogicUpdater::setNormalEvents(vector<Event> events,vector<tm> label) {
	normalEvents = events;
	tempMainDisplayLabel = label;
	setMainDisplayLabel(label);
	normalEventsToString();
}
void LogicUpdater::normalEventsToString() {
	mainDisplayStrings.clear();

	if (normalEvents.empty()) {
		setNoEventsMessage(mainDisplayStrings);
		return;
	}

	std::vector<int> indexOfMarkers;
	int newEventStartTime = 0;
	int newEventEndTime = 0;
	int newEventIndex = -1;
	int indexForNormalEvents = getTotalFloatingEvents();

	for (int i=0; i < normalEvents.size(); i++){
		EVENT_STRING toBePushed;
		initializeEventString(toBePushed);

		if (normalEvents[i].getName() == NEW_DAY_MESSAGE){	
			indexOfMarkers.push_back(i);

			toBePushed.isMarker = true;
			toBePushed.eventString = setMarkerEventString(normalEvents[i],i);

			//isClash is set between 2 markers 
			if( indexOfMarkers.size() >= 2 && newEventIndex != -1 ){
				setIsClash(newEventStartTime, newEventEndTime, newEventIndex,indexOfMarkers);
				newEventIndex = -1;
			}
		} else {
			toBePushed.isNew = setNormalIsNew(i);
			toBePushed.isCompleted = normalEvents[i].getIsCompleted();
			toBePushed.importanceLevel = normalEvents[i].getImportanceLevel();
			toBePushed.dateString = setNormalEventDateString(normalEvents[i],++indexForNormalEvents);
			toBePushed.eventString = setNormalEventEventString(normalEvents[i]);			
		}

		if (toBePushed.isNew == true){
			newEventStartTime = getStartTime(normalEvents[i]);
			newEventEndTime = getEndTime(normalEvents[i]);
			newEventIndex = i;
		}

		mainDisplayStrings.push_back(toBePushed);
	}
	indexOfMarkers.push_back(normalEvents.size());
	//isClash is set after last event too
	if( indexOfMarkers.size() >= 2 && newEventIndex != -1 ){
		setIsClash(newEventStartTime, newEventEndTime, newEventIndex,indexOfMarkers);
		newEventIndex = -1;
	}

	assert(mainDisplayStrings.size()>=1);
}

std::string LogicUpdater::setMarkerEventString(Event marker, int index){
	ostringstream out;

	if( index != 0){
		out << "\n";
	}

	out << "[";
	out << marker.getStartDate().tm_mday;
	out << " ";

	int monthInt =marker.getStartDate().tm_mon;
	out << intToMonth(monthInt);

	out << " ";
	out << marker.getStartDate().tm_year + 1900;

	out << ", ";

	int dayOfWeekInt = marker.getStartDate().tm_wday;
	out << intToDayOfWeek(dayOfWeekInt);

	out << "]";
	out << "==============================================================";
	out << "\n";

	return out.str();
}

std::string LogicUpdater::setNormalEventDateString(Event eventToBeSet, int eventIndex){
	ostringstream outDate;
	
	outDate << eventIndex << "." ;
	outDate << "\t" ;

	outDate << "[";
	if (eventToBeSet.getIsDeadline()){
		outDate << "*DUE*   ";
		int endTime = getEndTime(eventToBeSet);
		outDate << intToTime(endTime);
	} else if (isAllDay(eventToBeSet)){
		outDate << "    ";
		outDate << WORD_ALLDAY;
		outDate << "    ";
	} else{
		int startTime = getStartTime(eventToBeSet);
		outDate << intToTime(startTime);
		outDate << "-" ;
		int endTime = getEndTime(eventToBeSet);
		outDate << intToTime(endTime);
	}
			
	outDate << "]" ;
	outDate << "\t";
		
	return outDate.str();
}

std::string LogicUpdater::setNormalEventEventString(Event eventToBeSet){
	ostringstream outEvent;

	std::string nameOfEvent = eventToBeSet.getName();

	while(nameOfEvent.size() > MAX_LENGTH_EVENT_NAME){
		outEvent << nameOfEvent.substr(0,MAX_LENGTH_EVENT_NAME);
		outEvent << "\n";
		outEvent << "\t\t\t\t\t";
		nameOfEvent = nameOfEvent.substr(MAX_LENGTH_EVENT_NAME);
	}

	outEvent << nameOfEvent;
	
	return outEvent.str();	
}

bool LogicUpdater::setNormalIsNew(int vectorIndex){
	assert (normalEvents.size() > vectorIndex);
	
	bool isNew;

	if (newID == normalEvents[vectorIndex].getID()){
		isNew = true;
	} else {
		isNew = false;
	}
	return isNew;
}

void LogicUpdater:: setIsClash(int newEventStartTime, int newEventEndTime, int newEventIndex, std::vector<int> indexOfNewMarker){
	assert(indexOfNewMarker.size() >=0);

	//If there is a clash, this variable will become true
	bool setNewItemClash = false;

	for (int i=indexOfNewMarker[indexOfNewMarker.size()-2]+1; i < indexOfNewMarker[indexOfNewMarker.size()-1]; i++){
		int checkEventStartTime = getStartTime (normalEvents[i]);
		int checkEventEndTime = getEndTime (normalEvents[i]);

		//Case 1
		if (checkEventStartTime < newEventStartTime && newEventStartTime < checkEventEndTime){
			if (normalEvents[i].getID() != newID){
				mainDisplayStrings[i].isClash = true;
				setNewItemClash = true;
			}
		}
		
		//Case 2
		if (checkEventStartTime < newEventEndTime && newEventEndTime < checkEventEndTime){
			if (normalEvents[i].getID() != newID){
				mainDisplayStrings[i].isClash = true;
				setNewItemClash = true;
			}
		}
		
		//Case 3
		if (newEventStartTime < checkEventStartTime  && checkEventStartTime < newEventEndTime){
			if (normalEvents[i].getID() != newID){
				mainDisplayStrings[i].isClash = true;
				setNewItemClash = true;
			}
		}
		
		//Case 4
		if (newEventStartTime < checkEventEndTime && checkEventEndTime < newEventEndTime){
			if (normalEvents[i].getID() != newID){
				mainDisplayStrings[i].isClash = true;
				setNewItemClash = true;
			}
		}
		
		//Case 5 exactly same timeslot
		if (checkEventStartTime == newEventStartTime && checkEventEndTime == newEventEndTime){
			if (normalEvents[i].getID() != newID){
				mainDisplayStrings[i].isClash = true;
				setNewItemClash = true;
			}
		}
		
		if (setNewItemClash){
			mainDisplayStrings[newEventIndex].isClash = true;
		}
	}
}

bool LogicUpdater::isAllDay(Event eventToDisplay){
	bool isAllDayEvent = false;
	
	int startTime = getStartTime(eventToDisplay);
	string startTimeInString = intToTime(startTime);

	int endTime = getEndTime(eventToDisplay);
	string endTimeInString = intToTime(endTime);

	if (startTimeInString == "00:00am"  && endTimeInString == "11:59pm"){
		isAllDayEvent = true;
	}

	return isAllDayEvent;
}


std::string LogicUpdater::intToDayOfWeek (int dayInNum){
	if(dayInNum == 0){
		return "Sunday";
	} else if (dayInNum == 1){
		return "Monday";
	} else if (dayInNum == 2){
		return "Tuesday";
	} else if (dayInNum == 3){
		return "Wednesday";
	} else if (dayInNum == 4){
		return "Thursday";
	} else if (dayInNum == 5){
		return "Friday";
	} else if (dayInNum == 6){
		return "Saturday";
	} else{
		return "Invalid day";
	}
}

std::string LogicUpdater::intToMonth (int monthInNum){
	if(monthInNum == 0){
		return "January";
	} else if(monthInNum  == 1){
		return "Feburary";
	} else if(monthInNum  == 2){
		return "March";
	} else if(monthInNum  == 3){
		return "April";
	} else if(monthInNum  == 4){
		return "May";
	} else if(monthInNum  == 5){
		return "June";
	} else if(monthInNum  == 6){
		return "July";
	} else if(monthInNum  == 7){
		return "August";
	} else if(monthInNum  == 8){
		return "September";
	} else if(monthInNum  == 9){
		return "October";
	} else if(monthInNum  == 10){
		return "November";
	} else if(monthInNum  == 11){
		return "December";
	} else {
		return "Invalid month";
	}
}

std::string LogicUpdater::intToString(int num){
	std::string outString;
	std::ostringstream oss;
	oss << num;
	return oss.str();
}

std::string LogicUpdater::intToTime (int timeInInt){
	int hours;
	int minutes;
	bool afterTwelve = false;
	std::ostringstream oss;
	hours = timeInInt/100;
	minutes = timeInInt%100;

	if(hours > 12){
		hours = hours - 12;
		afterTwelve = true;
	}

	if (hours == 12){
		afterTwelve = true;
	}

	if(hours >= 10){
		oss << hours;
	} else{
		oss << "0";
		oss << hours;
	}

	oss << ":";

	if(minutes >= 10){
		oss << minutes;
	} else{
		oss << "0";
		oss << minutes;
	}

	if(afterTwelve){		
		oss << "pm";
	} else {
		oss << "am";
	}
	
	return oss.str();
}

int LogicUpdater:: getStartTime(Event toGet){
	return toGet.getStartDate().tm_hour*100 + toGet.getStartDate().tm_min;
}

int LogicUpdater:: getEndTime(Event toGet){
	return toGet.getEndDate().tm_hour*100 + toGet.getEndDate().tm_min;
}


bool LogicUpdater::isDisplayWeek(tm frontDate,tm backDate){
	bool isWeek;

	if (isFirstDayOfWeek(frontDate) && isLastDayOfWeek(backDate) && (backDate.tm_mday - frontDate.tm_mday) == 6 && isSameMonth(frontDate,backDate) && isSameYear(frontDate,backDate)){
		isWeek = true;
	}

	if (weekMonthOrNothing == WORD_WEEK){
		isWeek = true;
	}

	return isWeek;
}

bool LogicUpdater::isFirstDayOfWeek(tm frontDate){
	bool isFirstDay;

	if (frontDate.tm_wday == 0){
		isFirstDay = true;
	} else {
		isFirstDay = false;
	}

	return isFirstDay;

}

bool LogicUpdater::isLastDayOfWeek(tm backDate){
	bool isLastDay;

	if (backDate.tm_wday == 6){
		isLastDay = true;
	} else {
		isLastDay = false;
	}

	return isLastDay;
}

bool LogicUpdater::isSameMonth(tm frontDate,tm backDate){
	bool sameMonth;

	if(frontDate.tm_mon == backDate.tm_mon){
		sameMonth = true;
	} else {
		sameMonth = false;
	}

	return sameMonth;
}

bool LogicUpdater::isSameYear(tm frontDate,tm backDate){
	bool sameYear;

	if(frontDate.tm_year == backDate.tm_year){
		sameYear = true;
	} else {
		sameYear = false;
	}

	return sameYear;
}




