//@author A0111089L
#pragma once

#ifndef COMMAND_H
#define COMMAND_H

#include <algorithm>
#include "EventFacade.h"
#include "LogicLog.h"

using std::find;


class Command {
public:
	static const int INVALID_NUMBER;
	static const int SIZE_ZERO;
	static const int SIZE_ONE;
	static const int SIZE_TWO;


	//virtual methods
	virtual void execute() = 0;
	virtual Event getEvent() = 0;
	virtual void undo() = 0;

	//common methods
	vector<Event> getEventVector();
	bool getIsFloating();
	bool getIsExecuted();
	bool getIsUndoable();
	int getNumEvents(vector<Event> eventVec);
	Event getEventFromID(vector<Event> eventVec, int id);
	vector<Event> getShowEventVector(Event userEvent, vector<tm> currentShowingTM);
	void checkPartialMatches(int numResults, vector<Event> tempEvents);
	void chooseExactMatches(Event& userEvent);
	Event createInvalidEvent();


protected:
	EventFacade* eventFacade;
	vector<Event> eventsToShow;
	vector<tm> currentShowingTM;
	bool isFloating;
	bool isExecuted;
	bool isUndoable;
	LogicLog logger;
};




class AddCommand : public Command {
private:
	Event userEvent;

public:
	AddCommand(EventFacade* eventStorage, Event e, vector<tm> currentShowing);
	void execute();
	Event getEvent();
	void undo();
};




class CompleteCommand : public Command {
private:
	int id;
	Event userEvent;

public:
	CompleteCommand(EventFacade* eventStorage, int eventID, Event userEvent, vector<tm> currentShowing);
	void execute();
	Event getEvent();
	void undo();

	void completeImmediately();
	void completeExact(vector<Event> tempEvents);
};




class UncompleteCommand : public Command {
private:
	int id;
	Event userEvent;

public:
	UncompleteCommand(EventFacade* eventStorage, vector<Event> events, vector<tm> currentShowing);
	void execute();
	Event getEvent();
	void undo();

	void uncompleteImmediately();
};




class DeleteCommand : public Command {
private:
	int id;
	Event userEvent;

public:
	DeleteCommand(EventFacade* eventStorage, int eventID, Event userEvent, vector<tm> currentShowing);
	void execute();
	Event getEvent();
	void undo();

	void deleteImmediately();
	void deleteExact(vector<Event> tempEvents);
};




class EditCommand : public Command {
private:
	int id;
	Event eventToEdit, editedEvent;
	bool isEdited;

public:
	EditCommand(EventFacade* eventStorage, int eventID, Event toEdit, Event edited, vector<tm> currentShowing);
	void execute();
	Event getEvent();
	void undo();

	void editImmediately();
	void editExact(vector<Event> tempEvents);
	void redoEdit();
};




class SearchCommand : public Command {
private:
	string searchString;

public:
	SearchCommand(EventFacade* eventStorage, string s);
	void execute();
	Event getEvent();
	void undo();
};




class ShowCommand : public Command {
private:
	Event eventRangeToShow;

public:
	ShowCommand(EventFacade* eventStorage, Event e);
	void execute();
	Event getEvent();
	void undo();
};




class ShowAllCommand : public Command {
private:

public:
	ShowAllCommand(EventFacade* eventStorage);
	void execute();
	Event getEvent();
	void undo();
};




class ShowAllImportantCommand : public Command {
private:

public:
	ShowAllImportantCommand(EventFacade* eventStorage);
	void execute();
	Event getEvent();
	void undo();
};




class ShowCompletedCommand : public Command {
private:

public:
	ShowCompletedCommand(EventFacade* eventStorage);
	void execute();
	Event getEvent();
	void undo();
};




class ShowFloatCommand : public Command {
private:

public:
	ShowFloatCommand(EventFacade* eventStorage);
	void execute();
	Event getEvent();
	void undo();
};




class ShowImportanceCommand : public Command {
private:
	int importanceLevel;

public:
	ShowImportanceCommand(EventFacade* eventStorage, int importance);
	void execute();
	Event getEvent();
	void undo();
};




class NullCommand : public Command {
private:

public:
	NullCommand();
	void execute();
	Event getEvent();
	void undo();
};


#endif