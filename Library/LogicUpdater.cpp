//@author A0111230J

#include "LogicUpdater.h"

//Variables that cannot be initialized in LogicUpdater.h
const int LogicUpdater::GARBAGE_INT = -12345;
const int LogicUpdater::INVALID_NUMBER = -1;
const int LogicUpdater::ZERO = 0;
const string LogicUpdater::EMPTY_STRING = "";
const int LogicUpdater::SHIFT_BY_ONE = 1;
const int LogicUpdater::MAX_LENGTH_EVENT_NAME = 42;

const string LogicUpdater::SET_FLOATING = "set floating events";
const string LogicUpdater::SET_NORMAL = "set normal events";

const string LogicUpdater::NO_EVENTS_MESSAGE = "Currently no task";
const string LogicUpdater::ADDED_MESSAGE = "added: ";
const string LogicUpdater::EDITED_MESSAGE = "edited: ";
const string LogicUpdater::DELETED_MESSAGE = "deleted: ";
const string LogicUpdater::COMPLETED_MESSAGE = "completed: ";
const string LogicUpdater::UNCOMPLETED_MESSAGE = "uncompleted: ";
const string LogicUpdater::SHOW_MESSAGE = "showing: ";
const string LogicUpdater::SHOWALL_MESSAGE = "showing: all items";
const string LogicUpdater::SHOWALLIMPORTANT_MESSAGE = "showing: all important items";
const string LogicUpdater::SHOWCOMPLETE_MESSAGE = "showing: all completed items";
const string LogicUpdater::SHOWIMPORTANT_MESSAGE = "showing: importance level ";
const string LogicUpdater::EVENT_NOT_FOUND_MESSAGE = " not found";
const string LogicUpdater::PARTIAL_EVENT_FOUND_MESSAGE = " not found, showing partial matches..";
const string LogicUpdater::CHOOSE_EVENT_MESSAGE = "multiple results! please select an index.";
const string LogicUpdater::EVENT_NOT_COMPLETED_MESSAGE = "that event is not yet completed!";
const string LogicUpdater::DONE_EVENT_ERROR_MESSAGE = "sorry, you can't change a completed event :(";
const string LogicUpdater::DEADLINE_EVENT_ERROR_MESSAGE = "deadline events can only happen within 1 day!";
const string LogicUpdater::NEW_DAY_MESSAGE = "-MSmsgjyw-";
const string LogicUpdater::UNDO_MESSAGE = "undo";
const string LogicUpdater::REDO_MESSAGE = "redo";
const string LogicUpdater::NO_MORE_UNDO_MESSAGE = "no commands to undo";
const string LogicUpdater::NO_MORE_REDO_MESSAGE = "no commands to redo";
const string LogicUpdater::FILE_NOT_READ_MESSAGE = "memory corrupted, automatically reverted to last usable state";

const string LogicUpdater::WORD_TODAY = "Today";
const string LogicUpdater::WORD_TOMORROW = "Tomorrow";
const string LogicUpdater::WORD_MONTH = "Month";
const string LogicUpdater::WORD_WEEK = "Week";
const string LogicUpdater::WORD_ALLDAY = "All Day";

const string LogicUpdater::LABEL_TODAY = "[Today]";
const string LogicUpdater::LABEL_TOMORROW = "[Tomorrow]";
const string LogicUpdater::LABEL_MONTH = "[Month]";
const string LogicUpdater::LABEL_WEEK = "[Week]";
const string LogicUpdater::LABEL_ALLDAY = "    All Day    ";
const string LogicUpdater::LABEL_DUE = "*DUE*   ";

const string LogicUpdater::BLANK_SPACE = " " ;
const string LogicUpdater::TAB = "\t";
const string LogicUpdater::LEAVE_A_LINE = "\n";
const string LogicUpdater::OPEN_SQUARE_BRACKET = "[";
const string LogicUpdater::CLOSE_SQUARE_BRACKET = "]";
const string LogicUpdater::FULL_STOP = ".";
const string LogicUpdater::COMMA = ",";
const string LogicUpdater::DASH_WITH_SPACES = " - ";
const string LogicUpdater::DASH_WITHOUT_SPACES = "-";

//constructor
LogicUpdater::LogicUpdater() {
	_normalEvents.clear();
	_floatingEvents.clear();
	_feedbackEvents.clear();

	time_t timeNow;
	tm* tmNow;
	time(&timeNow);
	tmNow = localtime(&timeNow);
	_tempMainDisplayLabel.push_back(*tmNow);
	_tempMainDisplayLabel.push_back(*tmNow);

	_mainDisplayStrings.clear();
	_mainDisplayLabel.clear();
	_floatingDisplayStrings.clear();
	_feedbackDisplayStrings.clear();
}

vector<Event> LogicUpdater::getNormalEvents() {
	return _normalEvents;
}

vector<Event> LogicUpdater::getFloatingEvents() {
	return _floatingEvents;
}

vector<Event> LogicUpdater::getFeedbackEvents() {
	return _feedbackEvents;
}

int LogicUpdater::getTotalNumEvents() {
	
	int normalCount = 0;

	if (_floatingEvents.size() == normalCount && _normalEvents.size() == normalCount) {
		return normalCount;
	}

	for (int i = 0; i < _normalEvents.size(); i++) {
		if (_normalEvents[i].getName() != NEW_DAY_MESSAGE) {
			normalCount++;
		}
	}
	return _floatingEvents.size() + normalCount;
}

int LogicUpdater::getTotalFloatingEvents() {
	return _floatingEvents.size();
}

int LogicUpdater::getTotalNormalEvents() {
	return _normalEvents.size();
}

int LogicUpdater::getIDFromIndex(int index) {
	if (index > getTotalNumEvents()) {
		return INVALID_NUMBER;
	} else {
		if (index <= getTotalFloatingEvents()) {
			return _floatingEvents[index-1].getID();
		} else {
			int normalIndex = index - getTotalFloatingEvents();
			int count = 0;

			while (count != normalIndex) {
				if (_normalEvents[count].getName() == NEW_DAY_MESSAGE) {
					normalIndex++;
				}
				count++;
			}
			count--;

			return _normalEvents[count].getID();
		}
	}
}

string LogicUpdater::getNameFromIndex (int index) {
	if (index > getTotalNumEvents()) {
		return EMPTY_STRING;
	} else {
		if (index <= getTotalFloatingEvents()) {
			return _floatingEvents[index-1].getName();
		} else {
			int normalIndex = index - getTotalFloatingEvents();
			int count = 0;

			while (count != normalIndex) {
				if (_normalEvents[count].getName() == NEW_DAY_MESSAGE) {
					normalIndex++;
				}
				count++;
			}
			count--;

			return _normalEvents[count].getName();
		}
	}
}

int LogicUpdater::getIDFromName(string name) {
	for (int i = 0; i < getTotalFloatingEvents(); i++) {
		if (_floatingEvents[i].getName() == name) {
			return _floatingEvents[i].getID();
		}
	}

	for (int i = 0; i < getTotalNormalEvents(); i++) {
		if (_normalEvents[i].getName() == name) {
			return _normalEvents[i].getID();
		}
	}
	return INVALID_NUMBER;
}

int LogicUpdater::getNewID() {
	return _newID;
}


bool LogicUpdater::getIsFloatingFromID(int id) {
	for (int i = 0; i < getTotalFloatingEvents(); i++) {
		if (_floatingEvents[i].getID() == id) {
			return _floatingEvents[i].getIsFloating();
		}
	}

	for (int i = 0; i < getTotalNormalEvents(); i++) {
		if (_normalEvents[i].getID() == id) {
			return _normalEvents[i].getIsFloating();
		}
	}
}

Event LogicUpdater::getEventFromID(int id) {
	for (int i = 0; i < getTotalFloatingEvents(); i++) {
		if (_floatingEvents[i].getID() == id) {
			return _floatingEvents[i];
		}
	}

	for (int i = 0; i < getTotalNormalEvents(); i++) {
		if (_normalEvents[i].getID() == id) {
			return _normalEvents[i];
		}
	}
}

vector<Event> LogicUpdater::getExactNameMatches(int index, string name) {	
	vector<Event> resultEvents;

	if (index != INVALID_NUMBER) {
		if (index > getTotalNumEvents()) {
			return resultEvents;
		}

		if (index <= getTotalFloatingEvents()) {
			resultEvents.push_back(_floatingEvents[index-1]); 
		} else {
			int normalIndex = index - getTotalFloatingEvents();
			int count = 0;
			
			while (count != normalIndex) {
				if (_normalEvents[count].getName() == NEW_DAY_MESSAGE) {
					normalIndex++;
				}
				count++;
			}
			count--;

			resultEvents.push_back(_normalEvents[count]);
		}
		return resultEvents;
	}

	
	for (unsigned int i = 0; i < getTotalFloatingEvents(); i++) {
		if (_floatingEvents[i].getName() == name) {
			resultEvents.push_back(_floatingEvents[i]);
		}
	}

	
	for (unsigned int i = 0; i < getTotalNormalEvents(); i++) {
		if (_normalEvents[i].getName() == name | _normalEvents[i].getName() == NEW_DAY_MESSAGE) {
			resultEvents.push_back(_normalEvents[i]);
		}
	}

	if (resultEvents.empty()) {
		return resultEvents;
	}
	
	for (unsigned int i = 0; i < resultEvents.size() - 1; i++) {
		if (resultEvents[i].getName() == NEW_DAY_MESSAGE && resultEvents[i + 1].getName() == NEW_DAY_MESSAGE) {
			resultEvents.erase(resultEvents.begin() + i);
		}
	}
	
	return resultEvents;
}

vector<LogicUpdater::EVENT_STRING> LogicUpdater::getMainDisplayStrings() {
	return _mainDisplayStrings;
}

vector<LogicUpdater::EVENT_STRING> LogicUpdater::getFloatingDisplayStrings() {
	return _floatingDisplayStrings;
}

vector<string> LogicUpdater::getFeedbackDisplayStrings() {
	return _feedbackDisplayStrings;
}

vector<string> LogicUpdater::getErrorStrings() {
	return _errorStrings;
}

string LogicUpdater::getMainDisplayLabel() {
	return _mainDisplayLabel;
}

vector<tm> LogicUpdater::getTempMainDisplayLabel() {
	return _tempMainDisplayLabel;
}
//===================================================================================================================================================================
void LogicUpdater::setAllEvents(vector<Event> normalEvents,
vector<Event> floatingEvents, string feedback, vector<tm> label, int id, string weekMonthOrNothing) {
	_newID = id;
	setWeekMonthOrNothing (weekMonthOrNothing);
	setFeedbackStrings(feedback);
	setFloatingEvents(floatingEvents);
	_logger.log(SET_FLOATING + LogicLog::SUCCEEDED);
	setNormalEvents(normalEvents, label);
	_logger.log(SET_NORMAL + LogicLog::SUCCEEDED);
}

void LogicUpdater::setFeedbackStrings(string newFeedback) {
	if (!newFeedback.empty()) {
		_feedbackDisplayStrings.push_back(newFeedback);
	}

	while (_feedbackDisplayStrings.size()>3) {
		_feedbackDisplayStrings.erase(_feedbackDisplayStrings.begin());
	}

	assert (_feedbackDisplayStrings.size()<=3);
}

void LogicUpdater::setFloatingEvents(vector<Event> events) {
	_floatingEvents = events;
	floatingEventsToString();
}

void LogicUpdater::floatingEventsToString() {
	_floatingDisplayStrings.clear();
	

	if (_floatingEvents.empty()) {
		setNoEventsMessage(_floatingDisplayStrings);
	} else {
		for (int i = 0; i < _floatingEvents.size(); i++) {
			EVENT_STRING temp;
			initializeEventString(temp);

			ostringstream outDate;
			outDate << (i + SHIFT_BY_ONE) << FULL_STOP;
			temp.dateString = outDate.str();

			ostringstream outEvent;
			outEvent << _floatingEvents[i].getName();
			temp.eventString = outEvent.str();

			temp.isCompleted = _floatingEvents[i].getIsCompleted();
			temp.importanceLevel = _floatingEvents[i].getImportanceLevel();
			temp.isNew = setIsNew(_floatingEvents[i]);

			_floatingDisplayStrings.push_back(temp);
		}
	}
	assert(_floatingDisplayStrings.size()>=1);
}

std::string LogicUpdater::setMultipleDaysString(tm start,tm end) {
	std::mktime(&start);
	std::mktime(&end);
	
	if(start.tm_year == end.tm_year && start.tm_mon == end.tm_mon){
		assert(start.tm_mday < end.tm_mday);
	} else if(start.tm_year == end.tm_year){
		assert(start.tm_mon <= end.tm_mon);
	} else {
		assert(start.tm_year <= end.tm_year);
	}
	
	std::string multipleDaysString = "";

	if (isDisplayMonth(start,end)) {
		string commandMonth = LABEL_MONTH + BLANK_SPACE;
		multipleDaysString += commandMonth;
	} else if (isDisplayWeek(start,end)) {
		string commandWeek = LABEL_WEEK + BLANK_SPACE;
		multipleDaysString += commandWeek;
	}

	multipleDaysString += tmToString(start);

	if (start.tm_year != end.tm_year) {
		string startYear = intToString(start.tm_year + 1900);
		multipleDaysString += BLANK_SPACE + startYear;
	}

	multipleDaysString += DASH_WITH_SPACES;

	multipleDaysString += tmToString(end);

	string endYear = intToString(end.tm_year + 1900);
	multipleDaysString += BLANK_SPACE +endYear;

	return multipleDaysString;
}

void LogicUpdater::setMainDisplayLabel (vector<tm> label) {
	assert(label.size()==2);
	std::mktime(&label[0]);
	std::mktime(&label[1]);

	_mainDisplayLabel.clear();

	if (isSingleDay(label) && isToday (label[0])) {
		string commandToday = LABEL_TODAY + BLANK_SPACE;
		std::string dateInString = setSingleDayString(label[0]);
		_mainDisplayLabel += commandToday + dateInString;
	} else if (isSingleDay(label) && isTomorrow (label[0])) {
		string commandTomorrow = LABEL_TOMORROW + BLANK_SPACE;
		std::string dateInString = setSingleDayString(label[0]);
		_mainDisplayLabel += commandTomorrow + dateInString;
	} else if (isSingleDay(label)){
		std::string dateInString = setSingleDayString(label[0]);
		_mainDisplayLabel += dateInString;
	} else {
		_mainDisplayLabel = setMultipleDaysString(label[0],label[1]);
	}
}

void LogicUpdater::setWeekMonthOrNothing(string identity) {
	assert( identity == WORD_WEEK || identity == WORD_MONTH || identity == "");

	_weekMonthOrNothing = identity;
}

std::string LogicUpdater::setSingleDayString(tm label) {
	std::mktime(&label);

	string dayOfMonth = intToString(label.tm_mday);
	string month = intToMonth(label.tm_mon);
	string dayOfWeek = intToDayOfWeek(label.tm_wday);
	string year = intToString(label.tm_year + 1900);
	string dateInString = dayOfMonth + BLANK_SPACE + month + BLANK_SPACE + year + COMMA + BLANK_SPACE + dayOfWeek;
	return dateInString;
}

void LogicUpdater::setNormalEvents(vector<Event> events,vector<tm> label) {
	_normalEvents = events;
	_tempMainDisplayLabel = label;
	setMainDisplayLabel(label);
	normalEventsToString();
}

void LogicUpdater::normalEventsToString() {
	_mainDisplayStrings.clear();

	if (_normalEvents.empty()) {
		setNoEventsMessage(_mainDisplayStrings);
		return;
	}

	std::vector<int> indexOfMarkers;
	int newEventStartTime = ZERO;
	int newEventEndTime = ZERO;
	int newEventIndex = INVALID_NUMBER;
	int indexForNormalEvents = getTotalFloatingEvents();

	for (int i = 0; i < _normalEvents.size(); i++) {
		EVENT_STRING toBePushed;
		initializeEventString(toBePushed);

		//Set New Day Marker
		if (_normalEvents[i].getName() == NEW_DAY_MESSAGE) {	
			indexOfMarkers.push_back(i);

			toBePushed.isMarker = true;
			toBePushed.eventString = setMarkerEventString(_normalEvents[i],i);

			//isClash is set between 2 markers & when there is a new event
			if ( indexOfMarkers.size() >= 2 && newEventIndex != INVALID_NUMBER ) {
				setIsClash(newEventStartTime, newEventEndTime, newEventIndex,indexOfMarkers);
				newEventIndex = INVALID_NUMBER;
			}
		} else {
			//Set normal event
			toBePushed.isNew = setIsNew(_normalEvents[i]);
			toBePushed.isCompleted = _normalEvents[i].getIsCompleted();
			toBePushed.importanceLevel = _normalEvents[i].getImportanceLevel();
			toBePushed.dateString = setNormalEventDateString(_normalEvents[i],++indexForNormalEvents);
			toBePushed.eventString = setNormalEventEventString(_normalEvents[i]);			
		}

		if (toBePushed.isNew == true) {
			newEventStartTime = getStartTime(_normalEvents[i]);
			newEventEndTime = getEndTime(_normalEvents[i]);
			newEventIndex = i;
		}

		_mainDisplayStrings.push_back(toBePushed);
	}

	//isClash is set after the last event too
	indexOfMarkers.push_back(_normalEvents.size());
	
	if ( indexOfMarkers.size() >= 2 && newEventIndex != INVALID_NUMBER ) {
		setIsClash(newEventStartTime, newEventEndTime, newEventIndex,indexOfMarkers);
		newEventIndex = INVALID_NUMBER;
	}

	assert(_mainDisplayStrings.size()>=1);
}

std::string LogicUpdater::setMarkerEventString(Event marker, int index) {
	ostringstream out;

	assert(index>=0);
	if (index != 0) {
		out << LEAVE_A_LINE;
	}

	out << OPEN_SQUARE_BRACKET;
	out << marker.getStartDate().tm_mday;
	out << BLANK_SPACE;

	int monthInt = marker.getStartDate().tm_mon;
	out << intToMonth(monthInt);

	out << BLANK_SPACE;
	out << marker.getStartDate().tm_year + 1900;

	out << COMMA + BLANK_SPACE;

	int dayOfWeekInt = marker.getStartDate().tm_wday;
	out << intToDayOfWeek(dayOfWeekInt);

	out << CLOSE_SQUARE_BRACKET;
	out << "==============================================================";
	out << LEAVE_A_LINE;

	return out.str();
}

std::string LogicUpdater::setNormalEventDateString(Event eventToBeSet, int eventIndex) {
	assert(eventIndex >= 1);
	ostringstream outDate;
	
	outDate << eventIndex << ".";
	outDate << TAB;

	outDate << OPEN_SQUARE_BRACKET;
	if (eventToBeSet.getIsDeadline()) {
		outDate << LABEL_DUE;
		int endTime = getStartTime(eventToBeSet);
		outDate << intToTime(endTime);
	} else if (isAllDay(eventToBeSet)) {
		outDate << LABEL_ALLDAY;
	} else {
		int startTime = getStartTime(eventToBeSet);
		outDate << intToTime(startTime);
		outDate << DASH_WITHOUT_SPACES;
		int endTime = getEndTime(eventToBeSet);
		outDate << intToTime(endTime);
	}
			
	outDate << CLOSE_SQUARE_BRACKET;
	outDate << TAB;		
	return outDate.str();
}

std::string LogicUpdater::setNormalEventEventString(Event eventToBeSet) {
	
	ostringstream outEvent;

	std::string nameOfEvent = eventToBeSet.getName();

	while(nameOfEvent.size() > MAX_LENGTH_EVENT_NAME) {
		outEvent << nameOfEvent.substr(0,MAX_LENGTH_EVENT_NAME);
		outEvent << LEAVE_A_LINE;
		outEvent << TAB + TAB + TAB + TAB + TAB;
		nameOfEvent = nameOfEvent.substr(MAX_LENGTH_EVENT_NAME);
	}

	outEvent << nameOfEvent;
	return outEvent.str();	
}

void LogicUpdater:: setIsClash(int newEventStartTime, int newEventEndTime, int newEventIndex, std::vector<int> indexOfNewMarker) {
	assert(indexOfNewMarker.size() >=2);

	bool setNewItemClash = false;

	for (int i = indexOfNewMarker[indexOfNewMarker.size() - 2] + 1; i < indexOfNewMarker[indexOfNewMarker.size() - 1]; i++) {
		int checkEventStartTime = getStartTime (_normalEvents[i]);
		int checkEventEndTime = getEndTime (_normalEvents[i]);

		if (checkEventStartTime < newEventStartTime && newEventStartTime < checkEventEndTime && _normalEvents[i].getID() != _newID) {
				_mainDisplayStrings[i].isClash = true;
				setNewItemClash = true;
		}
		
		if (checkEventStartTime < newEventEndTime && newEventEndTime < checkEventEndTime && _normalEvents[i].getID() != _newID) {
				_mainDisplayStrings[i].isClash = true;
				setNewItemClash = true;
		}
		
		if (newEventStartTime < checkEventStartTime  && checkEventStartTime < newEventEndTime && _normalEvents[i].getID() != _newID) {
				_mainDisplayStrings[i].isClash = true;
				setNewItemClash = true;
		}

		if (newEventStartTime < checkEventEndTime && checkEventEndTime < newEventEndTime && _normalEvents[i].getID() != _newID){
				_mainDisplayStrings[i].isClash = true;
				setNewItemClash = true;
		}

		if (checkEventStartTime == newEventStartTime && checkEventEndTime == newEventEndTime && _normalEvents[i].getID() != _newID) {
				_mainDisplayStrings[i].isClash = true;
				setNewItemClash = true;
		}
	}
		
		if (setNewItemClash) {
			_mainDisplayStrings[newEventIndex].isClash = true;
		}
}


void LogicUpdater::setNoEventsMessage(vector<EVENT_STRING>& displayVec) {
	assert(displayVec.empty());

	EVENT_STRING noEvent;
	noEvent.dateString = "";
	noEvent.eventString = NO_EVENTS_MESSAGE;
	noEvent.isNew = false;
	noEvent.isClash= false;
	noEvent.isMarker = false;
	noEvent.isCompleted = false;
	noEvent.importanceLevel= 0;
	displayVec.push_back(noEvent);
}
//===================================================================================================================================================================

void LogicUpdater::initializeEventString(LogicUpdater::EVENT_STRING &item) {
	item.dateString = "";
	item.eventString = "";
	item.isNew = false;
	item.isClash = false;
	item.isMarker = false;
	item.isCompleted = false;
	item.importanceLevel = 0;
}

void LogicUpdater::initializeTime(tm date) {
	date.tm_hour = 0;
	date.tm_min = 0;
	date.tm_sec = 0;
}


bool LogicUpdater::setIsNew(Event toBeSet) {
	bool isNew = false;

	if (toBeSet.getID() == _newID) {
		isNew = true;
	}
	return isNew;
}

bool LogicUpdater::isSingleDay(vector<tm> label) {
	assert(label.size()==2);
	std::mktime(&label[0]);
	std::mktime(&label[1]);

	bool isSingle = false;
	if (label[0].tm_mday == label[1].tm_mday && label[0].tm_mon == label[1].tm_mon && label[0].tm_year == label[1].tm_year) {
		isSingle = true;
	}

	return isSingle;
}

bool LogicUpdater::isToday(tm date) {
	bool isDateToday = false;

	std::mktime(&date);

	//Initialize date to today
	time_t now = time(0);
	struct tm today = *localtime(&now);

	if (today.tm_mday == date.tm_mday && today.tm_mon == date.tm_mon && today.tm_year == date.tm_year) {
		isDateToday = true;
	}

	return isDateToday;
}

bool LogicUpdater::isTomorrow(tm date) {
	bool isDateTomorrow = false;

	std::mktime(&date);

	//Initialize date to tomorrow
	time_t now = time(0);
	struct tm tomorrow = *localtime(&now);
	tomorrow.tm_mday ++;
	mktime(&tomorrow);

	if (tomorrow.tm_mday == date.tm_mday && tomorrow.tm_mon == date.tm_mon && tomorrow.tm_year == date.tm_year) {
		isDateTomorrow = true;
	}

	return isDateTomorrow;
}

bool LogicUpdater::isAllDay(Event eventToDisplay) {
	bool isAllDayEvent = false;
	
	int startTime = getStartTime(eventToDisplay);
	string startTimeInString = intToTime(startTime);

	int endTime = getEndTime(eventToDisplay);
	string endTimeInString = intToTime(endTime);

	if (startTimeInString == "00:00am"  && endTimeInString == "11:59pm") {
		isAllDayEvent = true;
	}

	return isAllDayEvent;
}

bool LogicUpdater::isDisplayMonth(tm frontDate,tm backDate) {
	std::mktime(&frontDate);
	std::mktime(&backDate);

	if(frontDate.tm_year == backDate.tm_year && frontDate.tm_mon == backDate.tm_mon){
		assert(frontDate.tm_mday < backDate.tm_mday);
	} else if(frontDate.tm_year == backDate.tm_year){
		assert(frontDate.tm_mon <= backDate.tm_mon);
	} else {
		assert(frontDate.tm_year <= backDate.tm_year);
	}


	bool isMonth = false;

	if (isFirstDayOfMonth(frontDate) && isLastDayOfMonth(backDate) && isSameMonth(frontDate,backDate) && isSameYear(frontDate,backDate)) {
		isMonth = true;
	} else if (_weekMonthOrNothing == WORD_MONTH) {
		isMonth = true;
	}

	return isMonth;
}

bool LogicUpdater::isFirstDayOfMonth(tm frontDate) {
	bool isFirstDay = false;
	
	std::mktime(&frontDate);

	int monthBefore = frontDate.tm_mon;

	assert(frontDate.tm_mday>=1 && frontDate.tm_mday<=31); 
	assert(frontDate.tm_mon>=0 && frontDate.tm_mon<=11);
	assert(frontDate.tm_year<3000 && frontDate.tm_year>70);

	frontDate.tm_mday--;
	std::mktime(&frontDate);
	int monthAfter = frontDate.tm_mon;

	if (monthBefore != monthAfter) {
		isFirstDay = true;
	}

	return isFirstDay;
}

bool LogicUpdater::isLastDayOfMonth(tm backDate) {
	bool isLastDay = false;

	std::mktime(&backDate);
	
	int monthBefore = backDate.tm_mon;

	assert(backDate.tm_mday>=1 && backDate.tm_mday<=31); 
	assert(backDate.tm_mon>=0 && backDate.tm_mon<=11);
	assert(backDate.tm_year<3000 && backDate.tm_year>70);


	backDate.tm_mday++;
	std::mktime(&backDate);
	int monthAfter = backDate.tm_mon;

	if (monthBefore != monthAfter) {
		isLastDay = true;
	}

	return isLastDay;
}

bool LogicUpdater::isDisplayWeek(tm frontDate,tm backDate) {
	bool isWeek  = false;

	std::mktime(&frontDate);
	std::mktime(&backDate);

	if (isFirstDayOfWeek(frontDate) && isLastDayOfWeek(backDate) && countNumDays(frontDate,backDate) == 6 ) {
		isWeek = true;
	}

	if (_weekMonthOrNothing == WORD_WEEK) {
		isWeek = true;
	}

	return isWeek;
}

bool LogicUpdater::isFirstDayOfWeek(tm frontDate) {
	std::mktime(&frontDate);
	assert(frontDate.tm_wday>=0 && frontDate.tm_wday<=6);

	bool isFirstDay = false;

	if (frontDate.tm_wday == 0) {
		isFirstDay = true;
	}

	return isFirstDay;
}

bool LogicUpdater::isLastDayOfWeek(tm backDate) {
	std::mktime(&backDate);
	assert(backDate.tm_wday>=0 && backDate.tm_wday<=6);

	bool isLastDay = false;

	if (backDate.tm_wday == 6) {
		isLastDay = true;
	}

	return isLastDay;
}

bool LogicUpdater::isSameMonth(tm frontDate,tm backDate) {
	std::mktime(&frontDate);
	std::mktime(&backDate);

	bool sameMonth = false;

	if (frontDate.tm_mon == backDate.tm_mon) {
		sameMonth = true;
	}

	return sameMonth;
}

bool LogicUpdater::isSameYear(tm frontDate,tm backDate) {
	std::mktime(&frontDate);
	std::mktime(&backDate);

	bool sameYear = false;

	if (frontDate.tm_year == backDate.tm_year) {
		sameYear = true;
	}

	return sameYear;
}

std::string LogicUpdater::intToTime (int timeInInt) {
	int hours;
	int minutes;
	bool afterTwelve = false;
	std::ostringstream oss;
	hours = timeInInt/100;
	minutes = timeInInt%100;

	assert(0<=hours && hours<=23);
	assert(0<=minutes && minutes<=59);

	if (hours > 12) {
		hours = hours - 12;
		afterTwelve = true;
	} else if (hours == 12) {
		afterTwelve = true;
	}

	if (hours >= 10){
		oss << hours;
	} else{
		oss << "0";
		oss << hours;
	}

	oss << ":";

	if (minutes >= 10) {
		oss << minutes;
	} else {
		oss << "0";
		oss << minutes;
	}

	if (afterTwelve) {		
		oss << "pm";
	} else {
		oss << "am";
	}
	
	return oss.str();
}

std::string LogicUpdater::intToDayOfWeek (int dayInNum) {
	if (dayInNum == 0) {
		return "Sunday";
	} else if (dayInNum == 1) {
		return "Monday";
	} else if (dayInNum == 2) {
		return "Tuesday";
	} else if (dayInNum == 3) {
		return "Wednesday";
	} else if (dayInNum == 4) {
		return "Thursday";
	} else if (dayInNum == 5) {
		return "Friday";
	} else if (dayInNum == 6) {
		return "Saturday";
	} else {
		return "Invalid day";
	}
}

std::string LogicUpdater::intToMonth (int monthInNum) {
	if (monthInNum == 0) {
		return "January";
	} else if (monthInNum  == 1) {
		return "Feburary";
	} else if (monthInNum  == 2) {
		return "March";
	} else if (monthInNum  == 3) {
		return "April";
	} else if (monthInNum  == 4) {
		return "May";
	} else if (monthInNum  == 5) {
		return "June";
	} else if (monthInNum  == 6) {
		return "July";
	} else if (monthInNum  == 7) {
		return "August";
	} else if (monthInNum  == 8) {
		return "September";
	} else if (monthInNum  == 9) {
		return "October";
	} else if (monthInNum  == 10) {
		return "November";
	} else if (monthInNum  == 11) {
		return "December";
	} else {
		return "Invalid month";
	}
}

std::string LogicUpdater::tmToString(tm date){
	std::mktime(&date);

	assert(date.tm_mday>=1 && date.tm_mday<=31); 
	assert(date.tm_mon>=0 && date.tm_mon<=11);
	assert(date.tm_year<3000 && date.tm_year>70);

	string startDayOfMonth = intToString(date.tm_mday);
	string startMonth = intToMonth(date.tm_mon);

	return startDayOfMonth + BLANK_SPACE + startMonth;
}

std::string LogicUpdater::intToString(int num) {
	assert(num>=0);

	std::string outString;
	std::ostringstream oss;
	oss << num;
	return oss.str();
}

int LogicUpdater:: getStartTime(Event toGet) {
	return toGet.getStartDate().tm_hour*100 + toGet.getStartDate().tm_min;
}

int LogicUpdater:: getEndTime(Event toGet) {
	return toGet.getEndDate().tm_hour*100 + toGet.getEndDate().tm_min;
}

int LogicUpdater::countNumDays(tm startDay, tm endDay) {
	initializeTime(startDay);
	initializeTime(endDay);
	std::time_t start = std::mktime(&startDay);
	std::time_t end = std::mktime(&endDay);

	int dayDifference = std::difftime(end,start)/(60*60*24);

	return dayDifference;
}




