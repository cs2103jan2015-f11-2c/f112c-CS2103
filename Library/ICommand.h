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
	vector<Event> addedEvents;

public:
	AddCommand(EventStorage* eventStorage, Event e);
	void execute();
	vector<Event> getEventVector();

};




class DeleteCommand : public ICommand {
private:
	EventStorage* eventStore;
	int id;
	Event userEvent;
	vector<Event> deletedEvents;

public:
	DeleteCommand(EventStorage* eventStorage, int eventID, Event userEvent);
	void execute();
	vector<Event> getEventVector();
};




class EditCommand : public ICommand {
private:
	EventStorage* eventStore;
	int id;
	Event eventToEdit, editedEvent;
	vector<Event> editedResults;

public:
	EditCommand(EventStorage* eventStorage, int eventID, Event toEdit, Event edited);
	void execute();
	vector<Event> getEventVector();
};





class CheckMultipleCommand : public ICommand {
private:
	EventStorage* eventStore;
	string eventName;
	vector<Event> multipleResults;
	int numResults;

public:
	CheckMultipleCommand(EventStorage* eventStorage, string name);
	void execute();
	vector<Event> getEventVector();
	int getNumResults();
};




class ShowCommand : public ICommand {
private:
	EventStorage* eventStore;
	Event eventRangeToShow;
	vector<Event> eventsToShow;

public:
	ShowCommand(EventStorage* eventStorage, Event e);
	void execute();
	vector<Event> getEventVector();
};

#endif