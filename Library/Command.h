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


	//common api
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




//Add Command
class AddCommand : public Command {
private:
	Event userEvent;

public:
	AddCommand(EventFacade* eventStorage, Event e, vector<tm> currentShowing);
	void execute();
	Event getEvent();
	void undo();
};




//Complete Command
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





//Uncomplete Command
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





//Delete Command
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




//Edit Command
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




//Search Command
class SearchCommand : public Command {
private:
	string searchString;

public:
	SearchCommand(EventFacade* eventStorage, string s);
	void execute();
	Event getEvent();
	void undo();
};




//Show Command
class ShowCommand : public Command {
private:
	Event eventRangeToShow;

public:
	ShowCommand(EventFacade* eventStorage, Event e);
	void execute();
	Event getEvent();
	void undo();
};




//Show All Command
class ShowAllCommand : public Command {
private:

public:
	ShowAllCommand(EventFacade* eventStorage);
	void execute();
	Event getEvent();
	void undo();
};




//Show All Important Command
class ShowAllImportantCommand : public Command {
private:

public:
	ShowAllImportantCommand(EventFacade* eventStorage);
	void execute();
	Event getEvent();
	void undo();
};




//Show Completed Command
class ShowCompletedCommand : public Command {
private:

public:
	ShowCompletedCommand(EventFacade* eventStorage);
	void execute();
	Event getEvent();
	void undo();
};




//Show Float Command
class ShowFloatCommand : public Command {
private:

public:
	ShowFloatCommand(EventFacade* eventStorage);
	void execute();
	Event getEvent();
	void undo();
};




//Show Importance Command
class ShowImportanceCommand : public Command {
private:
	int importanceLevel;

public:
	ShowImportanceCommand(EventFacade* eventStorage, int importance);
	void execute();
	Event getEvent();
	void undo();
};




//Null Command
class NullCommand : public Command {
private:

public:
	NullCommand();
	void execute();
	Event getEvent();
	void undo();
};


#endif