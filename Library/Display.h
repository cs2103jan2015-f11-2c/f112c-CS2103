// Display keeps track of 3 x vector<Event> (1 each for floating, normal and feedback) and 3 x vector<string> (similar to event vectors)
// When any of the vector<Event> is changed, it will update the corresponding vector<string>
//		(e.g. if normalEvents is changed it will change mainDisplayStrings, floatingEvents<=>floatingDisplayStrings, feedbackEvents<=>feedbackDisplayStrings)
// UI can get any of the vector<string> to display in the appropriate window, no need to get vector<Event>

#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include <sstream>
#include "Event.h"
#include "Conversion.h"

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
	string mainDisplayLabel;

	int newID;
	int totalNumEvents;

	// This is required as events' numberings in main display will carry on from here
	// For now, main display events' numbering will start from 1
	int totalFloatingEvents;


public:
	static const string NO_EVENTS_MESSAGE;
	static const string ADDED_MESSAGE;
	static const string EDITED_MESSAGE;
	static const string DELETED_MESSAGE;
	static const string EVENT_NOT_FOUND_MESSAGE;
	static const string NEW_DAY_MESSAGE;

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
	string getMainDisplayLabel();

	int getTotalNumEvents();
	int getTotalFloatingEvents();
	int getTotalNormalEvents();
	int getIDFromIndex(int index);
	int getNewID();
	Event getEventFromID(int id);


	//setters
	void setNormalEvents(vector<Event> events, int id);
	void setFloatingEvents(vector<Event> events, int id);
	void setFeedbackEvents(vector<Event> events);
	void setMainDisplayLabel (vector<tm> label);

	void normalEventsToString();
	void floatingEventsToString();
	void setFeedbackStrings(string newFeedback);
	void setNoEventsMessage(vector<EVENT_STRING>& displayVec);

	bool setIsNew(int);
	void setIsClash(int,int,int);

	int getStartTime(Event);
	int getEndTime(Event); 

	string intToTime (int);


	//void setNewestEvent(int id);
};

#endif