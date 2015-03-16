#include "Display.h"


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

vector<Display::MAIN_EVENT> Display::getMainDisplayStrings() {
	return mainDisplayStrings;
}

vector<Display::FLOATING_EVENT> Display::getFloatingDisplayStrings() {
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


//setters
void Display::setNormalEvents(vector<Event> events, int id) {
	newID = id;
	normalEvents = events;
	normalEventsToString();
}

void Display::setFloatingEvents(vector<Event> events) {
	floatingEvents = events;
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
		if (checkEventStartTime <= newEventStartTime && newEventStartTime <= checkEventEndTime){
			if (normalEvents[i].getID() != newID){
				mainDisplayStrings[i].isClash = true;
				setNewItemClash = true;
			}
		}

		//Case 2
		if (checkEventStartTime <= newEventEndTime && newEventEndTime <= checkEventEndTime){
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

void Display::normalEventsToString() {
	mainDisplayStrings.clear();

	int newEventStartTime = 0;
	int newEventEndTime = 0;

	int newEventIndex = -1;

	for (int i=0; i < normalEvents.size(); i++){
		ostringstream out;

		out << (i+1) << "." << " " << normalEvents[i].getName();

		//Constructing MAIN_EVENT items and initializing
		MAIN_EVENT toBePushed;
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

	for (int i = 0; i < floatingEvents.size(); i++) {
		ostringstream out;
		out << (i+1) << "." << " " << floatingEvents[i].getName();
		
		FLOATING_EVENT temp;
		temp.eventString = out.str();
		temp.isNew = false;
		floatingDisplayStrings.push_back(temp);

		out.clear();
	}

	floatingDisplayStrings.back().isNew = true;
}

void Display::setFeedbackStrings(string newFeedback) {
	feedbackDisplayStrings.push_back(newFeedback);
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
