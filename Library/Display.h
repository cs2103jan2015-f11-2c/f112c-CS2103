// Display keeps track of 3 x vector<Event> (1 each for floating, normal and feedback) and 3 x vector<string> (similar to event vectors)
// When any of the vector<Event> is changed, it will update the corresponding vector<string>
//		(e.g. if normalEvents is changed it will change mainDisplayStrings, floatingEvents<=>floatingDisplayStrings, feedbackEvents<=>feedbackDisplayStrings)
// UI can get any of the vector<string> to display in the appropriate window, no need to get vector<Event>

#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include "Event.h"


class Display {
public:
	struct MAIN_EVENT {
		string eventString;
		bool isNew;
	};


private:
	vector<Event> normalEvents;
	vector<Event> floatingEvents;
	vector<Event> feedbackEvents;
	
	vector<MAIN_EVENT> mainDisplayStrings;
	vector<string> floatingDisplayStrings;
	vector<string> feedbackDisplayStrings;

	int totalNumEvents;


public:
	//constructor, destructor
	Display();
	//~Display();
	

	//getters
	vector<Event> getNormalEvents();
	vector<Event> getFloatingEvents();
	vector<Event> getFeedbackEvents();
	vector<MAIN_EVENT> getMainDisplayStrings();
	vector<string> getFloatingDisplayStrings();
	vector<string> getFeedbackDisplayStrings();

	int getTotalNumEvents();


	//setters
	void setNormalEvents(vector<Event> events);
	void setFloatingEvents(vector<Event> events);
	void setFeedbackEvents(vector<Event> events);

	void normalEventsToString();
	void floatingEventsToString();
	void feedbackEventsToString();

	void deleteEvent(int id);
};

#endif