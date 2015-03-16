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

vector<string> Logic::getFloatingStrings() {
	return display.getFloatingDisplayStrings();
}

vector<Display::MAIN_EVENT> Logic::getMainStrings() {
	return display.getMainDisplayStrings();
}

vector<string> Logic::getFeedbackStrings() {
	return display.getFeedbackDisplayStrings();
}

string Logic::getErrorString() {
	return "";
}

	//EXECUTORS
//called by UI with original user input string, returns vector of Events after input fully executed
bool Logic::executeUserInput(string input) {
	parserPtr = new Parser(input);
	
	Parser::commandType command = getCommand();
	Event userEvent = getEvent();

	executeCommand(command, userEvent);

	deleteParserPtr();

	return true;
}

//executes exact user command after parsing
void Logic::executeCommand(Parser::commandType command, Event userEvent) {
	string eventName = parserPtr->getNameOfEvent();
	int index, id;
	vector<Event> tempEvents;

	switch (command) {
	case Parser::ADDFLOAT: {
		display.setFloatingEvents(eventStore.addEvent(userEvent));
		display.setFeedbackStrings(userEvent.getName() + Display::ADDED_MESSAGE);
		break;
						   }

	case Parser::ADDFULLDAY:
		
		break;
	
	case Parser::ADD: {
		display.setNormalEvents(eventStore.addEvent(userEvent));
		display.setFeedbackStrings(userEvent.getName() + Display::ADDED_MESSAGE);
		break;
					  }

	case Parser::ADDSTART:
	
		break;

	case Parser::ADDMULFULLDAYS:
	
		break;

	case Parser::ADDMULDAYS:
		
		break;

	case Parser::DELETE_: {
		id = convertNameToID(eventName);

		tempEvents = eventStore.deleteEvent(id, eventName);

		bool isFloat = tempEvents[0].getIsFloating();

		setDisplay(isFloat, tempEvents);
		
		display.setFeedbackStrings(eventName + Display::DELETED_MESSAGE);

		break;
						  }

	case Parser::EDIT: {
		Event tempEvent = parserPtr->getEvent();

		id = convertNameToID(eventName);

		tempEvents = eventStore.editEvent(id, eventName, tempEvent);

		bool isFloat = tempEvents[0].getIsFloating();

		setDisplay(isFloat, tempEvents);

		display.setFeedbackStrings(userEvent.getName() + Display::EDITED_MESSAGE);

		break;
					   }

	case Parser::SHOWDAY:
		break;

	case Parser::SHOWMTH:
		break;

	case Parser::SHOWYR:
		break;

	case Parser::SHOWUSER:

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
			return display.getID(index);
		} else {
			return INVALID_NUMBER;
		}
}

void Logic::setDisplay(bool isFloat, vector<Event> eventsToSet) {
	if (isFloat) {
		display.setFloatingEvents(eventsToSet);
		} else {
			display.setNormalEvents(eventsToSet);
		}
}