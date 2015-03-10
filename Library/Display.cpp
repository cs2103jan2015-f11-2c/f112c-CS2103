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

vector<Display::MAIN_EVENT> Display::getMainDisplayStrings() {
	return mainDisplayStrings;
}

vector<string> Display::getFloatingDisplayStrings() {
	return floatingDisplayStrings;
}

vector<string> Display::getFeedbackDisplayStrings() {
	return feedbackDisplayStrings;
}

int Display::getTotalNumEvents() {
	return floatingEvents.size() + normalEvents.size();
}

int Display::getID(int index) {
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
	floatingDisplayStrings.clear();

	for (int i = 0; i < floatingEvents.size(); i++) {
		floatingDisplayStrings.push_back(floatingEvents[i].getName());
	}
}

void Display::setFeedbackStrings(string newFeedback) {
	feedbackDisplayStrings.push_back(newFeedback);
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