#include "Logic.h"

//for logging
const string Logic::LOG_FILE_NAME = "LogicLog.txt";
const string Logic::CREATING_ADD = "creating add command";
const string Logic::CREATING_DELETE = "creating delete command";
const string Logic::CREATING_EDIT = "creating edit command";
const string Logic::CREATING_SHOW = "creating show command";
const string Logic::CREATING_SHOWALL = "creating show all command";
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

vector<tm> Logic::getTempMainDisplayLabel() {
	return display.getTempMainDisplayLabel();
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

	case Parser::SHOWALL: {
		log(CREATING_SHOWALL);
		ICommand* showAllCommand = new ShowAllCommand(&eventStore);
		return executor.execute(showAllCommand);
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

		if (!commandPtr->getIsComplete()) {
			setEventVector(normalEvents, floatingEvents, tempEvents);
			
			//more than 1 exact match
			if ( (!floatingEvents.empty() && floatingEvents[0].getName() == nameOfEvent) |
				(!normalEvents.empty() && normalEvents[1].getName() == nameOfEvent) ) {
				vector<tm> tmVec;
				tmVec.push_back(normalEvents[1].getStartDate());
				tmVec.push_back(normalEvents[normalEvents.size() - 1].getEndDate());
				mktime(&tmVec[0]);
				mktime(&tmVec[1]);
				
				display.setAllEvents(normalEvents, floatingEvents, Display::CHOOSE_EVENT_MESSAGE, tmVec, Display::GARBAGE_INT);
				return;
			}
			
			//at least 1 partial match
			if (!tempEvents.empty() && tempEvents[0].getID() != INVALID_NUMBER) {
				string feedback = nameOfEvent + Display::EVENT_NOT_FOUND_MESSAGE;
				
				vector<tm> tmVec;
				if (normalEvents.empty()) { //no normal events to show
					tmVec = display.getTempMainDisplayLabel();
				} else { //at least 1 normal event to show (1st will always be marker)
					tmVec.push_back(normalEvents[1].getStartDate());
					if (normalEvents.size() > 2) { //if >1 normal event, show end date of last event
						tmVec.push_back(normalEvents[normalEvents.size() - 1].getEndDate());
					} else {
						tmVec.push_back(normalEvents[1].getEndDate());
					}
				}
				mktime(&tmVec[0]);
				mktime(&tmVec[1]);
				
				display.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, Display::GARBAGE_INT);
				return;
			}
		}

		//no event found
		if (!tempEvents.empty() && tempEvents[0].getID() == INVALID_NUMBER) {
			isDone = false;
			string feedback = nameOfEvent + Display::EVENT_NOT_FOUND_MESSAGE;
			display.setFeedbackStrings(feedback);
			return;
		}

		//successful deletion
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
		vector<Event> normalEvents, floatingEvents, tempEvents = commandPtr->getEventVector();
		vector<tm> tmVec;
		int id;

		if (!commandPtr->getIsComplete()) {
			setEventVector(normalEvents, floatingEvents, tempEvents);

			//more than 1 exact match
			if ( (!floatingEvents.empty() && floatingEvents[0].getName() == nameOfEvent) |
				(!normalEvents.empty() && normalEvents[1].getName() == nameOfEvent) ) {
				vector<tm> tmVec;
				tmVec.push_back(normalEvents[1].getStartDate());
				tmVec.push_back(normalEvents[normalEvents.size() - 1].getEndDate());
				mktime(&tmVec[0]);
				mktime(&tmVec[1]);
				
				display.setAllEvents(normalEvents, floatingEvents, Display::CHOOSE_EVENT_MESSAGE, tmVec, Display::GARBAGE_INT);
				return;
			}
			
			//at least 1 partial match
			if (!tempEvents.empty() && tempEvents[0].getID() != INVALID_NUMBER) {
				string feedback = nameOfEvent + Display::EVENT_NOT_FOUND_MESSAGE;
				
				vector<tm> tmVec;
				if (normalEvents.empty()) { //no normal events to show
					tmVec = display.getTempMainDisplayLabel();
				} else { //at least 1 normal event to show (1st will always be marker)
					tmVec.push_back(normalEvents[1].getStartDate());
					if (normalEvents.size() > 2) { //if >1 normal event, show end date of last event
						tmVec.push_back(normalEvents[normalEvents.size() - 1].getEndDate());
					} else {
						tmVec.push_back(normalEvents[1].getEndDate());
					}
				}
				mktime(&tmVec[0]);
				mktime(&tmVec[1]);
				
				display.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, Display::GARBAGE_INT);
				return;
			}
		}

		//no event found 
		if (!tempEvents.empty() && tempEvents[0].getID() == INVALID_NUMBER) {
			isDone = false;
			string feedback = nameOfEvent + Display::EVENT_NOT_FOUND_MESSAGE;
			display.setFeedbackStrings(feedback);
			return;
		}

		//normal 
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
		Event oldEvent = commandPtr->getEvent();
		string feedback = oldEvent.getName() + Display::EDITED_MESSAGE;

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

	case Parser::SHOWALL: {
		vector<Event> normalEvents, floatingEvents, tempEvents = commandPtr->getEventVector();
		setEventVector(normalEvents, floatingEvents, tempEvents);

		string feedback = Display::SHOW_MESSAGE + nameOfEvent;
		vector<tm> tmVec;
		if (normalEvents.empty()) { //no normal events to show
			tmVec = display.getTempMainDisplayLabel();
		} else { //at least 1 normal event to show (1st will always be marker)
			tmVec.push_back(normalEvents[1].getStartDate());
			if (normalEvents.size() > 2) { //if >1 normal event, show end date of last event
				tmVec.push_back(normalEvents[normalEvents.size() - 1].getEndDate());
			} else {
				tmVec.push_back(normalEvents[1].getEndDate());
			}
		}
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

	/*case Parser::UNDO: {
		break;
					   }
	*/

	case Parser::ERROR_: {
		delete commandPtr;
		commandPtr = NULL;
		isDone = false;

		string feedback = userEvent.getFeedback();

		display.setFeedbackStrings(feedback);
		break;
						 }

	default:
		break;
	}
}

void Logic::setEventVector(vector<Event>& normal, vector<Event>& floating, vector<Event> original) {
	int i = 0;
	
	while (original[i].getName() != Display::NEW_DAY_MESSAGE) {
		floating.push_back(original[i]);
		i++;
		if (i == original.size()) {
			return;
		}
	}
	
	for (; i < original.size() ; i++) {
		normal.push_back(original[i]);
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
		if (index > display.getTotalNumEvents()) {
			return INVALID_NUMBER;
		} else {
			return display.getIDFromIndex(index);
		}
	} else {
		return INVALID_NUMBER;
	}
}

void Logic::log(string logString) {
	ofstream outFile(LOG_FILE_NAME);
	
	logStrings.push_back(logString);
	for (int i = 0 ; i < logStrings.size() ; i++) {
		outFile << logStrings[i] << endl;
	}
	outFile.close();
}