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
	

	vector<Event> tempEvents = eventStore->checkMultipleResults(userEvent.getName());

	switch (tempEvents.size()) {
	case 0: {
		Event invalidEvent;
		invalidEvent.setFeedback(userEvent.getFeedback());
		invalidEvent.setID(INVALID_NUMBER);
		deletedEvents.push_back(invalidEvent);
		isComplete = true;
		return;
		break;
			}

	case 1: {
		isFloating = tempEvents[0].getIsFloating();
		userEvent = tempEvents[0];
		deletedEvents = eventStore->deleteEvent(tempEvents[0].getID(), tempEvents[0]);
		isComplete = true;
		return;
		break;
			}

	default: {
		deletedEvents = tempEvents;
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

	vector<Event> tempEvents = eventStore->checkMultipleResults(eventToEdit.getName());

	switch (tempEvents.size()) {
	case 0: {
		Event invalidEvent;
		invalidEvent.setID(INVALID_NUMBER);
		editedResults.push_back(invalidEvent);
		isComplete = true;
		return;
		break;
			}

	case 1: {
		isFloating = tempEvents[0].getIsFloating();
		eventToEdit = tempEvents[0];
		editedResults = eventStore->editEvent(eventToEdit.getID(), eventToEdit, editedEvent);
		isComplete = true;
		return;
		break;
			}

	default: {
		editedResults = tempEvents;
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
