// Display keeps track of 3 x vector<Event> (1 each for floating, normal and feedback) and 3 x vector<string> (similar to event vectors)
// When any of the vector<Event> is changed, it will update the corresponding vector<string>
//		(e.g. if normalEvents is changed it will change mainDisplayStrings, floatingEvents<=>floatingDisplayStrings, feedbackEvents<=>feedbackDisplayStrings)
// UI can get any of the vector<string> to display in the appropriate window, no need to get vector<Event>

#pragma once

#ifndef LOGIC_UPDATER
#define LOGIC_UPDATER

#include <assert.h>
#include <sstream>
#include <algorithm>
#include "Event.h"

using std::ostringstream;


class LogicUpdater {

public:
	struct EVENT_STRING {
		string dateString;
		string eventString;
		bool isNew;
		bool isClash;
		bool isMarker;
		bool isCompleted;
		int importanceLevel;
	};

	static const int GARBAGE_INT;
	static const int INVALID_NUMBER;
	static const string EMPTY_STRING;

	static const string NO_EVENTS_MESSAGE;
	static const string ADDED_MESSAGE;
	static const string EDITED_MESSAGE;
	static const string DELETED_MESSAGE;
	static const string SHOW_MESSAGE;
	static const string EVENT_NOT_FOUND_MESSAGE;
	static const string PARTIAL_EVENT_FOUND_MESSAGE;
	static const string CHOOSE_EVENT_MESSAGE;
	static const string NEW_DAY_MESSAGE;
	static const string UNDO_MESSAGE;
	static const string REDO_MESSAGE;

	static const string WORD_TODAY;
	static const string WORD_YESTERDAY;
	static const string WORD_TOMORROW;

	static const string WORD_ALLDAY;

	static const int SHIFT_BY_ONE;


	

private:
	//Private attributes
	vector<Event> normalEvents;
	vector<Event> floatingEvents;
	vector<Event> feedbackEvents;
	vector<tm> tempMainDisplayLabel;

	vector<EVENT_STRING> mainDisplayStrings;
	string mainDisplayLabel;
	vector<EVENT_STRING> floatingDisplayStrings;
	vector<string> feedbackDisplayStrings;
	vector<string> errorStrings;
	
	int newID;
	

public:
	//constructor
	LogicUpdater();
	
	//getters
	vector<Event> getNormalEvents();
	vector<Event> getFloatingEvents();
	vector<Event> getFeedbackEvents();
	vector<tm> getTempMainDisplayLabel();

	vector<EVENT_STRING> getMainDisplayStrings();
	vector<EVENT_STRING> getFloatingDisplayStrings();
	vector<string> getFeedbackDisplayStrings();
	vector<string> getErrorStrings();
	string getMainDisplayLabel();
	
	int getTotalNumEvents();
	int getTotalFloatingEvents();
	int getTotalNormalEvents();
	int getIDFromIndex(int index);
	string getNameFromIndex (int index);
	int getIDFromName(string name);
	int getNewID();

	bool getIsFloatingFromID(int id);
	Event getEventFromID(int id);

	//setter
	void setAllEvents (vector<Event> normalEvents,vector<Event> floatingEvents,string feedback, vector<tm> label, int id);
	void setFeedbackStrings(string newFeedback);

private:

	void initializeEventString(EVENT_STRING &item);
	void setNoEventsMessage(vector<EVENT_STRING>& displayVec);

	void setFloatingEvents(vector<Event> events);
	void floatingEventsToString();
	bool setFloatingIsNew(int);

	void setMainDisplayLabel (vector<tm> label);
	bool isSingleDay(vector<tm>);
	std::string setSingleDayString(tm);
	std::string setMultipleDaysString(tm,tm);
	bool isToday(tm);
	bool isTomorrow(tm);
	
	void setNormalEvents(vector<Event> events,vector<tm> label);
	void normalEventsToString();
	std::string setMarkerEventString(Event, int );
	std::string setNormalEventDateString(Event, int );

	bool setNormalIsNew(int);
	void setIsClash(int,int,int,std::vector<int>);
	bool isAllDay(Event);

	std::string intToDayOfWeek (int);
	std::string intToMonth (int);
	std::string intToString(int);
	string intToTime (int);

	int getStartTime(Event);
	int getEndTime(Event); 

	
	
	

	


};

#endif