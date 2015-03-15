#include "ICommand.h"


AddCommand::AddCommand(EventStorage* eventStorage, Event e) {
	eventStore = eventStorage;
	userEvent = e;
}

void AddCommand::execute() {
	eventStore->addEvent(userEvent);
}




DeleteCommand::DeleteCommand(EventStorage* eventStorage, int eventID, Event e) {
	eventStore = eventStorage;
	id = eventID;
	userEvent = e;
}

void DeleteCommand::execute() {
	eventStore->deleteEvent(id, userEvent);
}




EditCommand::EditCommand(EventStorage* eventStorage, int eventID, Event toEdit, Event edited) {
	eventStore = eventStorage;
	id = eventID;
	eventToEdit = toEdit;
	editedEvent = edited;
}

void EditCommand::execute() {
	eventStore->editEvent(id, eventToEdit, editedEvent);
}