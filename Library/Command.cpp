#include "Command.h"


const int Command::INVALID_NUMBER = -1;
const int Command::SIZE_ZERO = 0;
const int Command::SIZE_ONE = 1;

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
	for (unsigned int i = 0 ; i < eventVec.size() ; i++) {
		if (eventVec[i].getID() < 0) {
			eventVec.erase(eventVec.begin() + i);
		}
	}

	int count = SIZE_ZERO;
	vector<int> idVec;

	//only count events with different ID
	for (unsigned int i = 0 ; i < eventVec.size() ; i++) {
		if ( find(idVec.begin(), idVec.end(), eventVec[i].getID()) == idVec.end() ) {
			idVec.push_back(eventVec[i].getID());
			count++;
		}
	}
	return count;
}

Event Command::getEventFromID(vector<Event> eventVec, int id) {
	for (unsigned int i = 0 ; i < eventVec.size() ; i++) {
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
	for (unsigned int i = 0 ; i < logStrings.size() ; i++) {
		outFile << logStrings[i] << endl;
	}
	outFile.close();
}

void Command::log(int logInt) {
	ostringstream outString;
	outString << logInt;

	ofstream outFile(LOG_FILE_NAME);

	logStrings.push_back(outString.str());
	for (unsigned int i = 0 ; i < logStrings.size() ; i++) {
		outFile << logStrings[i] << endl;
	}
	outFile.close();
}

void Command::log(string logString, int logInt) {
	ostringstream outString;
	outString << " " << logInt;

	ofstream outFile(LOG_FILE_NAME);

	logStrings.push_back(logString + outString.str());
	for (unsigned int i = 0 ; i < logStrings.size() ; i++) {
		outFile << logStrings[i] << endl;
	}
	outFile.close();
}




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
		isFloating = userEvent.getIsFloating();
		//completedEvents = eventFacade->???
		isExecuted = true;
		return;
	}

	vector<Event> tempEvents = eventFacade->findNameExact(userEvent.getName());
	int numResults = getNumEvents(tempEvents);

	switch (numResults) {
	case 0: {
		break;
			}

	case 1: {
		break;
			}

	default: {
		break;
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
}




DeleteCommand::DeleteCommand(EventFacade* eventStorage, Event e) {
	eventFacade = eventStorage;
	userEvent = e;
	isExecuted = false;
	isUndoable = true;
}

void DeleteCommand::execute() {
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
			break;
				}

		default: { //at least 1 partial match
			deletedEvents = tempEvents;
			userEvent = createInvalidEvent();
			isExecuted = false;
			return;
			break;
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
		break;
				   }

	default: { //more than 1 exact match
		deletedEvents = eventFacade->findNameOccurrence(userEvent.getName());
		userEvent = createInvalidEvent();
		isExecuted = false;
		return;
		break;
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




EditCommand::EditCommand(EventFacade* eventStorage, Event toEdit, Event edited) {
	eventFacade = eventStorage;
	eventToEdit = toEdit;
	editedEvent = edited;
	isExecuted = false;
	isUndoable = true;
}

void EditCommand::execute() {
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
		editedResults = eventFacade->deleteEvent(editedEvent.getID(), editedEvent);
		editedResults = eventFacade->addEvent(eventToEdit);
		return;
	}
}




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




ShowImportanceCommand::ShowImportanceCommand(EventFacade* eventStorage) {
	eventFacade = eventStorage;
	isUndoable = false;
}

void ShowImportanceCommand::execute() {
}

vector<Event> ShowImportanceCommand::getEventVector() {
	return eventsToShow;
}

Event ShowImportanceCommand::getEvent() {
	return createInvalidEvent();
}

void ShowImportanceCommand::undo() {
}




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