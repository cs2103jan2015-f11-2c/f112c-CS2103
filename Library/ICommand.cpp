#include "ICommand.h"


const int ICommand::INVALID_NUMBER = -1;
const string ICommand::LOG_FILE_NAME = "CommandLog.txt";

bool ICommand::getIsFloating() {
	return isFloating;
}

bool ICommand::getIsComplete() {
	return isComplete;
}

int ICommand::getNumEvents(vector<Event> eventVec) {
	if(eventVec.empty()) {
		return 0;
	}
	
	int i = 0, count = 1;
	vector<int> idVec;

	while (eventVec[i].getID() > 0) {
		i++;
	}
	idVec.push_back(eventVec[i].getID());

	for (; i < eventVec.size() ; i++) {
		if (eventVec[i].getID() > 0) {
			if ( find(idVec.begin(), idVec.end(), eventVec[i].getID()) != idVec.end()) {
				count++;
			}
		}
	}
	return count;
}

void ICommand::log(string logString) {
	ofstream outFile(LOG_FILE_NAME);
	
	logStrings.push_back(logString);
	for (int i = 0 ; i < logStrings.size() ; i++) {
		outFile << logStrings[i] << endl;
	}
	outFile.close();

}



AddCommand::AddCommand(EventStorage* eventStorage, Event e) {
	eventStore = eventStorage;
	userEvent = e;
	isComplete = false;
}

void AddCommand::execute() {
	int newID = userEvent.getID();
	addedEvents = eventStore->addEvent(userEvent);
	isComplete = true;
}

vector<Event> AddCommand::getEventVector() {
	return addedEvents;
}

Event AddCommand::getEvent() {
	return userEvent;
}

void AddCommand::undo() {
	addedEvents = eventStore->deleteEvent(userEvent.getID(), userEvent);
}




DeleteCommand::DeleteCommand(EventStorage* eventStorage, int eventID, Event e) {
	eventStore = eventStorage;
	id = eventID;
	userEvent = e;
	isComplete = false;
}

void DeleteCommand::execute() {
	if (id > 0) {
		isFloating = userEvent.getIsFloating();
		deletedEvents = eventStore->deleteEvent(id, userEvent);
		isComplete = true;
		return;
	}
	
	vector<Event> tempEvents = eventStore->checkExactString(userEvent.getName());
	int numResults = getNumEvents(tempEvents);
	
	switch (numResults) {
	case 0: { //no exact match
		tempEvents = eventStore->checkMultipleResults(userEvent.getName());
		numResults = getNumEvents(tempEvents);
		switch (numResults) {
		case 0: { //no partial match
			Event invalidEvent;
			invalidEvent.setFeedback(userEvent.getFeedback());
			invalidEvent.setID(INVALID_NUMBER);
			deletedEvents.push_back(invalidEvent);
			isComplete = true;
			return;
			break;
				}

		default: { //at least 1 partial match
			deletedEvents = tempEvents;
			isComplete = false;
			return;
			break;
				 }
		}
		break;
			}

	case 1: { //1 exact match
		if (tempEvents.size() == 1) {
			isFloating = true;
			userEvent = tempEvents[0];
			deletedEvents = eventStore->deleteEvent(tempEvents[0].getID(), tempEvents[0]);
		} else {
			isFloating = false;
			userEvent = tempEvents[1];
			deletedEvents = eventStore->deleteEvent(tempEvents[1].getID(), tempEvents[1]);
		}
		isComplete = true;
		return;
		break;
			}

	default:
Many_Exact_Match: { //more than 1 exact match
		deletedEvents = eventStore->checkMultipleResults(userEvent.getName());
		isComplete = false;
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
}




EditCommand::EditCommand(EventStorage* eventStorage, int eventID, Event toEdit, Event edited) {
	eventStore = eventStorage;
	id = eventID;
	eventToEdit = toEdit;
	editedEvent = edited;
}

void EditCommand::execute() {
	if (id > 0) {
		isFloating = eventToEdit.getIsFloating();
		editedResults = eventStore->editEvent(id, eventToEdit, editedEvent);
		isComplete = true;
		return;
	}

	vector<Event> tempEvents = eventStore->checkExactString(eventToEdit.getName());
	int numResults = getNumEvents(tempEvents);

	switch (numResults) {
	case 0: { //no exact match
		tempEvents = eventStore->checkMultipleResults(eventToEdit.getName());
		numResults = tempEvents.size();
		switch (numResults) {
		case 0: { //no partial match
			Event invalidEvent;
			invalidEvent.setFeedback(eventToEdit.getFeedback());
			invalidEvent.setID(INVALID_NUMBER);
			editedResults.push_back(invalidEvent);
			isComplete = true;
			return;
			break;
				}

		default: { //at least 1 partial match
			editedResults = tempEvents;
			isComplete = false;
			return;
			break;
				 }
		}
		break;
			}

	case 1: { //1 exact match
		if (tempEvents.size() == 1) {
		isFloating = true;
		eventToEdit = tempEvents[0];
		editedResults = eventStore->editEvent(eventToEdit.getID(), eventToEdit, editedEvent);
		} else {
			isFloating = false;
			eventToEdit = tempEvents[1];
			editedResults = eventStore->editEvent(eventToEdit.getID(), eventToEdit, editedEvent);
		}
		isComplete = true;
		return;
		break;
			}

	default:
Many_Exact_Match: { //more than 1 exact match
		editedResults = eventStore->checkMultipleResults(eventToEdit.getName());
		isComplete = false;
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
}




SearchCommand::SearchCommand(EventStorage* eventStorage, Event e) {
	eventStore = eventStorage;
	userSearchEvent = e;
}

void SearchCommand::execute() {
}

vector<Event> SearchCommand::getEventVector() {
	return searchResults;
}

Event SearchCommand::getEvent() {
	return userSearchEvent;
}

void SearchCommand::undo() {
}




ShowCommand::ShowCommand(EventStorage* eventStorage, Event e) {
	eventStore = eventStorage;
	eventRangeToShow = e;
}

void ShowCommand::execute() {
	eventsToShow = eventStore->showDates(eventRangeToShow);
}

vector<Event> ShowCommand::getEventVector() {
	return eventsToShow;
}

Event ShowCommand::getEvent() {
	return eventRangeToShow;
}

void ShowCommand::undo() {
}




ShowAllCommand::ShowAllCommand(EventStorage* eventStorage) {
	eventStore = eventStorage;
}

void ShowAllCommand::execute() {
	vector<Event> floating = eventStore->getAllFloatingEvents();
	vector<Event> normal = eventStore->getAllNormalEvents();
	floating.insert(floating.end(), normal.begin(), normal.end());

	eventsToShow = floating;
}

vector<Event> ShowAllCommand::getEventVector() {
	return eventsToShow;
}

Event ShowAllCommand::getEvent() {
	Event e;
	e.setID(INVALID_NUMBER);
	return e;
}

void ShowAllCommand::undo() {
}




ShowFloatCommand::ShowFloatCommand(EventStorage* eventStorage) {
	eventStore = eventStorage;
}

void ShowFloatCommand::execute() {
	eventsToShow = eventStore->getAllFloatingEvents();
	isFloating = true;
}

vector<Event> ShowFloatCommand::getEventVector() {
	return eventsToShow;
}

Event ShowFloatCommand::getEvent() {
	Event e;
	return e;
}

void ShowFloatCommand::undo() {
}