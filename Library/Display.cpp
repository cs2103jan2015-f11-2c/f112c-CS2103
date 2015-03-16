#include "Display.h"


const string Display::ADDED_MESSAGE = " added";
const string Display::EDITED_MESSAGE = " edited";
const string Display::DELETED_MESSAGE = " deleted";

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

vector<string> Display::getFloatingDisplayStrings() {
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

void Display::normalEventsToString() {
}

void Display::floatingEventsToString() {
	floatingDisplayStrings.clear();

	for (int i = 0; i < floatingEvents.size(); i++) {
		ostringstream out;
		out << (i+1) << "." << " " << floatingEvents[i].getName();
		
		floatingDisplayStrings.push_back(out.str());

		out.clear();
	}
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
