#include "Logic.h"

//for logging
const string Logic::LOG_FILE_NAME = "LogicLog.txt";
const string Logic::ADDFLOAT_EXECUTING = "executing addfloat command";
const string Logic::ADD_EXECUTING = "executing add command";
const string Logic::DELETE_EXECUTING = "executing delete command";
const string Logic::EDIT_EXECUTING = "executing edit command";
const string Logic::SHOW_EXECUTING = "executing show command";
const string Logic::SEARCH_EXECUTING = "executing search command";
const string Logic::ERROR_EXECUTING = "executing error command";
const string Logic::CASE_0 = "entered case 0";
const string Logic::CASE_1 = "entered case 1";

//for exceptions
const string Logic::EXCEPTION_WRONG_ISFLOATING = "exception: isFloating set wrong";

const int Logic::INVALID_NUMBER = -1;


	//CONSTRUCTOR, DESTRUCTOR
Logic::Logic(void) {
	parserPtr = NULL;

	ofstream outFile(LOG_FILE_NAME);
	outFile.clear();
	outFile.close();
}

Logic::~Logic() {
	deleteParserPtr();
}


	//GETTERS
Parser::commandType Logic::getCommand() {
	return parserPtr->getCommandType();
}

Event Logic::getEvent() {
	return parserPtr->getEvent();
}

EventStorage Logic::getEventStorage() {
	return eventStore;
}

vector<Display::EVENT_STRING> Logic::getFloatingStrings() {
	return display.getFloatingDisplayStrings();
}

vector<Display::EVENT_STRING> Logic::getMainStrings() {
	return display.getMainDisplayStrings();
}

vector<string> Logic::getFeedbackStrings() {
	return display.getFeedbackDisplayStrings();
}

vector<string> Logic::getErrorString() {
	return display.getErrorStrings();
}

string Logic::getMainDisplayLabel() {
	return display.getMainDisplayLabel();
}


	//EXECUTORS
//called by UI with original user input string, returns vector of Events after input fully executed
bool Logic::executeUserInput(string input) {
	parserPtr = new Parser(input);

	Parser::commandType command = getCommand();
	Event userEvent = getEvent();
	bool isDone = true;

	executeCommand(command, userEvent, isDone);

	deleteParserPtr();

	return isDone;
}

//executes exact user command after parsing
void Logic::executeCommand(Parser::commandType command, Event userEvent, bool& isDone) {
	string eventName = parserPtr->getNameOfEvent(), feedback;

	log(commandToString(command));
	
	switch (command) {
	case Parser::ADDFLOAT: {
		assert(userEvent.getIsFloating());

		int newID = userEvent.getID();
		vector<Event> floatingEvents = eventStore.addEvent(userEvent);
		vector<Event> normalEvents = display.getNormalEvents();
		vector<tm> tmVec = display.getTempMainDisplayLabel();
		feedback = userEvent.getName() + Display::ADDED_MESSAGE;;

		display.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, newID);
		
		break;
						   }
	
	case Parser::ADD: {
		assert(!userEvent.getIsFloating());

		int newID = userEvent.getID();
		vector<Event> floatingEvents;
		vector<Event> normalEvents = eventStore.addEvent(userEvent);
		feedback = userEvent.getName() + Display::ADDED_MESSAGE;
		vector<tm> tmRange;
		tmRange.push_back(userEvent.getStartDate());
		tmRange.push_back(userEvent.getEndDate());

		display.setAllEvents(normalEvents, floatingEvents, feedback, tmRange, newID);

		break;
					  }

	case Parser::DELETE_: {
		int id = convertNameToID(eventName);

		Event uselessEvent;

		if (id == INVALID_NUMBER) {
			//if desired event is not in display vectors, check if it is in eventStore
			vector<Event> tempEvents = eventStore.checkMultipleResults(eventName);

			int numResults = tempEvents.size();

			switch (numResults) {
			//if eventStore returns no events, means the event user wants to delete does not exist
			case 0: {
				log(CASE_0);

				vector<Event> floatingEvents = display.getFloatingEvents();
				vector<Event> normalEvents = display.getNormalEvents();
				feedback = eventName + Display::EVENT_NOT_FOUND_MESSAGE;
				vector<tm> tmVec = display.getTempMainDisplayLabel();

				display.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, Display::GARBAGE_INT);
				break;
					}

			//if eventStore returns 1 event, delete that event
			case 1: {
				log(CASE_1);

				bool isFloat = tempEvents[0].getIsFloating();
				vector<Event> floatingEvents, normalEvents;

				if (isFloat) {
					floatingEvents = eventStore.deleteEvent(id, tempEvents[0]);
					normalEvents = display.getNormalEvents();
				} else {
					floatingEvents = display.getFloatingEvents();
					normalEvents = eventStore.deleteEvent(id, tempEvents[0]);
				}

				feedback = eventName + Display::DELETED_MESSAGE;
				vector<tm> tmVec = display.getTempMainDisplayLabel();
				
				display.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, Display::GARBAGE_INT);
				break;
					}


			//if eventStore returns >1 event, ????
			default:
				break;
			}

		} else { //if desired event found in display vectors, call eventStore to delete it immediately
			bool isFloat = display.getIsFloatingFromID(id);
			vector<Event> floatingEvents, normalEvents;
			Event emptyEvent;

			if (isFloat) {
				floatingEvents = eventStore.deleteEvent(id, emptyEvent);
				normalEvents = display.getNormalEvents();
				} else {
					floatingEvents = display.getFloatingEvents();
					normalEvents = eventStore.deleteEvent(id, emptyEvent);
				}
			
			feedback = eventName + Display::DELETED_MESSAGE;
			vector<tm> tmVec = display.getTempMainDisplayLabel();
			
			display.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, Display::GARBAGE_INT);
		}
		break;
						  }

	case Parser::EDIT: {
		Event editedEvent = parserPtr->getEvent();
		int id = convertNameToID(eventName);

		//if desired event is not in display vectors, check if it is in eventStore
		if (id == INVALID_NUMBER) {
			vector<Event> tempEvents = eventStore.checkMultipleResults(eventName);

			int numResults = tempEvents.size();

			switch (numResults) {
			//if eventStore returns no events, means the event user wants to edit does not exist
			case 0: {
				log(CASE_0);

				vector<Event> floatingEvents = display.getFloatingEvents();
				vector<Event> normalEvents = display.getNormalEvents();
				feedback = eventName + Display::EVENT_NOT_FOUND_MESSAGE;
				vector<tm> tmVec = display.getTempMainDisplayLabel();

				display.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, Display::GARBAGE_INT);
				break;
					}


			//if eventStore returns 1 event, edit that event
			case 1: {
				log(CASE_1);

				Event eventToEdit = tempEvents[0];
				bool isFloat = eventToEdit.getIsFloating();
				id = eventToEdit.getID();
				vector<Event> floatingEvents, normalEvents;
				vector<tm> tmVec;

				if (isFloat) {
					floatingEvents = eventStore.editEvent(id, eventToEdit, editedEvent);
					normalEvents = display.getNormalEvents();
					tmVec.push_back(floatingEvents[0].getStartDate());
					tmVec.push_back(floatingEvents[0].getEndDate());
				} else {
					floatingEvents = display.getFloatingEvents();
					normalEvents = eventStore.editEvent(id, eventToEdit, editedEvent);
					tmVec.push_back(normalEvents[0].getStartDate());
					tmVec.push_back(normalEvents[0].getEndDate());
				}
		
				feedback = eventToEdit.getName() + Display::EDITED_MESSAGE;
				
				display.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id);
				break;
					}


			//if eventStore returns >1 event, ????
			default:
				break;
			}

		} else { //if desired event found in display vectors, call eventStore to edit it immediately
			bool isFloat = display.getIsFloatingFromID(id);
			Event eventToEdit = display.getEventFromID(id);
			vector<Event> floatingEvents, normalEvents;
			vector<tm> tmVec;

			if (isFloat) {
					floatingEvents = eventStore.editEvent(id, eventToEdit, editedEvent);
					normalEvents = display.getNormalEvents();
					tmVec.push_back(floatingEvents[0].getStartDate());
					tmVec.push_back(floatingEvents[0].getEndDate());
				} else {
					floatingEvents = display.getFloatingEvents();
					normalEvents = eventStore.editEvent(id, eventToEdit, editedEvent);
					tmVec.push_back(normalEvents[0].getStartDate());
					tmVec.push_back(normalEvents[0].getEndDate());
				}

			feedback = eventToEdit.getName() + Display::EDITED_MESSAGE;

			display.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id);
		}
		break;
					   }

	case Parser::SHOW: {
		Event eventRangeToShow = parserPtr->getEvent();
		
		vector<tm> tmVec;
		tmVec.push_back(eventRangeToShow.getStartDate());
		tmVec.push_back(eventRangeToShow.getEndDate());
		

		vector<Event> eventsToShow = eventStore.showDates(eventRangeToShow);
		vector<Event> floatingEvents = display.getFloatingEvents();
		string emptyString;

		display.setAllEvents(eventsToShow, floatingEvents, emptyString, tmVec, Display::GARBAGE_INT);
		break;
					   }

	case Parser::SEARCH:
		break;

	case Parser::ERROR_: {
		break;
						 }

	default:
		break;
	}
}

void Logic::deleteParserPtr() {
	delete parserPtr;
	parserPtr = NULL;
}


	//OTHERS
bool Logic::isNumber(string s) {
	for (int i = 0 ; i < s.size() ; i++) {
		if (!isdigit(s[i])) {
			return false;
		}
	}
	return true;
}

int Logic::convertNameToID(string name) {
	if (isNumber(name)) {
			int index = std::stoi(name);
			return display.getIDFromIndex(index);
		} else {
			return INVALID_NUMBER;
		}
}

string Logic::commandToString(Parser::commandType command) {
	switch (command) {

	case Parser::ADDFLOAT:
		return ADDFLOAT_EXECUTING;
	
	case Parser::ADD:
		return ADD_EXECUTING;

	case Parser::DELETE_: 
		return DELETE_EXECUTING;

	case Parser::EDIT:
		return EDIT_EXECUTING;

	case Parser::SHOW:
		return SHOW_EXECUTING;

	case Parser::SEARCH:
		return SEARCH_EXECUTING;

	case Parser::ERROR_:
		return ERROR_EXECUTING;

	default:
		break;
	}
}

void Logic::log(string logString) {
	ofstream outFile(LOG_FILE_NAME);
	
	logStrings.push_back(logString);
	for (int i = 0 ; i < logStrings.size() ; i++) {
		outFile << logStrings[i] << endl;
	}

	outFile.close();

	return;
}