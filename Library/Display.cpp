#include "Display.h"

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

vector<string> Display::getMainDisplayStrings() {
	return mainDisplayStrings;
}

vector<string> Display::getFloatingDisplayStrings() {
	return floatingDisplayStrings;
}

vector<string> Display::getFeedbackDisplayStrings() {
	return feedbackDisplayStrings;
}


//setters
void Display::setNormalEvents(vector<Event> events) {
	normalEvents = events;
}

void Display::setFloatingEvents(vector<Event> events) {
	floatingEvents = events;
	floatingEventsToString();
}

void Display::setFeedbackEvents(vector<Event> events) {
	feedbackEvents = events;
}

void Display::floatingEventsToString() {
	for (int i = 0; i < floatingEvents.size(); i++) {
		floatingDisplayStrings.push_back(floatingEvents[i].getName());
	}
}

void Display::deleteEvent(int id) {
	vector<Event> temp = floatingEvents;
	
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i].getID() == id) {
			temp.erase(temp.begin() + i);
		}
		return;
	}

	return;
}