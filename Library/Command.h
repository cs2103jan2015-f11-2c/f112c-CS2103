#pragma once

#ifndef COMMAND_H
#define COMMAND_H

#include <algorithm>
#include <fstream>
#include <sstream>
#include "EventStorage.h"

using std::find;
using std::ofstream;
using std::ostringstream;


class Command {
public:
	static const int INVALID_NUMBER;
	static const string LOG_FILE_NAME;

	virtual void execute() = 0;
	virtual vector<Event> getEventVector() = 0;
	virtual Event getEvent() = 0;
	virtual void undo() = 0;

	bool getIsFloating();
	bool getIsExecuted();
	bool getIsUndoable();
	int getNumEvents(vector<Event> eventVec);
	Event createInvalidEvent();

	void log(string logString);
	void log(int logInt);
	void log(string logString, int logInt);

protected:
	bool isFloating;
	bool isExecuted;
	bool isUndoable;
	vector<string> logStrings;
};




class AddCommand : public Command {
private:
	EventStorage* eventStore;
	Event userEvent;
	vector<Event> addedEvents;

public:
	AddCommand(EventStorage* eventStorage, Event e);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};




/*
class CompleteCommand : public Command {
private:
	EventStorage* eventStore;
	int id;
	Event userEvent;
	vector<Event> completedEvents;

public:
	CompleteCommand(EventStorage* eventStorage, int eventID, Event userEvent);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};
*/




class DeleteCommand : public Command {
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
	void undo();
};




class EditCommand : public Command {
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
	void undo();
};




class SearchCommand : public Command {
private:
	EventStorage* eventStore;
	string searchString;
	vector<Event> searchResults;

public:
	SearchCommand(EventStorage* eventStorage, string s);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};




class ShowCommand : public Command {
private:
	EventStorage* eventStore;
	Event eventRangeToShow;
	vector<Event> eventsToShow;

public:
	ShowCommand(EventStorage* eventStorage, Event e);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};




class ShowAllCommand : public Command {
private:
	EventStorage* eventStore;
	vector<Event> eventsToShow;
public:
	ShowAllCommand(EventStorage* eventStorage);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};




class ShowFloatCommand : public Command {
private:
	EventStorage* eventStore;
	vector<Event> eventsToShow;

public:
	ShowFloatCommand(EventStorage* eventStorage);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};





class NullCommand : public Command {
private:

public:
	NullCommand();
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};


#endif