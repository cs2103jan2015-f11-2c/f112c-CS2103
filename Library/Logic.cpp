
#include "Logic.h"


	//CONSTRUCTOR
Logic::Logic(void) {
	parserPtr = NULL;
}


	//GETTERS
Parser::commandType Logic::getCommand() {
	return parserPtr->getCommandType();
}

Event Logic::getEvent() {
	return parserPtr->getEvent();
}


	//EXECUTORS
//called by UI with original user input string, returns vector of Events after input fully executed
vector<Event> Logic::executeUserInput(string input) {
	parserPtr = new Parser(input);
	
	Parser::commandType command = getCommand();
	Event userEvent = getEvent();

	vector<Event> resultEvent = executeCommand(command, userEvent);

	deleteParserPtr();

	return resultEvent;
	/*
	Event e;

	vector<string> svec;
	svec.push_back("#school");

	e.setName("exam");
	e.setFeedback("event added");
	e.setStartDate(6, 2, 2015);
	e.setStartTime(11, 0);
	e.setEndDate(6, 2, 2015);
	e.setEndTime(12, 0);
	e.setIsFloating(false);
	e.setDescription("foo");
	e.setTags(svec);


	vector<Event> v;
	v.push_back(e);
	
	return v;
	*/
}

//executes exact user command after parsing
vector<Event> Logic::executeCommand(Parser::commandType command, Event userEvent) {
	vector<Event> resultEvent;
	
	switch (command) {
	case Parser::ADDFLOAT:
		resultEvent = eventStore.addEvent(userEvent);
		break;

	case Parser::ADDFULLDAY:
		resultEvent = eventStore.addEvent(userEvent);
		break;
	
	case Parser::ADD:
		resultEvent = eventStore.addEvent(userEvent);
		break;

	case Parser::ADDSTART:
		resultEvent = eventStore.addEvent(userEvent);
		break;

	case Parser::ADDMULFULLDAYS:
		resultEvent = eventStore.addEvent(userEvent);
		break;

	case Parser::ADDMULDAYS:
		resultEvent = eventStore.addEvent(userEvent);
		break;

	case Parser::DELETE_:
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
		return eventStore.searchAllComponentsOfEvent(userEvent.getName());
		break;

	case Parser::ERROR_:
		break;

	default:
		break;
	}

	return resultEvent;
}

void Logic::deleteParserPtr() {
	delete parserPtr;
	parserPtr = NULL;
}
