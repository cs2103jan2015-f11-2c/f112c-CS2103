#include "Logic.h"


const int Logic::INVALID_NUMBER = -1;


	//CONSTRUCTOR, DESTRUCTOR
Logic::Logic(void) {
	parserPtr = NULL;
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

	switch (command) {
	case Parser::ADDFLOAT: {
		tempEvents = eventStore.addEvent(userEvent);
		display.setFloatingEvents(tempEvents);
		
		int newID = display.getNewID();
		tempEvents = display.getNormalEvents();
		display.setNormalEvents(tempEvents, newID);

		feedback = userEvent.getName() + Display::ADDED_MESSAGE;
		display.setFeedbackStrings(feedback);
		break;
						   }
	
	case Parser::ADD: {
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
				setDisplay(isFloat, tempEvents);
		
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
			setDisplay(isFloat, tempEvents);
			
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
				setDisplay(isFloat, tempEvents);
		
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
			setDisplay(isFloat, tempEvents);
		
			feedback = eventToEdit.getName() + Display::EDITED_MESSAGE;
			display.setFeedbackStrings(feedback);
		}

		break;
					   }

	case Parser::SHOW:
		break;

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

void Logic::setDisplay(bool isFloat, vector<Event> eventsToSet) {
	if (isFloat) {
		display.setFloatingEvents(eventsToSet);
		} else {
			int id = display.getNewID();
			display.setNormalEvents(eventsToSet, id);
		}
}

void Logic::log(string logString) {
	return;
}