/**
 * This class is used store information that are to be displayed to the user. 
 * Key information are first stored in it's primitive vector<event> and vector<tm> form. These information are subsequently being converted and stored as vector<EVENT_STRING> and vector<string> form.
 * The former form is being used by the setter for checking and updating purposes while the latter is being used for direct and easier display to user. 
 *
 * @author A0111230J
 * @author A0111089L
 */


#pragma once

#ifndef LOGIC_UPDATER
#define LOGIC_UPDATER

#include <assert.h>
#include <ctime>
#include <algorithm>
#include "Event.h"
#include "LogicLog.h"

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

/*
* =================================================================================================================================================================== 
* Static variables 
* ===================================================================================================================================================================
*/
	static const int GARBAGE_INT;
	static const int INVALID_NUMBER;
	static const int ZERO;
	static const string EMPTY_STRING;
	static const int SHIFT_BY_ONE;
	static const int MAX_LENGTH_EVENT_NAME;

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
	static const string COMPLETED_MESSAGE;

	static const string WORD_TODAY;
	static const string WORD_TOMORROW;
	static const string WORD_MONTH;
	static const string WORD_WEEK;
	static const string WORD_ALLDAY;

	static const string LABEL_TODAY;
	static const string LABEL_TOMORROW;
	static const string LABEL_MONTH;
	static const string LABEL_WEEK;
	static const string LABEL_ALLDAY;
	static const string LABEL_DUE;

	static const string BLANK_SPACE;
	static const string TAB;
	static const string LEAVE_A_LINE;
	static const string OPEN_SQUARE_BRACKET;
	static const string CLOSE_SQUARE_BRACKET;
	static const string FULL_STOP;
	static const string COMMA;
	static const string DASH_WITH_SPACES;
	static const string DASH_WITHOUT_SPACES;


	
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Private attributes 
* ===================================================================================================================================================================
*/
private:
	vector<Event> _normalEvents;
	vector<Event> _floatingEvents;
	vector<Event> _feedbackEvents;
	vector<tm> _tempMainDisplayLabel;

	int _newID;
	string _weekMonthOrNothing;

	vector<EVENT_STRING> _mainDisplayStrings;
	string _mainDisplayLabel;
	vector<EVENT_STRING> _floatingDisplayStrings;
	vector<string> _feedbackDisplayStrings;
	vector<string> _errorStrings;
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Public getters & respective APIs
* ===================================================================================================================================================================
*/
public:
	//constructor
	LogicUpdater();
	
	//WJ
	//Getters for extracting information when setting/updating
	vector<Event> getNormalEvents();
	vector<Event> getFloatingEvents();
	vector<Event> getFeedbackEvents();
	
	int getTotalNumEvents();
	int getTotalFloatingEvents();
	int getTotalNormalEvents();

	int getIDFromIndex(int index);
	string getNameFromIndex (int index);
	int getIDFromName(string name);
	int getNewID();
	bool getIsFloatingFromID(int id);
	Event getEventFromID(int id);

	//YK
	//Getters for extracting information to display
	vector<EVENT_STRING> getMainDisplayStrings();
	vector<EVENT_STRING> getFloatingDisplayStrings();
	vector<string> getFeedbackDisplayStrings();
	vector<string> getErrorStrings();
	string getMainDisplayLabel();
	vector<tm> getTempMainDisplayLabel();
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Public setters & respective APIs
* ===================================================================================================================================================================
*/	
	//Pre-condition : vector<tm> label to be of size 2
	//				  Conventionally, id will house the id of a newly-added event, but will take on LogicUpdater::GARBAGE_INT when there is no new event
	//				  weekMonthOrNothing can only contain one of the 3 words (LogicUpdater::WORD_MONTH, LogicUpdater::WORD_WEEK, or empty)
	//This function is the single point assessed by the setter to updated the information to be displayed to user
	//Information passed into this function will be processed and stored in 2 forms in the respective private attribute of this Class
	void setAllEvents (vector<Event> normalEvents,vector<Event> floatingEvents,string feedback, vector<tm> label, int id, string weekMonthOrNothing);

	//Pre-condition : None
	//This function is the single point assessed by the setter to updated the feedback to be displayed
	//[WARNING - This function is purely to update the feedback only. It is being used in the case where only feedback required update which the other information
	//remain the same]
	//[WARNING - Empty feedbackstring will be ignored and recorded]
	void setFeedbackStrings(string newFeedback);
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Intermediate supporting functions that are invoked by the Public setters 
* The main roles of these functions is to update the private attributes of these classes correctly
* These functions are asssisted by the Universal basic supporting functions
* ===================================================================================================================================================================
*/
	void setFloatingEvents(vector<Event> events);

	//Pre-condition : _floatingEvents to be correctly set
	//Converts the newly updated _floatingEvents into and stored as EVENT_STRING form
	void floatingEventsToString();

	//Pre-condition: Dates passed in cannot be the same
	//[WARNING - start date must be on the left & end date on the right] 
	std::string setMultipleDaysString(tm,tm);

	//Pre-condition : Size of vector must be 2
	void setMainDisplayLabel (vector<tm> label);

	void setWeekMonthOrNothing(string);

	std::string setSingleDayString(tm);

	//Pre-condition : Size of vector<tm> must be 2
	void setNormalEvents(vector<Event> events,vector<tm> label);
	
	void normalEventsToString();

	std::string setMarkerEventString(Event, int);

	std::string setNormalEventDateString(Event, int);

	std::string setNormalEventEventString(Event);

	void setIsClash(int,int,int,std::vector<int>);

	//Pre-condition : Vector passed in must be empty
	//This vector will become size 1 containing the NO_EVENTS_MESSAGE
	void setNoEventsMessage(vector<EVENT_STRING>& displayVec);
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Universal basic supporting functions
* ===================================================================================================================================================================
*/
	void initializeEventString(EVENT_STRING &item);

	void initializeTime(tm);

	bool setIsNew(Event);

	//Pre-condition : Size of vector must be 2
	bool isSingleDay(vector<tm>);

	bool isToday(tm);
	
	bool isTomorrow(tm);

	//Pre-condition: Dates passed in to be in 12-hr formatt - e.g. 12:30pm
	bool isAllDay(Event);

	//Pre-condition: start date must be on the left & end date on the right
	bool isDisplayMonth(tm,tm);
	
	bool isFirstDayOfMonth(tm);
	
	bool isLastDayOfMonth(tm);

	bool isDisplayWeek(tm,tm);

	bool isFirstDayOfWeek(tm);

	bool isLastDayOfWeek(tm);

	bool isSameMonth(tm,tm);

	bool isSameYear(tm,tm);

	//Pre-condition: Time pass in must be in 24-hrs formatt - hhmm 
	//Returns time in  12-hr formatt - e.g. 12:30pm
	string intToTime (int);
	
	std::string intToDayOfWeek (int);
	
	std::string intToMonth (int);
	
	std::string intToString(int);

	std::string tmToString(tm);
	
	int getStartTime(Event);
	
	int getEndTime(Event); 

	int countNumDays(tm, tm);
//===================================================================================================================================================================
};

#endif