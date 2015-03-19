#include "Logic.h"

//for logging
const string Logic::LOG_FILE_NAME = "logicLog.txt";
const string Logic::ADDFLOAT_STRING = "executing addfloat command";
const string Logic::ADD_STRING = "executing add command";
const string Logic::DELETE_STRING = "executing delete command";
const string Logic::EDIT_STRING = "executing edit command";
const string Logic::SHOW_STRING = "executing show command";
const string Logic::SEARCH_STRING = "executing search command";
const string Logic::ERROR_STRING = "executing error command";

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
	int index, id;
	vector<Event> tempEvents;

	log(commandToString(command));
	
	switch (command) {
	case Parser::ADDFLOAT: {
		try {
			if (!userEvent.getIsFloating()) {
				throw EXCEPTION_WRONG_ISFLOATING;
			}
		} catch (string exception) {
				log(exception);
			}
		
		int newID = userEvent.getID();
		tempEvents = eventStore.addEvent(userEvent);
		display.setFloatingEvents(tempEvents, newID);
		
		tempEvents = display.getNormalEvents();
		display.setNormalEvents(tempEvents, newID);

		feedback = userEvent.getName() + Display::ADDED_MESSAGE;
		display.setFeedbackStrings(feedback);
		break;
						   }
	
	case Parser::ADD: {
		try {
			if (userEvent.getIsFloating()) {
				throw EXCEPTION_WRONG_ISFLOATING;
			}
		} catch (string exception) {
				log(exception);
			}

		int newID = userEvent.getID();
		tempEvents = eventStore.addEvent(userEvent);
		display.setNormalEvents(tempEvents, newID);

		feedback = userEvent.getName() + Display::ADDED_MESSAGE;
		display.setFeedbackStrings(feedback);
		break;
					  }

	case Parser::DELETE_: {
		id = convertNameToID(eventName);

		Event uselessEvent;

		if (id == INVALID_NUMBER) {
			//if desired event is not in display vectors, check if it is in eventStore
			tempEvents = eventStore.checkMultipleResults(eventName);

			int numResults = tempEvents.size();

			switch (numResults) {
			//if eventStore returns no events, means the event user wants to delete does not exist
			case 0: {
				feedback = eventName + Display::EVENT_NOT_FOUND_MESSAGE;
				display.setFeedbackStrings(feedback);
				break;
					}


			//if eventStore returns 1 event, delete that event
			case 1: {
				uselessEvent = tempEvents[0];
				id = uselessEvent.getID();

				tempEvents = eventStore.deleteEvent(id, uselessEvent);

				bool isFloat = tempEvents[0].getIsFloating();
				setDisplay(isFloat, tempEvents, INVALID_NUMBER);
		
				feedback = eventName + Display::DELETED_MESSAGE;
				display.setFeedbackStrings(feedback);

				break;
					}


			//if eventStore returns >1 event, ????
			default:
				break;
			}

		} else { //if desired event found in display vectors, call eventStore to delete it immediately
			tempEvents = eventStore.deleteEvent(id, uselessEvent);
			
			bool isFloat = tempEvents[0].getIsFloating();
			setDisplay(isFloat, tempEvents, INVALID_NUMBER);
			
			feedback = eventName + Display::DELETED_MESSAGE;
			display.setFeedbackStrings(feedback);
		}
		
		break;
						  }

	case Parser::EDIT: {
		Event editedEvent = parserPtr->getEvent();
		id = convertNameToID(eventName);

		//if desired event is not in display vectors, check if it is in eventStore
		if (id == INVALID_NUMBER) {
			tempEvents = eventStore.checkMultipleResults(eventName);

			int numResults = tempEvents.size();

			switch (numResults) {
			//if eventStore returns no events, means the event user wants to edit does not exist
			case 0: {
				feedback = eventName + Display::EVENT_NOT_FOUND_MESSAGE;
				display.setFeedbackStrings(feedback);
				break;
					}


			//if eventStore returns 1 event, edit that event
			case 1: {
				Event eventToEdit = tempEvents[0];
				id = eventToEdit.getID();

				tempEvents = eventStore.editEvent(id, eventToEdit, editedEvent);

				bool isFloat = tempEvents[0].getIsFloating();
				setDisplay(isFloat, tempEvents, id);
		
				feedback = eventToEdit.getName() + Display::EDITED_MESSAGE;
				display.setFeedbackStrings(feedback);

				break;
					}


			//if eventStore returns >1 event, ????
			default:
				break;
			}

		} else { //if desired event found in display vectors, call eventStore to edit it immediately
			Event eventToEdit = display.getEventFromID(id);
			tempEvents = eventStore.editEvent(id, eventToEdit, editedEvent);
			
			bool isFloat = tempEvents[0].getIsFloating();
			setDisplay(isFloat, tempEvents, id);
		
			feedback = eventToEdit.getName() + Display::EDITED_MESSAGE;
			display.setFeedbackStrings(feedback);
		}

		break;
					   }

	case Parser::SHOW: {
		Event eventsToShow = parserPtr->getEvent();

		//eventStore.???

		break;
					   }

	case Parser::SEARCH:
		break;

	case Parser::ERROR_:
		break;

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

void Logic::setDisplay(bool isFloat, vector<Event> eventsToSet, int id) {
	if (isFloat) {
		display.setFloatingEvents(eventsToSet, id);
		} else {
			display.setNormalEvents(eventsToSet, id);
		}
}

string Logic::commandToString(Parser::commandType command) {
	switch (command) {

	case Parser::ADDFLOAT:
		return ADDFLOAT_STRING;
	
	case Parser::ADD:
		return ADD_STRING;

	case Parser::DELETE_: 
		return DELETE_STRING;

	case Parser::EDIT:
		return EDIT_STRING;

	case Parser::SHOW:
		return SHOW_STRING;

	case Parser::SEARCH:
		return SEARCH_STRING;

	case Parser::ERROR_:
		return ERROR_STRING;

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