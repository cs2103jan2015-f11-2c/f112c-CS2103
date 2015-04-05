#include "Command.h"


const int Command::INVALID_NUMBER = -1;
const int Command::SIZE_ZERO = 0;
const int Command::SIZE_ONE = 1;
const int Command::SIZE_TWO = 2;



vector<Event> Command::getEventVector() {
	return eventsToShow;
}

bool Command::getIsFloating() {
	return isFloating;
}

bool Command::getIsExecuted() {
	return isExecuted;
}

bool Command::getIsUndoable() {
	return isUndoable;
}

int Command::getNumEvents(vector<Event> eventVec) {
	//remove marker events
	for (unsigned int i = 0; i < eventVec.size(); i++) {
		if (eventVec[i].getID() < 0) {
			eventVec.erase(eventVec.begin() + i);
		}
	}

	int count = SIZE_ZERO;
	vector<int> idVec;

	//only count events with different ID
	for (unsigned int i = 0; i < eventVec.size(); i++) {
		if ( find(idVec.begin(), idVec.end(), eventVec[i].getID()) == idVec.end() ) {
			idVec.push_back(eventVec[i].getID());
			count++;
		}
	}
	return count;
}

Event Command::getEventFromID(vector<Event> eventVec, int id) {
	for (unsigned int i = 0; i < eventVec.size(); i++) {
		if (eventVec[i].getID() == id) {
			return eventVec[i];
		}
	}
	return createInvalidEvent();
}

void Command::checkPartialMatches(int numResults, vector<Event> tempEvents) {
	switch (numResults) {
		case SIZE_ZERO: { //no partial match
			eventsToShow.push_back(createInvalidEvent());
			isExecuted = true;
			return;
						}

		default: { //at least 1 partial match
			eventsToShow = tempEvents;
			isExecuted = false;
			return;
				 }
	}
}

void Command::chooseExactMatches(Event& userEvent) {
	eventsToShow = eventFacade->findNameOccurrence(userEvent.getName());
	userEvent = createInvalidEvent();
	isExecuted = false;
}

Event Command::createInvalidEvent() {
	Event invalidEvent;
	invalidEvent.setID(INVALID_NUMBER);
	return invalidEvent;
}




//Add Command
AddCommand::AddCommand(EventFacade* eventStorage, Event e) {
	eventFacade = eventStorage;
	userEvent = e;
	isExecuted = false;
	isUndoable = true;
}

void AddCommand::execute() {
	eventsToShow = eventFacade->addEvent(userEvent);
	isFloating = userEvent.getIsFloating();
	isExecuted = true;
	logger.log(LogicLog::EXECUTED + LogicLog::ADD);
}

Event AddCommand::getEvent() {
	return userEvent;
}

void AddCommand::undo() {
	eventsToShow = eventFacade->deleteEvent(userEvent.getID(), userEvent);
}




//Complete Command
CompleteCommand::CompleteCommand(EventFacade* eventStorage, int eventID, Event e) {
	eventFacade = eventStorage;
	id = eventID;
	userEvent = e;
	isExecuted = false;
	isUndoable = true;
}

void CompleteCommand::execute() {
	//if id found in current display, delete immediately
	if (id > 0) {
		completeImmediately();
		logger.log(LogicLog::EXECUTED + LogicLog::COMPLETE);
		return;
	}

	vector<Event> tempEvents = eventFacade->findNameExact(userEvent.getName());
	int numResults = getNumEvents(tempEvents);

	switch (numResults) {
	case SIZE_ZERO: { //no exact match
		logger.log(LogicLog::CASE_0 + LogicLog::COMPLETE);
		userEvent = createInvalidEvent();
		tempEvents = eventFacade->findNameOccurrence(userEvent.getName());
		numResults = getNumEvents(tempEvents);

		checkPartialMatches(numResults, tempEvents);
		return;
					}

	case SIZE_ONE: { //1 exact match
		logger.log(LogicLog::CASE_1 + LogicLog::COMPLETE);
		completeExact(tempEvents);
		logger.log(LogicLog::EXECUTED + LogicLog::COMPLETE);
		return;
				   }

	default: { //more than 1 exact match
		logger.log(LogicLog::DEFAULT + LogicLog::COMPLETE);
		chooseExactMatches(userEvent);
		return;
			 }
	}
}

Event CompleteCommand::getEvent() {
	return userEvent;
}

void CompleteCommand::undo() {
	if (userEvent.getID() != INVALID_NUMBER) {
		eventsToShow = eventFacade->uncompleteEvent(userEvent.getID(), userEvent);
	}
}

void CompleteCommand::completeImmediately() {
	isFloating = userEvent.getIsFloating();
	eventsToShow = eventFacade->completeEvent(id, userEvent);
	isExecuted = true;
}

void CompleteCommand::completeExact(vector<Event> tempEvents) {
	if (tempEvents.size() == SIZE_ONE) { //1 floating match => event will be at index 0
		isFloating = true;
		userEvent = tempEvents[0];
		eventsToShow = eventFacade->completeEvent(tempEvents[0].getID(), tempEvents[0]);
	} else { //1 normal match => event will be at index 1
		isFloating = false;
		userEvent = tempEvents[1];
		eventsToShow = eventFacade->completeEvent(tempEvents[1].getID(), tempEvents[1]);
	}
	isExecuted = true;
}




//Delete Command
DeleteCommand::DeleteCommand(EventFacade* eventStorage, int eventID, Event e) {
	eventFacade = eventStorage;
	id = eventID;
	userEvent = e;
	isExecuted = false;
	isUndoable = true;
}

void DeleteCommand::execute() {
	//if id found in current display, delete immediately
	if (id > SIZE_ZERO) {
		deleteImmediately();
		logger.log(LogicLog::EXECUTED + LogicLog::DELETE);
		return;
	}

	vector<Event> tempEvents = eventFacade->findNameExact(userEvent.getName());
	int numResults = getNumEvents(tempEvents);

	switch (numResults) {
	case SIZE_ZERO: { //no exact match
		logger.log(LogicLog::CASE_0 + LogicLog::DELETE);
		tempEvents = eventFacade->findNameOccurrence(userEvent.getName());
		userEvent = createInvalidEvent();
		numResults = getNumEvents(tempEvents);

		checkPartialMatches(numResults, tempEvents);
		return;
					}

	case SIZE_ONE: { //1 exact match
		logger.log(LogicLog::CASE_1 + LogicLog::DELETE);
		deleteExact(tempEvents);
		logger.log(LogicLog::EXECUTED + LogicLog::DELETE);
		return;
				   }

	default: { //more than 1 exact match
		logger.log(LogicLog::DEFAULT + LogicLog::DELETE);
		chooseExactMatches(userEvent);
		return;
			 };
	};
}

Event DeleteCommand::getEvent() {
	return userEvent;
}

void DeleteCommand::undo() {
	if (userEvent.getID() != INVALID_NUMBER) {
		eventsToShow = eventFacade->addEvent(userEvent);
	}
}

void DeleteCommand::deleteImmediately() {
	isFloating = userEvent.getIsFloating();
	eventsToShow = eventFacade->deleteEvent(id, userEvent);
	isExecuted = true;
}

void DeleteCommand::deleteExact(vector<Event> tempEvents) {
	if (tempEvents.size() == SIZE_ONE) { //1 floating match => event will be at index 0
		isFloating = true;
		userEvent = tempEvents[0];
		eventsToShow = eventFacade->deleteEvent(tempEvents[0].getID(), tempEvents[0]);
	} else { //1 normal match => event will be at index 1
		isFloating = false;
		userEvent = tempEvents[1];
		eventsToShow = eventFacade->deleteEvent(tempEvents[1].getID(), tempEvents[1]);
	}
	isExecuted = true;
}




//Edit Command
EditCommand::EditCommand(EventFacade* eventStorage, int eventID, Event toEdit, Event edited) {
	eventFacade = eventStorage;
	id = eventID;
	eventToEdit = toEdit;
	editedEvent = edited;
	isExecuted = false;
	isUndoable = true;
}

void EditCommand::execute() {
	if (id > 0) {
		editImmediately();
		logger.log(LogicLog::EXECUTED + LogicLog::EDIT);
		return;
	}

	vector<Event> tempEvents = eventFacade->findNameExact(eventToEdit.getName());
	int numResults = getNumEvents(tempEvents);

	switch (numResults) {
	case SIZE_ZERO: { //no exact match
		logger.log(LogicLog::CASE_0 + LogicLog::EDIT);
		eventToEdit = createInvalidEvent();
		tempEvents = eventFacade->findNameOccurrence(eventToEdit.getName());
		numResults = tempEvents.size();
		
		checkPartialMatches(numResults, tempEvents);
		return;
					}

	case SIZE_ONE: { //1 exact match
		logger.log(LogicLog::CASE_1 + LogicLog::EDIT);
		editExact(tempEvents);
		logger.log(LogicLog::EXECUTED + LogicLog::EDIT);
		return;
				   }

	default:{ //more than 1 exact match
		logger.log(LogicLog::DEFAULT + LogicLog::EDIT);
		chooseExactMatches(eventToEdit);
		return;
			}
	}

}

Event EditCommand::getEvent() {
	return eventToEdit;
}

void EditCommand::undo() {
	if (eventToEdit.getID() != INVALID_NUMBER) {
		eventFacade->deleteEvent(editedEvent.getID(), editedEvent);
		eventsToShow = eventFacade->addEvent(eventToEdit);
	}
}

void EditCommand::editImmediately() {
	isFloating = eventToEdit.getIsFloating();
	eventsToShow = eventFacade->editEvent(id, eventToEdit, editedEvent);
	editedEvent = getEventFromID(eventsToShow, id);
	isExecuted = true;
}

void EditCommand::editExact(vector<Event> tempEvents) {
	if (tempEvents.size() == 1) { //1 floating match => event will be at index 0
		isFloating = true;
		eventToEdit = tempEvents[0];
		eventsToShow = eventFacade->editEvent(eventToEdit.getID(), eventToEdit, editedEvent);
	} else { //1 normal match => event will be at index 1
		isFloating = false;
		eventToEdit = tempEvents[1];
		eventsToShow = eventFacade->editEvent(eventToEdit.getID(), eventToEdit, editedEvent);
	}
	editedEvent = getEventFromID(eventsToShow, eventToEdit.getID());
	isExecuted = true;
}




//Search Command
SearchCommand::SearchCommand(EventFacade* eventStorage, string s) {
	eventFacade = eventStorage;
	searchString = s;
	isUndoable = false;
}

void SearchCommand::execute() {
	eventsToShow = eventFacade->findNameOccurrence(searchString);
	logger.log(LogicLog::EXECUTED + LogicLog::SEARCH);
}

Event SearchCommand::getEvent() {
	return createInvalidEvent();
}

void SearchCommand::undo() {
}




//Show Command
ShowCommand::ShowCommand(EventFacade* eventStorage, Event e) {
	eventFacade = eventStorage;
	eventRangeToShow = e;
	isUndoable = false;
}

void ShowCommand::execute() {
	eventsToShow = eventFacade->showDates(eventRangeToShow);
	logger.log(LogicLog::EXECUTED + LogicLog::SHOW);
}

Event ShowCommand::getEvent() {
	return eventRangeToShow;
}

void ShowCommand::undo() {
}




//Show All Command
ShowAllCommand::ShowAllCommand(EventFacade* eventStorage) {
	eventFacade = eventStorage;
	isUndoable = false;
}

void ShowAllCommand::execute() {
	vector<Event> floating = eventFacade->showAllFloatingEvents();
	vector<Event> normal = eventFacade->showAllNormalEvents();
	floating.insert(floating.end(), normal.begin(), normal.end());

	eventsToShow = floating;
	logger.log(LogicLog::EXECUTED + LogicLog::SHOWALL);
}

Event ShowAllCommand::getEvent() {
	return createInvalidEvent();
}

void ShowAllCommand::undo() {
}




//Show All Important Command
ShowAllImportantCommand::ShowAllImportantCommand(EventFacade* eventStorage) {
	eventFacade = eventStorage;
	isUndoable = false;
}

void ShowAllImportantCommand::execute() {
	eventsToShow = eventFacade->findAllImportance();
	logger.log(LogicLog::EXECUTED + LogicLog::SHOWALLIMPORTANT);
}

Event ShowAllImportantCommand::getEvent() {
	return createInvalidEvent();
}

void ShowAllImportantCommand::undo() {
}




//Show Completed Command
ShowCompletedCommand::ShowCompletedCommand(EventFacade* eventStorage) {
	eventFacade = eventStorage;
	isUndoable = false;
}

void ShowCompletedCommand::execute() {
	vector<Event> floating = eventFacade->showAllFloatingCompleted();
	vector<Event> normal = eventFacade->showAllNormalCompleted();
	floating.insert(floating.end(), normal.begin(), normal.end());

	eventsToShow = floating;
	logger.log(LogicLog::EXECUTED + LogicLog::SHOWCOMPLETED);
}

Event ShowCompletedCommand::getEvent() {
	return createInvalidEvent();
}

void ShowCompletedCommand::undo() {
}




//Show Due Command
ShowDueCommand::ShowDueCommand(EventFacade* eventStorage) {
	eventFacade = eventStorage;
	isUndoable = false;
}

void ShowDueCommand::execute() {
}

Event ShowDueCommand::getEvent() {
	return createInvalidEvent();
}

void ShowDueCommand::undo() {
}




//Show Float Command
ShowFloatCommand::ShowFloatCommand(EventFacade* eventStorage) {
	eventFacade = eventStorage;
	isUndoable = false;
}

void ShowFloatCommand::execute() {
	eventsToShow = eventFacade->showAllFloatingEvents();
	isFloating = true;
	logger.log(LogicLog::EXECUTED + LogicLog::SHOWFLOAT);
}

Event ShowFloatCommand::getEvent() {
	return createInvalidEvent();
}

void ShowFloatCommand::undo() {
}




//Show Importance Command
ShowImportanceCommand::ShowImportanceCommand(EventFacade* eventStorage, int importance) {
	eventFacade = eventStorage;
	importanceLevel = importance;
	isUndoable = false;
}

void ShowImportanceCommand::execute() {
	eventsToShow = eventFacade->findLevelImportance(importanceLevel);
	logger.log(LogicLog::EXECUTED + LogicLog::SHOWIMPORTANCE);
}

Event ShowImportanceCommand::getEvent() {
	return createInvalidEvent();
}

void ShowImportanceCommand::undo() {
}




//Null Command
NullCommand::NullCommand() {
	isExecuted = false;
	isUndoable = false;
	eventsToShow.clear();
}

void NullCommand::execute() {
}

Event NullCommand::getEvent() {
	return createInvalidEvent();
}

void NullCommand::undo() {
}