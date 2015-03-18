#include "Display.h"


const string Display::NO_EVENTS_MESSAGE = "nothing here";
const string Display::ADDED_MESSAGE = " added";
const string Display::EDITED_MESSAGE = " edited";
const string Display::DELETED_MESSAGE = " deleted";
const string Display::EVENT_NOT_FOUND_MESSAGE = " not found";

//constructor
Display::Display() {
	normalEvents.clear();
	floatingEvents.clear();
	feedbackEvents.clear();
	mainDisplayStrings.clear();
	floatingDisplayStrings.clear();
	feedbackDisplayStrings.clear();
	
}


//getters
vector<Event> Display::getNormalEvents() {
	return normalEvents;
}

vector<Event> Display::getFloatingEvents() {
	return floatingEvents;
}

vector<Event> Display::getFeedbackEvents() {
	return feedbackEvents;
}

vector<Display::EVENT_STRING> Display::getMainDisplayStrings() {
	return mainDisplayStrings;
}

vector<Display::EVENT_STRING> Display::getFloatingDisplayStrings() {
	return floatingDisplayStrings;
}

vector<string> Display::getFeedbackDisplayStrings() {
	return feedbackDisplayStrings;
}

vector<string> Display::getErrorStrings() {
	return errorStrings;
}

int Display::getTotalNumEvents() {
	return floatingEvents.size() + normalEvents.size();
}

int Display::getTotalFloatingEvents() {
	return floatingEvents.size();
}

int Display::getTotalNormalEvents() {
	return normalEvents.size();
}

int Display::getIDFromIndex(int index) {
	if (index > getTotalNumEvents()) {
		return -1;
	} else {
		if (index <= floatingEvents.size()) {
			return floatingEvents[index-1].getID();
		} else {
			int normalIndex = index - floatingEvents.size();
			return normalEvents[normalIndex - 1].getID();
		}
	}
}

int Display::getNewID() {
	return newID;
}

Event Display::getEventFromID(int id) {
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
void Display::setNormalEvents(vector<Event> events, int id) {
	newID = id;
	normalEvents = events;
	normalEventsToString();
}

void Display::setFloatingEvents(vector<Event> events, int id) {
	newID = id;
	floatingEvents = events;
	totalFloatingEvents = events.size();
	floatingEventsToString();
}

void Display::setFeedbackEvents(vector<Event> events) {
	feedbackEvents = events;
}


bool Display::setIsNew(int vectorIndex){
	bool isNew;
	if ( newID == normalEvents[vectorIndex].getID()){
		isNew = true;
	} else {
		isNew = false;
	}

	return isNew;
}


void Display:: setIsClash(int newEventStartTime, int newEventEndTime, int newEventIndex){
	
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

int Display:: getStartTime(Event toGet){
	return toGet.getStartDate().tm_hour*100 + toGet.getStartDate().tm_min;
}

int Display:: getEndTime(Event toGet){
	return toGet.getEndDate().tm_hour*100 + toGet.getEndDate().tm_min;
}

std::string Display::intToTime (int timeInInt){
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

void Display::normalEventsToString() {
	mainDisplayStrings.clear();

	/*
	if (normalEvents.empty()) {
		setNoEventsMessage(mainDisplayStrings);
		return;
	}
	*/
	
	int newEventStartTime = 0;
	int newEventEndTime = 0;

	int newEventIndex = -1;

	for (int i=0; i < normalEvents.size(); i++){
		ostringstream out;

		out << (i + 1 + getTotalFloatingEvents()) << "." ;
		out << "\t" ;
		out << "[" ;
		int startTime = getStartTime(normalEvents[i]);
		out << intToTime(startTime);
		out << "-" ;
		int endTime = getEndTime(normalEvents[i]);
		out << intToTime(endTime);
		out << "]" ;
		out << "\t\t";
		out << normalEvents[i].getName();
		
		if (normalEvents[i].getDescription() != ""){
			out << "   ";
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

		out << "\n";

		//Constructing MAIN_EVENT items and initializing
		EVENT_STRING toBePushed;
		toBePushed.eventString = out.str();

		toBePushed.isNew = setIsNew(i);

		if (toBePushed.isNew == true){
			newEventStartTime = getStartTime(normalEvents[i]);
			newEventEndTime = getEndTime(normalEvents[i]);
			newEventIndex = i;
		}

		//Set isClash is false first
		toBePushed.isClash = false;

		mainDisplayStrings.push_back(toBePushed);

		out.clear();
	}

	setIsClash(newEventStartTime, newEventEndTime, newEventIndex);
}



void Display::floatingEventsToString() {
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

		if ( floatingEvents[i].getID() == newID){
			temp.isNew = true;
		} else{
			temp.isNew = false;
		}

		floatingDisplayStrings.push_back(temp);

		out.clear();
	}
}

void Display::setFeedbackStrings(string newFeedback) {
	feedbackDisplayStrings.push_back(newFeedback);
}

void Display::setNoEventsMessage(vector<EVENT_STRING>& displayVec) {
	EVENT_STRING noEvent;
	noEvent.eventString = NO_EVENTS_MESSAGE;
	
	displayVec.push_back(noEvent);
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
