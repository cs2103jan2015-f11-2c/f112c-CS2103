// Display keeps track of 3 x vector<Event> (1 each for floating, normal and feedback) and 3 x vector<string> (similar to event vectors)
// When any of the vector<Event> is changed, it will update the corresponding vector<string>
//		(e.g. if normalEvents is changed it will change mainDisplayStrings, floatingEvents<=>floatingDisplayStrings, feedbackEvents<=>feedbackDisplayStrings)
// UI can get any of the vector<string> to display in the appropriate window, no need to get vector<Event>

#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include <sstream>
#include "Event.h"

using std::ostringstream;


class Display {
public:
	struct EVENT_STRING {
		string eventString;
		bool isNew;
		bool isClash;
	};


private:
	vector<Event> normalEvents;
	vector<Event> floatingEvents;
	vector<Event> feedbackEvents;
	
	vector<EVENT_STRING> mainDisplayStrings;
	vector<EVENT_STRING> floatingDisplayStrings;
	vector<string> feedbackDisplayStrings;
	vector<string> errorStrings;

	int newID;
	int totalNumEvents;

	// This is required as events' numberings in main display will carry on from here
	// For now, main display events' numbering will start from 1
	int totalFloatingEvents;


public:
	static const string ADDED_MESSAGE;
	static const string EDITED_MESSAGE;
	static const string DELETED_MESSAGE;
	static const string EVENT_NOT_FOUND_MESSAGE;

	//constructor, destructor
	Display();
	//~Display();
	

	//getters
	vector<Event> getNormalEvents();
	vector<Event> getFloatingEvents();
	vector<Event> getFeedbackEvents();
	vector<EVENT_STRING> getMainDisplayStrings();
	vector<EVENT_STRING> getFloatingDisplayStrings();
	vector<string> getFeedbackDisplayStrings();
	vector<string> getErrorStrings();

	int getTotalNumEvents();
	int getTotalFloatingEvents();
	int getIDFromIndex(int index);
	int getNewID();


	//setters
	void setNormalEvents(vector<Event> events, int id);
	void setFloatingEvents(vector<Event> events);
	void setFeedbackEvents(vector<Event> events);

	void normalEventsToString();
	void floatingEventsToString();
	void setFeedbackStrings(string newFeedback);

	bool setIsNew(int);
	void setIsClash(int,int,int);

	int getStartTime(Event);
	int getEndTime(Event);


	//void setNewestEvent(int id);
};

#endif