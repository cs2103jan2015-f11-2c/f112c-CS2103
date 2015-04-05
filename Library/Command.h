#pragma once

#ifndef COMMAND_H
#define COMMAND_H

#include <algorithm>
#include <fstream>
#include <sstream>
#include "EventFacade.h"
#include "LogicLog.h"

using std::find;


class Command {
public:
	static const int INVALID_NUMBER;
	static const int SIZE_ZERO;
	static const int SIZE_ONE;
	static const int SIZE_TWO;

	static const string LOG_FILE_NAME;

	//virtual methods
	virtual void execute() = 0;
	virtual vector<Event> getEventVector() = 0;
	virtual Event getEvent() = 0;
	virtual void undo() = 0;

	//common methods
	bool getIsFloating();
	bool getIsExecuted();
	bool getIsUndoable();
	int getNumEvents(vector<Event> eventVec);
	Event getEventFromID(vector<Event> eventVec, int id);
	Event createInvalidEvent();


protected:
	bool isFloating;
	bool isExecuted;
	bool isUndoable;
	LogicLog logger;
};




class AddCommand : public Command {
private:
	EventFacade* eventFacade;
	Event userEvent;
	vector<Event> addedEvents;

public:
	AddCommand(EventFacade* eventStorage, Event e);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};




class CompleteCommand : public Command {
private:
	EventFacade* eventFacade;
	int id;
	Event userEvent;
	vector<Event> completedEvents;

public:
	CompleteCommand(EventFacade* eventStorage, int eventID, Event userEvent);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();

	void completeImmediately();
};




class DeleteCommand : public Command {
private:
	EventFacade* eventFacade;
	int id;
	Event userEvent;
	vector<Event> deletedEvents;

public:
	DeleteCommand(EventFacade* eventStorage, int eventID, Event userEvent);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();

	void deleteImmediately();
};




class EditCommand : public Command {
private:
	EventFacade* eventFacade;
	int id;
	Event eventToEdit, editedEvent;
	vector<Event> editedResults;

public:
	EditCommand(EventFacade* eventStorage, int eventID, Event toEdit, Event edited);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();

	void editImmediately();
};




class SearchCommand : public Command {
private:
	EventFacade* eventFacade;
	string searchString;
	vector<Event> searchResults;

public:
	SearchCommand(EventFacade* eventStorage, string s);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};




class ShowCommand : public Command {
private:
	EventFacade* eventFacade;
	Event eventRangeToShow;
	vector<Event> eventsToShow;

public:
	ShowCommand(EventFacade* eventStorage, Event e);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};




class ShowAllCommand : public Command {
private:
	EventFacade* eventFacade;
	vector<Event> eventsToShow;
public:
	ShowAllCommand(EventFacade* eventStorage);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};




class ShowAllImportantCommand : public Command {
private:
	EventFacade* eventFacade;
	vector<Event> eventsToShow;
public:
	ShowAllImportantCommand(EventFacade* eventStorage);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};




class ShowCompletedCommand : public Command {
private:
	EventFacade* eventFacade;
	vector<Event> eventsToShow;

public:
	ShowCompletedCommand(EventFacade* eventStorage);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};




class ShowDueCommand : public Command {
private:
	EventFacade* eventFacade;
	vector<Event> eventsToShow;

public:
	ShowDueCommand(EventFacade* eventStorage);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};




class ShowFloatCommand : public Command {
private:
	EventFacade* eventFacade;
	vector<Event> eventsToShow;

public:
	ShowFloatCommand(EventFacade* eventStorage);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};




class ShowImportanceCommand : public Command {
private:
	EventFacade* eventFacade;
	vector<Event> eventsToShow;
	int importanceLevel;

public:
	ShowImportanceCommand(EventFacade* eventStorage, int importance);
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};




class NullCommand : public Command {
public:
	NullCommand();
	void execute();
	vector<Event> getEventVector();
	Event getEvent();
	void undo();
};


#endif