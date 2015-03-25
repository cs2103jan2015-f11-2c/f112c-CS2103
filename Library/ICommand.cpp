#include "ICommand.h"


const int ICommand::INVALID_NUMBER = -1;

bool ICommand::getIsFloating() {
	return isFloating;
}

bool ICommand::getIsComplete() {
	return isComplete;
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

	switch (tempEvents.size()) {
	case 0: { //no exact match
		tempEvents = eventStore->checkMultipleResults(userEvent.getName());
		switch (tempEvents.size()) {
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

	case 1: { //1 exact floating match
		isFloating = true;
		userEvent = tempEvents[0];
		deletedEvents = eventStore->deleteEvent(tempEvents[0].getID(), tempEvents[0]);
		isComplete = true;
		return;
		break;
			}

	case 2: { //1 exact normal match or 2 exact floating match
		if (tempEvents[0].getIsFloating()) {
			isFloating = true;
			goto Many_Exact_Match;
		}

		isFloating = false;
		userEvent = tempEvents[1];
		deletedEvents = eventStore->deleteEvent(tempEvents[1].getID(), tempEvents[1]);
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

	switch (tempEvents.size()) {
	case 0: { //no exact match
		tempEvents = eventStore->checkMultipleResults(eventToEdit.getName());
		switch (tempEvents.size()) {
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

	case 1: { //1 exact floating match
		isFloating = true;
		eventToEdit = tempEvents[0];
		editedResults = eventStore->editEvent(eventToEdit.getID(), eventToEdit, editedEvent);
		isComplete = true;
		return;
		break;
			}

	case 2: { //1 exact normal match or 2 exact floating match
		if (tempEvents[0].getIsFloating()) {
			isFloating = true;
			goto Many_Exact_Match;
		}

		isFloating = false;
		eventToEdit = tempEvents[1];
		editedResults = eventStore->editEvent(eventToEdit.getID(), eventToEdit, editedEvent);
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
