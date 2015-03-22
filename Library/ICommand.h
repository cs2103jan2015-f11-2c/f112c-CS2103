#pragma once

#ifndef ICOMMAND_H
#define ICOMMAND_H

#include "EventStorage.h"


class ICommand {
public:
	virtual void execute() = 0;
	virtual vector<Event> getEventVector() = 0;
	virtual bool getIsFloating() = 0;
};




class AddCommand : public ICommand {
private:
	EventStorage* eventStore;
	Event userEvent;
	vector<Event> addedEvents;
	bool isFloating;

public:
	AddCommand(EventStorage* eventStorage, Event e);
	void execute();
	vector<Event> getEventVector();
	bool getIsFloating();
};




class DeleteCommand : public ICommand {
private:
	EventStorage* eventStore;
	int id;
	Event userEvent;
	vector<Event> deletedEvents;
	bool isFloating;

public:
	DeleteCommand(EventStorage* eventStorage, int eventID, Event userEvent);
	void execute();
	vector<Event> getEventVector();
	bool getIsFloating();
};




class EditCommand : public ICommand {
private:
	EventStorage* eventStore;
	int id;
	Event eventToEdit, editedEvent;
	vector<Event> editedResults;
	bool isFloating;

public:
	EditCommand(EventStorage* eventStorage, int eventID, Event toEdit, Event edited);
	void execute();
	vector<Event> getEventVector();
	bool getIsFloating();
};





class CheckMultipleCommand : public ICommand {
private:
	EventStorage* eventStore;
	string eventName;
	vector<Event> multipleResults;
	int numResults;
	bool isFloating;

public:
	CheckMultipleCommand(EventStorage* eventStorage, string name);
	void execute();
	vector<Event> getEventVector();
	int getNumResults();
	bool getIsFloating();
};




class ShowCommand : public ICommand {
private:
	EventStorage* eventStore;
	Event eventRangeToShow;
	vector<Event> eventsToShow;
	bool isFloating;

public:
	ShowCommand(EventStorage* eventStorage, Event e);
	void execute();
	vector<Event> getEventVector();
	bool getIsFloating();
};




class ShowFloatCommand : public ICommand {
private:
	EventStorage* eventStore;
	vector<Event> eventsToShow;
	bool isFloating;

public:
	ShowFloatCommand(EventStorage* eventStorage);
	void execute();
	vector<Event> getEventVector();
	bool getIsFloating();
};

#endif