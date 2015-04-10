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
		if (eventVec[i].getID() < SIZE_ZERO) {
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
			if (eventVec[i].getIsFloating()) {
				return eventVec[i];
			} else {
				return eventFacade->findEventWithID(id);
			}
		}
	}
	return createInvalidEvent();
}

//if userEvent dates fall within the dates currently being shown, maintain the current date range being shown, otherwise use the date range of userEvent
vector<Event> Command::getShowEventVector(Event userEvent, vector<tm> currentShowingTM) {
	assert(currentShowingTM.size() == SIZE_TWO);
	
	vector<tm> userTM, tmRangeToShow;
	userTM.push_back(userEvent.getStartDate());
	userTM.push_back(userEvent.getEndDate());
	
	if (userTM[SIZE_ZERO].tm_year >= currentShowingTM[SIZE_ZERO].tm_year &&
		userTM[SIZE_ZERO].tm_mon >= currentShowingTM[SIZE_ZERO].tm_mon &&
		userTM[SIZE_ZERO].tm_mday >= currentShowingTM[SIZE_ZERO].tm_mday &&
		userTM[SIZE_ONE].tm_year <= currentShowingTM[SIZE_ONE].tm_year &&
		userTM[SIZE_ONE].tm_mon <= currentShowingTM[SIZE_ONE].tm_mon &&
		userTM[SIZE_ONE].tm_mday <= currentShowingTM[SIZE_ONE].tm_mday) {
			tmRangeToShow = currentShowingTM;

	} else {
		tmRangeToShow = userTM;
	}

	Event eventWithShowRange;
	eventWithShowRange.setStartEndDate(tmRangeToShow);

	return eventFacade->showDates(eventWithShowRange);
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

//used when user wants to change an event by typing its name, but there are several events with the same name
void Command::chooseExactMatches(Event& userEvent) {
	eventsToShow = eventFacade->findNameOccurrence(userEvent.getName());

	//setting userEvent to have invalid id indicates this command cannot be added to the undoStack
	userEvent = createInvalidEvent();
	assert(userEvent.getID() == INVALID_NUMBER);
	isExecuted = false;
}

Event Command::createInvalidEvent() {
	Event invalidEvent;
	invalidEvent.setID(INVALID_NUMBER);
	return invalidEvent;
}




//Add Command
AddCommand::AddCommand(EventFacade* eventStorage, Event e, vector<tm> currentShowing) {
	eventFacade = eventStorage;
	userEvent = e;
	currentShowingTM = currentShowing;
	isExecuted = false;
	isUndoable = true;
}

void AddCommand::execute() {
	isFloating = userEvent.getIsFloating();
	eventsToShow = eventFacade->addEvent(userEvent);

	if (isFloating) {
		return;
	} else {
		eventsToShow = getShowEventVector(userEvent, currentShowingTM);
	}

	isExecuted = true;
	logger.log(LogicLog::EXECUTED + LogicLog::ADD);
}

Event AddCommand::getEvent() {
	return userEvent;
}

void AddCommand::undo() {
	eventsToShow = eventFacade->deleteEvent(userEvent);
	if (!userEvent.getIsFloating()) {
		eventsToShow = getShowEventVector(userEvent, currentShowingTM);
	}
}




//Complete Command
CompleteCommand::CompleteCommand(EventFacade* eventStorage, int eventID, Event e, vector<tm> currentShowing) {
	eventFacade = eventStorage;
	id = eventID;
	userEvent = e;
	currentShowingTM = currentShowing;
	isExecuted = false;
	isUndoable = true;
}

void CompleteCommand::execute() {
	//if id found in current display, complete immediately
	if (id > SIZE_ZERO) {
		completeImmediately();
		logger.log(LogicLog::EXECUTED + LogicLog::COMPLETE);
		return;
	}

	vector<Event> tempEvents = eventFacade->findNameExact(userEvent.getName());
	int numResults = getNumEvents(tempEvents);

	switch (numResults) {

		//no exact match
	case SIZE_ZERO: { 
		logger.log(LogicLog::CASE_0 + LogicLog::COMPLETE);
		tempEvents = eventFacade->findNameOccurrence(userEvent.getName());
		userEvent = createInvalidEvent();
		numResults = getNumEvents(tempEvents);

		checkPartialMatches(numResults, tempEvents);
		return;
					}

					//1 exact match
	case SIZE_ONE: { 
		logger.log(LogicLog::CASE_1 + LogicLog::COMPLETE);
		completeExact(tempEvents);
		logger.log(LogicLog::EXECUTED + LogicLog::COMPLETE);
		return;
				   }

				   //more than 1 exact match
	default: { 
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
		eventsToShow = eventFacade->uncompleteEvent(userEvent);
		if (!isFloating) {
			eventsToShow = getShowEventVector(userEvent, currentShowingTM);
		}
	}
}

void CompleteCommand::completeImmediately() {
	isFloating = userEvent.getIsFloating();
	eventsToShow = eventFacade->completeEvent(userEvent);

	isExecuted = true;
}

void CompleteCommand::completeExact(vector<Event> tempEvents) {
	if (tempEvents.size() == SIZE_ONE) { //1 floating match => event will be at index 0
		isFloating = true;
		userEvent = tempEvents[SIZE_ZERO];
	
	} else { //1 normal match => event will be at index 1
		isFloating = false;
		id = tempEvents[SIZE_ONE].getID();
		userEvent = eventFacade->findEventWithID(id);
	}

	id = userEvent.getID();
	completeImmediately();
}




//Uncomplete Command
UncompleteCommand::UncompleteCommand(EventFacade* eventStorage, vector<Event> events, vector<tm> currentShowing) {
	eventFacade = eventStorage;
	eventsToShow = events;
	currentShowingTM = currentShowing;
	isExecuted = false;
	isUndoable = true;
}

void UncompleteCommand::execute() {
	int numResults = getNumEvents(eventsToShow);

	switch (numResults) {

	//no exact match
	case SIZE_ZERO: {
		logger.log(LogicLog::CASE_0 + LogicLog::UNCOMPLETE);
		userEvent = createInvalidEvent();
		isExecuted = true;
		return;
					}

	//1 exact match
	case SIZE_ONE: {
		logger.log(LogicLog::CASE_1 + LogicLog::UNCOMPLETE);
		
		userEvent = eventsToShow[SIZE_ZERO];
		if (userEvent.getID() <= INVALID_NUMBER) {
			userEvent = eventsToShow[SIZE_ONE];
		}
		uncompleteImmediately();

		logger.log(LogicLog::EXECUTED + LogicLog::UNCOMPLETE);
		return;
				   }
	
	//more than 1 exact match
	default: {
		logger.log(LogicLog::DEFAULT + LogicLog::UNCOMPLETE);
		userEvent = createInvalidEvent();
		return;
			 }
	}
}

Event UncompleteCommand::getEvent() {
	return userEvent;	
}

void UncompleteCommand::undo() {
	
}

void UncompleteCommand::uncompleteImmediately() {
	isFloating = userEvent.getIsFloating();
	if (isFloating) {
		eventsToShow = eventFacade->uncompleteEvent(userEvent);
	} else {
		eventFacade->uncompleteEvent(userEvent);
		eventsToShow = getShowEventVector(userEvent, currentShowingTM);
	}

	isExecuted = true;
}




//Delete Command
DeleteCommand::DeleteCommand(EventFacade* eventStorage, int eventID, Event e, vector<tm> currentShowing) {
	eventFacade = eventStorage;
	id = eventID;
	userEvent = e;
	currentShowingTM = currentShowing;
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

	//no exact match
	case SIZE_ZERO: { 
		logger.log(LogicLog::CASE_0 + LogicLog::DELETE);
		tempEvents = eventFacade->findNameOccurrence(userEvent.getName());
		userEvent = createInvalidEvent();
		numResults = getNumEvents(tempEvents);

		checkPartialMatches(numResults, tempEvents);
		return;
					}

	//1 exact match
	case SIZE_ONE: { 
		logger.log(LogicLog::CASE_1 + LogicLog::DELETE);
		deleteExact(tempEvents);
		logger.log(LogicLog::EXECUTED + LogicLog::DELETE);
		return;
				   }

	//more than 1 exact match
	default: { 
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
		if (!isFloating) {
			eventsToShow = getShowEventVector(userEvent, currentShowingTM);
		}
	}
}

void DeleteCommand::deleteImmediately() {
	isFloating = userEvent.getIsFloating();
	if (isFloating) {
		eventsToShow = eventFacade->deleteEvent(userEvent);
	} else {
		eventFacade->deleteEvent(userEvent);
		eventsToShow = getShowEventVector(userEvent, currentShowingTM);
	}

	isExecuted = true;
}

void DeleteCommand::deleteExact(vector<Event> tempEvents) {
	if (tempEvents.size() == SIZE_ONE) { //1 floating match => event will be at index 0
		isFloating = true;
		userEvent = tempEvents[SIZE_ZERO];

	} else { //1 normal match => event will be at index 1
		isFloating = false;
		id = tempEvents[SIZE_ONE].getID();
		userEvent = eventFacade->findEventWithID(id);
	}

	id = userEvent.getID();
	deleteImmediately();
}




//Edit Command
EditCommand::EditCommand(EventFacade* eventStorage, int eventID, Event toEdit, Event edited, vector<tm> currentShowing) {
	eventFacade = eventStorage;
	id = eventID;
	eventToEdit = toEdit;
	editedEvent = edited;
	currentShowingTM = currentShowing;
	isExecuted = false;
	isUndoable = true;
	isEdited = false;

}

void EditCommand::execute() {
	//if id found in current display, edit immediately
	if (id > SIZE_ZERO) {
		if (isEdited == false) {
			//for first time edit
			editImmediately();
		} else {
			//for redoing edit command that has previously been executed and undone
			redoEdit();
		}
		return;
	}

	vector<Event> tempEvents = eventFacade->findNameExact(eventToEdit.getName());
	int numResults = getNumEvents(tempEvents);

	switch (numResults) {

		//no exact match
	case SIZE_ZERO: { 
		logger.log(LogicLog::CASE_0 + LogicLog::EDIT);
		tempEvents = eventFacade->findNameOccurrence(eventToEdit.getName());
		eventToEdit = createInvalidEvent();
		numResults = tempEvents.size();

		checkPartialMatches(numResults, tempEvents);
		return;
					}

					//1 exact match
	case SIZE_ONE: { 
		logger.log(LogicLog::CASE_1 + LogicLog::EDIT);
		editExact(tempEvents);
		logger.log(LogicLog::EXECUTED + LogicLog::EDIT);
		return;
				   }

				   //more than 1 exact match
	default:{ 
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
	if (eventToEdit.getID() == INVALID_NUMBER) {
		return;
	}

	eventFacade->deleteEvent(editedEvent);
	if (eventToEdit.getIsFloating()) {
		eventsToShow = eventFacade->addEvent(eventToEdit);
	} else {
		eventFacade->addEvent(eventToEdit);
		eventsToShow = getShowEventVector(eventToEdit, currentShowingTM);
	}
	isFloating = eventToEdit.getIsFloating();
}

void EditCommand::editImmediately() {
	eventsToShow = eventFacade->editEvent(eventToEdit, editedEvent);
	editedEvent = getEventFromID(eventsToShow, id);
	isFloating = editedEvent.getIsFloating();
	if (!isFloating) {
		eventsToShow = getShowEventVector(editedEvent, currentShowingTM);
	}

	isExecuted = true;
	isEdited = true;
}

void EditCommand::editExact(vector<Event> tempEvents) {
	if (tempEvents.size() == SIZE_ONE) { //1 floating match => event will be at index 0
		isFloating = true;
		eventToEdit = tempEvents[SIZE_ZERO];

	} else { //1 normal match => event will be at index 1
		isFloating = false;
		id = tempEvents[SIZE_ONE].getID();
		eventToEdit = eventFacade->findEventWithID(id);
	}

	id = eventToEdit.getID();
	editImmediately();
}

void EditCommand::redoEdit() {
	eventsToShow = eventFacade->deleteEvent(eventToEdit);
	eventsToShow = eventFacade->addEvent(editedEvent);
	isFloating = editedEvent.getIsFloating();

	if (!isFloating) {
		eventsToShow = getShowEventVector(editedEvent, currentShowingTM);
	}
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