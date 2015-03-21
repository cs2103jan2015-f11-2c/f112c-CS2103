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




DeleteCommand::DeleteCommand(EventStorage* eventStorage, int eventID, Event e) {
	eventStore = eventStorage;
	id = eventID;
	userEvent = e;
}

void DeleteCommand::execute() {
	deletedEvents = eventStore->deleteEvent(id, userEvent);
}

vector<Event> DeleteCommand::getEventVector() {
	return deletedEvents;
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