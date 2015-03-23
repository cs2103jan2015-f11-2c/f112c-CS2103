#include "Logic.h"

//for logging
const string Logic::LOG_FILE_NAME = "LogicLog.txt";
const string Logic::CREATING_ADD = "creating add command";
const string Logic::CREATING_DELETE = "creating delete command";
const string Logic::CREATING_EDIT = "creating edit command";
const string Logic::CREATING_SHOW = "creating show command";
const string Logic::CREATING_SHOWFLOAT = "creating showfloat command";
const string Logic::CREATING_SEARCH = "creating search command";
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

	Parser::commandType commandType = parserPtr->getCommandType();
	Event userEvent = parserPtr->getEvent();
	string nameOfEvent = parserPtr->getNameOfEvent();
	bool isDone = true;
	
	ICommand* commandPtr = queueCommand(executor, commandType, userEvent, nameOfEvent);
	setDisplay(commandPtr, commandType, userEvent, nameOfEvent, isDone);

	deleteParserPtr();

	return isDone;
}

ICommand* Logic::queueCommand(Executor& executor, Parser::commandType command, Event userEvent, string nameOfEvent) {
	switch (command) {
	case Parser::ADD:
	case Parser::ADDFLOAT: {
		log(CREATING_ADD);
		ICommand* addCommand = new AddCommand(&eventStore, userEvent);
		return executor.execute(addCommand);
		break;
						   }
	
	case Parser::DELETE_: {
		log(CREATING_DELETE);
		int id = convertNameToID(nameOfEvent);

		Event eventToDelete;
		eventToDelete.setName(nameOfEvent);
		if (id != INVALID_NUMBER) {
			eventToDelete = display.getEventFromID(id);
		}
	
		ICommand* deleteCommand = new DeleteCommand(&eventStore, id, eventToDelete);
		return executor.execute(deleteCommand);
		break;
						  }

	case Parser::EDIT: {
		log(CREATING_EDIT);
		int id = convertNameToID(nameOfEvent);
		
		Event eventToEdit;
		eventToEdit.setName(nameOfEvent);
		if (id != INVALID_NUMBER) {
			eventToEdit = display.getEventFromID(id);
		}

		ICommand* editCommand = new EditCommand(&eventStore, id, eventToEdit, userEvent);
		return executor.execute(editCommand);
		break;
					   }

	case Parser::SHOW: {
		log(CREATING_SHOW);
		ICommand* showCommand = new ShowCommand(&eventStore, userEvent);
		return executor.execute(showCommand);
		break;
					   }

	case Parser::SHOWFLOAT: {
		log(CREATING_SHOWFLOAT);
		ICommand* showFloatCommand = new ShowFloatCommand(&eventStore);
		return executor.execute(showFloatCommand);
		break;
					   }

	case Parser::ERROR_: {
		Event emptyEvent;
		return new AddCommand(&eventStore, emptyEvent);
		break;
						 }

	default:
		break;
	}
}

void Logic::setDisplay(ICommand* commandPtr, Parser::commandType command, Event userEvent, string nameOfEvent, bool& isDone) {
	switch (command) {
	case Parser::ADD: {
		vector<Event> normalEvents = commandPtr->getEventVector();
		vector<Event> floatingEvents = display.getFloatingEvents();
		string feedback = userEvent.getName() + Display::ADDED_MESSAGE;
		vector<tm> tmVec;
		tmVec.push_back(userEvent.getStartDate());
		tmVec.push_back(userEvent.getEndDate());
		int id = userEvent.getID();

		display.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id);
		break;
						   }
	
	case Parser::ADDFLOAT: {		
		vector<Event> normalEvents = display.getNormalEvents();
		vector<Event> floatingEvents = commandPtr->getEventVector();
		string feedback = userEvent.getName() + Display::ADDED_MESSAGE;
		vector<tm> tmVec = display.getTempMainDisplayLabel();
		int id = userEvent.getID();

		display.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id);
		break;
						   }

	case Parser::DELETE_: {
		vector<Event> normalEvents, floatingEvents, tempEvents = commandPtr->getEventVector() ;

		//more than one event found case
		if (!commandPtr->getIsComplete()) {
			normalEvents = commandPtr->getEventVector();
			floatingEvents = display.getFloatingEvents();
			vector<tm> tmVec = display.getTempMainDisplayLabel();
			display.setAllEvents(normalEvents, floatingEvents, Display::CHOOSE_EVENT_MESSAGE, tmVec, Display::GARBAGE_INT);
			return;
		}

		//no event found case
		if (!tempEvents.empty() && tempEvents[0].getID() == INVALID_NUMBER) {
			isDone = false;
			string feedback = nameOfEvent + Display::EVENT_NOT_FOUND_MESSAGE;
			//display.set???
			return;
		}

		//normal case
		if (commandPtr->getIsFloating()) {
			normalEvents = display.getNormalEvents();
			floatingEvents = commandPtr->getEventVector();
		} else {
			normalEvents = commandPtr->getEventVector();
			floatingEvents = display.getFloatingEvents();
		}
		Event deletedEvent = commandPtr->getEvent();
		string feedback = deletedEvent.getName() + Display::DELETED_MESSAGE;
		vector<tm> tmVec = display.getTempMainDisplayLabel();

		display.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, Display::GARBAGE_INT);
		break;
						  }
	
	case Parser::EDIT: {
		vector<Event> normalEvents, floatingEvents;
		vector<tm> tmVec;
		int id;

		if (commandPtr->getIsFloating()) {
			normalEvents = display.getNormalEvents();
			floatingEvents = commandPtr->getEventVector();
			tmVec = display.getTempMainDisplayLabel();
			id = floatingEvents[0].getID();
		} else {
			normalEvents = commandPtr->getEventVector();
			floatingEvents = display.getFloatingEvents();
			tmVec.push_back(normalEvents[0].getStartDate());
			tmVec.push_back(normalEvents[0].getEndDate());
			id = normalEvents[0].getID();
		}
		string feedback = nameOfEvent + Display::DELETED_MESSAGE;

		display.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id);
		break;
					   }

	case Parser::SHOW: {
		vector<Event> normalEvents = commandPtr->getEventVector();
		vector<Event> floatingEvents = display.getFloatingEvents();
		string feedback = Display::SHOW_MESSAGE + nameOfEvent;
		vector<tm> tmVec;
		tmVec.push_back(userEvent.getStartDate());
		tmVec.push_back(userEvent.getEndDate());
		mktime(&tmVec[0]);
		mktime(&tmVec[1]);

		display.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, Display::GARBAGE_INT);
		break;
					   }

	case Parser::SHOWFLOAT: {
		vector<Event> normalEvents = display.getNormalEvents();
		vector<Event> floatingEvents = commandPtr->getEventVector();
		string emptyFeedback;
		vector<tm> tmVec = display.getTempMainDisplayLabel();

		display.setAllEvents(normalEvents, floatingEvents, emptyFeedback, tmVec, Display::GARBAGE_INT);
		break;
							}

	case Parser::ERROR_: {
		delete commandPtr;
		commandPtr = NULL;
		isDone = false;

		string feedback = userEvent.getFeedback();

		//display.set???
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
			return display.getIDFromName(name);
		}
}

string Logic::commandToString(Parser::commandType command) {
	switch (command) {

	case Parser::ADD:
	case Parser::ADDFLOAT:
		return CREATING_ADD;

	case Parser::DELETE_: 
		return CREATING_DELETE;

	case Parser::EDIT:
		return CREATING_EDIT;

	case Parser::SHOW:
		return CREATING_SHOW;

	case Parser::SEARCH:
		return CREATING_SEARCH;

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




//////////////////////////////////////old method///////////////////////////////////////////////////////////
/*
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
*/