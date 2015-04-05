#include "Command.h"


const int Command::INVALID_NUMBER = -1;
const int Command::SIZE_ZERO = 0;
const int Command::SIZE_ONE = 1;
const int Command::SIZE_TWO = 2;

const string Command::LOG_FILE_NAME = "CommandLog.txt";


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

Event Command::createInvalidEvent() {
	Event invalidEvent;
	invalidEvent.setID(INVALID_NUMBER);
	return invalidEvent;
}

void Command::log(string logString) {
	ofstream outFile(LOG_FILE_NAME);

	logStrings.push_back(logString);
	for (unsigned int i = 0; i < logStrings.size(); i++) {
		outFile << logStrings[i] << endl;
	}
	outFile.close();
}

void Command::log(int logInt) {
	ostringstream outString;
	outString << logInt;

	ofstream outFile(LOG_FILE_NAME);

	logStrings.push_back(outString.str());
	for (unsigned int i = 0; i < logStrings.size(); i++) {
		outFile << logStrings[i] << endl;
	}
	outFile.close();
}

void Command::log(string logString, int logInt) {
	ostringstream outString;
	outString << " " << logInt;

	ofstream outFile(LOG_FILE_NAME);

	logStrings.push_back(logString + outString.str());
	for (unsigned int i = 0; i < logStrings.size(); i++) {
		outFile << logStrings[i] << endl;
	}
	outFile.close();
}




//Add Command
AddCommand::AddCommand(EventFacade* eventStorage, Event e) {
	eventFacade = eventStorage;
	userEvent = e;
	isExecuted = false;
	isUndoable = true;
}

void AddCommand::execute() {
	addedEvents = eventFacade->addEvent(userEvent);
	isFloating = userEvent.getIsFloating();
	isExecuted = true;
}

vector<Event> AddCommand::getEventVector() {
	return addedEvents;
}

Event AddCommand::getEvent() {
	return userEvent;
}

void AddCommand::undo() {
	addedEvents = eventFacade->deleteEvent(userEvent.getID(), userEvent);
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
		return;
	}

	vector<Event> tempEvents = eventFacade->findNameExact(userEvent.getName());
	int numResults = getNumEvents(tempEvents);

	switch (numResults) {
	case SIZE_ZERO: { //no exact match
		userEvent = createInvalidEvent();
		tempEvents = eventFacade->findNameOccurrence(userEvent.getName());
		numResults = getNumEvents(tempEvents);

		switch (numResults) {
		case 0: { //no partial match
			completedEvents.push_back(createInvalidEvent());
			userEvent = createInvalidEvent();
			isExecuted = true;
			return;
				}

		default: { //at least 1 partial match
			completedEvents = tempEvents;
			userEvent = createInvalidEvent();
			isExecuted = false;
			return;
				 }
		}

		break;
					}

	case SIZE_ONE: { //1 exact match
		if (tempEvents.size() == SIZE_ONE) { //1 floating match => event will be at index 0
			isFloating = true;
			userEvent = tempEvents[0];
			completedEvents = eventFacade->completeEvent(tempEvents[0].getID(), tempEvents[0]);
		} else { //1 normal match => event will be at index 1
			isFloating = false;
			userEvent = tempEvents[1];
			completedEvents = eventFacade->completeEvent(tempEvents[1].getID(), tempEvents[1]);
		}
		isExecuted = true;
		return;
				   }

	default: { //more than 1 exact match
		completedEvents = eventFacade->findNameOccurrence(userEvent.getName());
		userEvent = createInvalidEvent();
		isExecuted = false;
		return;
			 }
	}
}

vector<Event> CompleteCommand::getEventVector() {
	return completedEvents;
}

Event CompleteCommand::getEvent() {
	return userEvent;
}

void CompleteCommand::undo() {
	if (userEvent.getID() != INVALID_NUMBER) {
		completedEvents = eventFacade->uncompleteEvent(userEvent.getID(), userEvent);
	}
}

void CompleteCommand::completeImmediately() {
	isFloating = userEvent.getIsFloating();
	completedEvents = eventFacade->completeEvent(id, userEvent);
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
		return;
	}

	vector<Event> tempEvents = eventFacade->findNameExact(userEvent.getName());
	int numResults = getNumEvents(tempEvents);

	switch (numResults) {
	case SIZE_ZERO: { //no exact match
		userEvent = createInvalidEvent();
		tempEvents = eventFacade->findNameOccurrence(userEvent.getName());
		numResults = getNumEvents(tempEvents);
		
		switch (numResults) {
		case 0: { //no partial match
			deletedEvents.push_back(createInvalidEvent());
			userEvent = createInvalidEvent();
			isExecuted = true;
			return;
				}

		default: { //at least 1 partial match
			deletedEvents = tempEvents;
			userEvent = createInvalidEvent();
			isExecuted = false;
			return;
				 }
		}

		break;
				}

	case SIZE_ONE: { //1 exact match
		if (tempEvents.size() == SIZE_ONE) { //1 floating match => event will be at index 0
			isFloating = true;
			userEvent = tempEvents[0];
			deletedEvents = eventFacade->deleteEvent(tempEvents[0].getID(), tempEvents[0]);
		} else { //1 normal match => event will be at index 1
			isFloating = false;
			userEvent = tempEvents[1];
			deletedEvents = eventFacade->deleteEvent(tempEvents[1].getID(), tempEvents[1]);
		}
		isExecuted = true;
		return;
				   }

	default: { //more than 1 exact match
		deletedEvents = eventFacade->findNameOccurrence(userEvent.getName());
		userEvent = createInvalidEvent();
		isExecuted = false;
		return;
			 };
	};
}

vector<Event> DeleteCommand::getEventVector() {
	return deletedEvents;
}

Event DeleteCommand::getEvent() {
	return userEvent;
}

void DeleteCommand::undo() {
	if (userEvent.getID() != INVALID_NUMBER) {
		deletedEvents = eventFacade->addEvent(userEvent);
	}
}

void DeleteCommand::deleteImmediately() {
	isFloating = userEvent.getIsFloating();
	deletedEvents = eventFacade->deleteEvent(id, userEvent);
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
		return;
	}

	vector<Event> tempEvents = eventFacade->findNameExact(eventToEdit.getName());
	int numResults = getNumEvents(tempEvents);

	switch (numResults) {
	case SIZE_ZERO: { //no exact match
		eventToEdit = createInvalidEvent();
		tempEvents = eventFacade->findNameOccurrence(eventToEdit.getName());
		numResults = tempEvents.size();
		switch (numResults) {
		case SIZE_ZERO: { //no partial match
			editedResults.push_back(createInvalidEvent());
			isExecuted = true;
			return;
			break;
					}

		default: { //at least 1 partial match
			editedResults = tempEvents;
			isExecuted = false;
			return;
			break;
				 }
		}
		break;
				}

	case SIZE_ONE: { //1 exact match
		if (tempEvents.size() == 1) { //1 floating match => event will be at index 0
			isFloating = true;
			eventToEdit = tempEvents[0];
			editedResults = eventFacade->editEvent(eventToEdit.getID(), eventToEdit, editedEvent);
		} else { //1 normal match => event will be at index 1
			isFloating = false;
			eventToEdit = tempEvents[1];
			editedResults = eventFacade->editEvent(eventToEdit.getID(), eventToEdit, editedEvent);
		}
		editedEvent = getEventFromID(editedResults, eventToEdit.getID());
		isExecuted = true;
		return;
		break;
				   }

	default:{ //more than 1 exact match
		eventToEdit = createInvalidEvent();
		editedResults = eventFacade->findNameOccurrence(eventToEdit.getName());
		isExecuted = false;
		return;
		break;
			}
	}

}

vector<Event> EditCommand::getEventVector() {
	return editedResults;
}

Event EditCommand::getEvent() {
	return eventToEdit;
}

void EditCommand::undo() {
	if (eventToEdit.getID() != INVALID_NUMBER) {
		eventFacade->deleteEvent(editedEvent.getID(), editedEvent);
		editedResults = eventFacade->addEvent(eventToEdit);
		return;
	}
}

void EditCommand::editImmediately() {
	isFloating = eventToEdit.getIsFloating();
	editedResults = eventFacade->editEvent(id, eventToEdit, editedEvent);
	editedEvent = getEventFromID(editedResults, id);
	isExecuted = true;
}




//Search Command
SearchCommand::SearchCommand(EventFacade* eventStorage, string s) {
	eventFacade = eventStorage;
	searchString = s;
	isUndoable = false;
}

void SearchCommand::execute() {
	searchResults = eventFacade->findNameOccurrence(searchString);
}

vector<Event> SearchCommand::getEventVector() {
	return searchResults;
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
}

vector<Event> ShowCommand::getEventVector() {
	return eventsToShow;
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
}

vector<Event> ShowAllCommand::getEventVector() {
	return eventsToShow;
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
}

vector<Event> ShowAllImportantCommand::getEventVector() {
	return eventsToShow;
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
}

vector<Event> ShowCompletedCommand::getEventVector() {
	return eventsToShow;
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

vector<Event> ShowDueCommand::getEventVector() {
	return eventsToShow;
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
}

vector<Event> ShowFloatCommand::getEventVector() {
	return eventsToShow;
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
}

vector<Event> ShowImportanceCommand::getEventVector() {
	return eventsToShow;
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
}

void NullCommand::execute() {
}

vector<Event> NullCommand::getEventVector() {
	vector<Event> emptyVec;
	return emptyVec;
}

Event NullCommand::getEvent() {
	return createInvalidEvent();
}

void NullCommand::undo() {
}