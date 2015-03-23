#include "ICommand.h"


AddCommand::AddCommand(EventStorage* eventStorage, Event e) {
	eventStore = eventStorage;
	userEvent = e;
}

void AddCommand::execute() {
	int newID = userEvent.getID();
	addedEvents = eventStore->addEvent(userEvent);
}

vector<Event> AddCommand::getEventVector() {
	return addedEvents;
}

bool AddCommand::getIsFloating() {
	return isFloating;
}




DeleteCommand::DeleteCommand(EventStorage* eventStorage, int eventID, Event e) {
	eventStore = eventStorage;
	id = eventID;
	userEvent = e;
}

void DeleteCommand::execute() {
	if (id > 0) {
		deletedEvents = eventStore->deleteEvent(id, userEvent);
		return;
	}
	

	vector<Event> tempEvents = eventStore->checkMultipleResults(userEvent.getName());
	
	switch (tempEvents.size()) {
	case 0:
		break;

	case 1: {
		isFloating = tempEvents[0].getIsFloating();
		deletedEvents = eventStore->deleteEvent(tempEvents[0].getID(), tempEvents[0]);
		return;
		break;
			}

	default:
		break;
	};
}

vector<Event> DeleteCommand::getEventVector() {
	return deletedEvents;
}

bool DeleteCommand::getIsFloating() {
	return isFloating;
}




EditCommand::EditCommand(EventStorage* eventStorage, int eventID, Event toEdit, Event edited) {
	eventStore = eventStorage;
	id = eventID;
	eventToEdit = toEdit;
	editedEvent = edited;
}

void EditCommand::execute() {
	editedResults = eventStore->editEvent(id, eventToEdit, editedEvent);
}

vector<Event> EditCommand::getEventVector() {
	return editedResults;
}

bool EditCommand::getIsFloating() {
	return isFloating;
}




CheckMultipleCommand::CheckMultipleCommand(EventStorage* eventStorage, string name) {
	eventStore = eventStorage;
	eventName = name;
}

void CheckMultipleCommand::execute() {
	multipleResults = eventStore->checkMultipleResults(eventName);
	numResults = multipleResults.size();
}

vector<Event> CheckMultipleCommand::getEventVector() {
	return multipleResults;
}

int CheckMultipleCommand::getNumResults() {
	return numResults;
}

bool CheckMultipleCommand::getIsFloating() {
	return isFloating;
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

bool ShowCommand::getIsFloating() {
	return isFloating;
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

bool ShowFloatCommand::getIsFloating() {
	return isFloating;
}