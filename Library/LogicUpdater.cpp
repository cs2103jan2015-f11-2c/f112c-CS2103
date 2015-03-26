#include "LogicUpdater.h"


const int LogicUpdater::GARBAGE_INT = -12345;
const int LogicUpdater::INVALID_NUMBER = -1;
const string LogicUpdater::NO_EVENTS_MESSAGE = "Currently no task";
const string LogicUpdater::ADDED_MESSAGE = " added";
const string LogicUpdater::EDITED_MESSAGE = " edited";
const string LogicUpdater::DELETED_MESSAGE = " deleted";
const string LogicUpdater::SHOW_MESSAGE = "showing ";
const string LogicUpdater::EVENT_NOT_FOUND_MESSAGE = " not found, showing partial matches";
const string LogicUpdater::CHOOSE_EVENT_MESSAGE = "More than 1 result found, please select one from above via index.";
const string LogicUpdater::NEW_DAY_MESSAGE = "-MSmsgjyw-";

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
	return floatingEvents.size() + normalEvents.size();
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
void LogicUpdater::setAllEvents(vector<Event> normalEvents,vector<Event> floatingEvents, string feedback, vector<tm> label, int id){
	newID = id;
	setFeedbackStrings(feedback);
	setFloatingEvents(floatingEvents);
	setNormalEvents(normalEvents, label);
}

void LogicUpdater::setFeedbackStrings(string newFeedback) {
	feedbackDisplayStrings.push_back(newFeedback);
	
	while (feedbackDisplayStrings.size()>3){
		feedbackDisplayStrings.erase(feedbackDisplayStrings.begin());
	}

	assert (feedbackDisplayStrings.size()<=3);
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
		ostringstream out;
		out << (i + 1) << "." << " " << floatingEvents[i].getName();
		
		EVENT_STRING temp;
		temp.eventString = out.str();
		temp.isMarker = false;

		if (floatingEvents[i].getID() == newID){
			temp.isNew = true;
		} else{
			temp.isNew = false;
		}

		floatingDisplayStrings.push_back(temp);

		out.clear();
	}
	assert(floatingDisplayStrings.size()>=1);
}

void LogicUpdater::setNormalEvents(vector<Event> events,vector<tm> label) {
	normalEvents = events;
	tempMainDisplayLabel = label;
	setMainDisplayLabel(label);
	normalEventsToString();
}

void LogicUpdater::setMainDisplayLabel (vector<tm> label){
	assert(label.size()==2);

	if (label[0].tm_mday == label[1].tm_mday && label[0].tm_mon == label[1].tm_mon){
		//1 day only
		Conversion convert;
		string dayOfMonth = convert.intToString(label[0].tm_mday);

		string month = convert.intToMonth(label[0].tm_mon);

		string dayOfWeek = convert.intToDayOfWeek(label[0].tm_wday);

		mainDisplayLabel = dayOfMonth + " " + month + ", " + dayOfWeek;
	} else {
		//More than 1 day
		Conversion convert;
		string startDayOfMonth = convert.intToString(label[0].tm_mday);
		string startMonth = convert.intToMonth(label[0].tm_mon);

		mainDisplayLabel = startDayOfMonth + " " + startMonth;

		if (label[0].tm_year != label[1].tm_year){
			string startYear = convert.intToString(label[0].tm_year+ 1900) ;
			mainDisplayLabel += " " + startYear;
		}

		mainDisplayLabel += " - ";

		string endDayOfMonth = convert.intToString(label[1].tm_mday);
		string endMonth = convert.intToMonth(label[1].tm_mon);

		mainDisplayLabel += endDayOfMonth + " " + endMonth;

		string endYear = convert.intToString(label[1].tm_year + 1900);
		mainDisplayLabel += " " +endYear;
	}
}

bool LogicUpdater::setIsNew(int vectorIndex){
	bool isNew;
	if (newID == normalEvents[vectorIndex].getID()){
		isNew = true;
	} else {
		isNew = false;
	}
	return isNew;
}


void LogicUpdater:: setIsClash(int newEventStartTime, int newEventEndTime, int newEventIndex){
	
	//If there is a clash, this variable will become true
	bool setNewItemClash = false;

	for (int i=0; i < normalEvents.size(); i++){
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

		//Case 3 exactly same timeslot
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

int LogicUpdater:: getStartTime(Event toGet){
	return toGet.getStartDate().tm_hour*100 + toGet.getStartDate().tm_min;
}

int LogicUpdater:: getEndTime(Event toGet){
	return toGet.getEndDate().tm_hour*100 + toGet.getEndDate().tm_min;
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
	
	if(afterTwelve){
		oss << hours;

		if (minutes >0){
		oss << ":";
		oss << minutes;
		}
			
		oss << "pm";
	} else {
		oss << hours;

		if (minutes >0){
		oss << ":";
		oss << minutes;
		}
		
		oss << "am";
	}
	
	return oss.str();
}

void LogicUpdater::normalEventsToString() {
	mainDisplayStrings.clear();

	if (normalEvents.empty()) {
		setNoEventsMessage(mainDisplayStrings);
		return;
	}
	
	int headCounter =0;
	int newEventStartTime = 0;
	int newEventEndTime = 0;
	int newEventIndex = -1;

	//This for loop requires refactoring
	int indexForNormalEvents = getTotalFloatingEvents();

	for (int i=0; i < normalEvents.size(); i++){
		//Constructing MAIN_EVENT items and initializing
		EVENT_STRING toBePushed;

		ostringstream out;

		//Generate header
		if (normalEvents[i].getName() == NEW_DAY_MESSAGE){
			toBePushed.isMarker = true;
			if (headCounter!=0){
				out << "\n";
			}
			
			headCounter++;

			out << "[";
			out << normalEvents[i].getStartDate().tm_mday;
			out << " ";

			Conversion convert;
			int monthInt = normalEvents[i].getStartDate().tm_mon;
			out << convert.intToMonth(monthInt);

			out << " ";
			out << normalEvents[i].getStartDate().tm_year + 1900;

			out << ", ";

			int dayOfWeekInt = normalEvents[i].getStartDate().tm_wday;
			out << convert.intToDayOfWeek(dayOfWeekInt);

			out << "]";
			out << "===============================================";
			out << "\n";
		} 
		 //Generate event list
		 else {
			toBePushed.isMarker = false;

			out << (++indexForNormalEvents) << "." ;
			out << "\t" ;
			out << "[" ;
			int startTime = getStartTime(normalEvents[i]);
			out << intToTime(startTime);
			out << "-" ;
			int endTime = getEndTime(normalEvents[i]);
			out << intToTime(endTime);
			out << "]" ;
			out << "\t";
			out << normalEvents[i].getName();
		
			if (normalEvents[i].getDescription() != ""){
				out << " ";
				out << "(";
				out << normalEvents[i].getDescription();
				out << ")";
			}

			if (normalEvents[i].getTags().size() != 0){
				out << "\n";
				out << "\t\t\t\t";
			
				vector<string> tagVector = normalEvents[i].getTags();
				for (int i=0; i<tagVector.size(); i++){
					out << tagVector[i];
					out << " "; 
				}	
			}
		}
		toBePushed.eventString = out.str();

		toBePushed.isNew = setIsNew(i);

		if (toBePushed.isNew == true){
			newEventStartTime = getStartTime(normalEvents[i]);
			newEventEndTime = getEndTime(normalEvents[i]);
			newEventIndex = i;

			//Add in exception
		}

		//Set isClash is false first
		toBePushed.isClash = false;

		mainDisplayStrings.push_back(toBePushed);

		out.clear();
	}
	
	setIsClash(newEventStartTime, newEventEndTime, newEventIndex);

	assert(mainDisplayStrings.size()>=1);
}

void LogicUpdater::setNoEventsMessage(vector<EVENT_STRING>& displayVec) {
	EVENT_STRING noEvent;
	noEvent.eventString = NO_EVENTS_MESSAGE;
	noEvent.isClash= false;
	noEvent.isNew = false;
	noEvent.isMarker = false;
	
	displayVec.push_back(noEvent);

	assert(displayVec.size()==1);
}





//========================================================================================================================

// Not in use for now
void LogicUpdater::setFeedbackEvents(vector<Event> events) {
	//Maximum only 3
	feedbackEvents.clear();

	for (int i=0; i<3 || i< events.size();i++){
		feedbackEvents.push_back(events[events.size()-i]);
	}

	std::reverse(feedbackEvents.begin(),feedbackEvents.end());

	assert(feedbackEvents.size()<=3);
}

/*
void Display::setNewestEvent(int id) {
	int index;

	for (int i = 0 ; i < normalEvents.size() ; i++) {
		if (normalEvents[i].getID() == id) {
			index = i;
		}
		break;
	}

}
*/