#pragma once

#ifndef ICOMMAND_H
#define ICOMMAND_H

#include "EventStorage.h"


class ICommand {
public:
	virtual void execute() = 0;

};




class AddCommand : public ICommand {
private:
	EventStorage* eventStore;
	Event userEvent;

public:
	AddCommand(EventStorage* eventStorage, Event e);
	void execute();

};




class DeleteCommand : public ICommand {
private:
	EventStorage* eventStore;
	int id;
	Event userEvent;

public:
	DeleteCommand(EventStorage* eventStorage, int eventID, Event userEvent);
	void execute();
};




class EditCommand : public ICommand {
private:
	EventStorage* eventStore;
	int id;
	Event eventToEdit, editedEvent;

public:
	EditCommand(EventStorage* eventStorage, int eventID, Event toEdit, Event edited);
	void execute();
};


#endif