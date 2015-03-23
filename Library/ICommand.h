#pragma once

#ifndef ICOMMAND_H
#define ICOMMAND_H

#include "EventStorage.h"


class ICommand {
public:
	static const int INVALID_NUMBER;
	virtual void execute() = 0;
	virtual vector<Event> getEventVector() = 0;
	virtual Event getEvent() = 0;

	bool getIsFloating();
	bool getIsComplete();

protected:
	bool isFloating;
	bool isComplete;	
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
	Event getEvent();
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
	Event getEvent();
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
	Event getEvent();
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
	Event getEvent();
};




class ShowFloatCommand : public ICommand {
private:
	EventStorage* eventStore;
	vector<Event> eventsToShow;

public:
	ShowFloatCommand(EventStorage* eventStorage);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
};

#endif