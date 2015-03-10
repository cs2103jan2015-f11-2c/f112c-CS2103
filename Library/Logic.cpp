#include "Logic.h"


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

vector<string> Logic::getMainStrings() {
	return display.getMainDisplayStrings();
}

vector<string> Logic::getFeedbackStrings() {
	return display.getFeedbackDisplayStrings();
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
	switch (command) {
	case Parser::ADDFLOAT:
		display.setFloatingEvents(eventStore.addEvent(userEvent));
		break;

	case Parser::ADDFULLDAY:
		//resultEvent = eventStore.addEvent(userEvent);
		break;
	
	case Parser::ADD:
		//resultEvent = eventStore.addEvent(userEvent);
		break;

	case Parser::ADDSTART:
		//resultEvent = eventStore.addEvent(userEvent);
		break;

	case Parser::ADDMULFULLDAYS:
		//resultEvent = eventStore.addEvent(userEvent);
		break;

	case Parser::ADDMULDAYS:
		//resultEvent = eventStore.addEvent(userEvent);
		break;

	case Parser::DELETE_:
		int userIndex = parserPtr->getIndex();
		vector<Event> floatingEvents = display.getFloatingEvents();

		if (userIndex <= floatingEvents.size()) {
			eventStore.deleteEvent(userIndex, floatingEvents);
		}

		//else {
		//}

		break;

	case Parser::EDIT:
		break;

	case Parser::SHOWDAY:
		break;

	case Parser::SHOWMTH:
		break;

	case Parser::SHOWYR:
		break;

	case Parser::SHOWUSER:
		//return eventStore.searchAllComponentsOfEvent(userEvent.getName());
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
