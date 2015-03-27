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
const string Logic::CREATING_UNDO = "creating undo";
const string Logic::CREATING_REDO = "creating redo";
const string Logic::CASE_0 = "entered case 0";
const string Logic::CASE_1 = "entered case 1";

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

vector<LogicUpdater::EVENT_STRING> Logic::getFloatingStrings() {
	return updater.getFloatingDisplayStrings();
}

vector<LogicUpdater::EVENT_STRING> Logic::getMainStrings() {
	return updater.getMainDisplayStrings();
}

vector<string> Logic::getFeedbackStrings() {
	return updater.getFeedbackDisplayStrings();
}

vector<string> Logic::getErrorString() {
	return updater.getErrorStrings();
}

string Logic::getMainDisplayLabel() {
	return updater.getMainDisplayLabel();
}

vector<tm> Logic::getTempMainDisplayLabel() {
	return updater.getTempMainDisplayLabel();
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
			eventToDelete = updater.getEventFromID(id);
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
			eventToEdit = updater.getEventFromID(id);
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

	case Parser::UNDO: {
		log(CREATING_UNDO);
		return executor.undo();
		break;
					   }

	case Parser::REDO: {
		log(CREATING_REDO);
		return executor.redo();
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
		vector<Event> floatingEvents = updater.getFloatingEvents();
		string feedback = userEvent.getName() + LogicUpdater::ADDED_MESSAGE;
		vector<tm> tmVec;
		tmVec.push_back(userEvent.getStartDate());
		tmVec.push_back(userEvent.getEndDate());
		int id = userEvent.getID();

		updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id);
		break;
					  }

	case Parser::ADDFLOAT: {		
		vector<Event> normalEvents = updater.getNormalEvents();
		vector<Event> floatingEvents = commandPtr->getEventVector();
		string feedback = userEvent.getName() + LogicUpdater::ADDED_MESSAGE;
		vector<tm> tmVec = updater.getTempMainDisplayLabel();
		int id = userEvent.getID();

		updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id);
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

					updater.setAllEvents(normalEvents, floatingEvents, LogicUpdater::CHOOSE_EVENT_MESSAGE, tmVec, LogicUpdater::GARBAGE_INT);
					return;
			}

			//at least 1 partial match
			if (!tempEvents.empty() && tempEvents[0].getID() != INVALID_NUMBER) {
				string feedback = nameOfEvent + LogicUpdater::EVENT_NOT_FOUND_MESSAGE;

				vector<tm> tmVec;
				if (normalEvents.empty()) { //no normal events to show
					tmVec = updater.getTempMainDisplayLabel();
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

				updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT);
				return;
			}
		}

		//no event found
		if (!tempEvents.empty() && tempEvents[0].getID() == INVALID_NUMBER) {
			isDone = false;
			string feedback = nameOfEvent + LogicUpdater::EVENT_NOT_FOUND_MESSAGE;
			updater.setFeedbackStrings(feedback);
			return;
		}

		//successful deletion
		if (commandPtr->getIsFloating()) {
			normalEvents = updater.getNormalEvents();
			floatingEvents = commandPtr->getEventVector();
		} else {
			normalEvents = commandPtr->getEventVector();
			floatingEvents = updater.getFloatingEvents();
		}
		Event deletedEvent = commandPtr->getEvent();
		string feedback = deletedEvent.getName() + LogicUpdater::DELETED_MESSAGE;
		vector<tm> tmVec = updater.getTempMainDisplayLabel();

		updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT);
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

					updater.setAllEvents(normalEvents, floatingEvents, LogicUpdater::CHOOSE_EVENT_MESSAGE, tmVec, LogicUpdater::GARBAGE_INT);
					return;
			}

			//at least 1 partial match
			if (!tempEvents.empty() && tempEvents[0].getID() != INVALID_NUMBER) {
				string feedback = nameOfEvent + LogicUpdater::EVENT_NOT_FOUND_MESSAGE;

				vector<tm> tmVec;
				if (normalEvents.empty()) { //no normal events to show
					tmVec = updater.getTempMainDisplayLabel();
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

				updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT);
				return;
			}
		}

		//no event found 
		if (!tempEvents.empty() && tempEvents[0].getID() == INVALID_NUMBER) {
			isDone = false;
			string feedback = nameOfEvent + LogicUpdater::EVENT_NOT_FOUND_MESSAGE;
			updater.setFeedbackStrings(feedback);
			return;
		}

		//normal 
		if (commandPtr->getIsFloating()) {
			normalEvents = updater.getNormalEvents();
			floatingEvents = commandPtr->getEventVector();
			tmVec = updater.getTempMainDisplayLabel();
			id = floatingEvents[0].getID();
		} else {
			normalEvents = commandPtr->getEventVector();
			floatingEvents = updater.getFloatingEvents();
			tmVec.push_back(normalEvents[0].getStartDate());
			tmVec.push_back(normalEvents[0].getEndDate());
			id = normalEvents[0].getID();
		}
		Event oldEvent = commandPtr->getEvent();
		string feedback = oldEvent.getName() + LogicUpdater::EDITED_MESSAGE;

		updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id);
		break;
					   }

	case Parser::SHOW: {
		vector<Event> normalEvents = commandPtr->getEventVector();
		vector<Event> floatingEvents = updater.getFloatingEvents();
		string feedback = LogicUpdater::SHOW_MESSAGE + nameOfEvent;
		vector<tm> tmVec;
		tmVec.push_back(userEvent.getStartDate());
		tmVec.push_back(userEvent.getEndDate());
		mktime(&tmVec[0]);
		mktime(&tmVec[1]);

		updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT);
		break;
					   }

	case Parser::SHOWALL: {
		vector<Event> normalEvents, floatingEvents, tempEvents = commandPtr->getEventVector();
		setEventVector(normalEvents, floatingEvents, tempEvents);

		string feedback = LogicUpdater::SHOW_MESSAGE + nameOfEvent;
		vector<tm> tmVec;
		if (normalEvents.empty()) { //no normal events to show
			tmVec = updater.getTempMainDisplayLabel();
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

		updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT);
		break;
						  }

	case Parser::SHOWFLOAT: {
		vector<Event> normalEvents = updater.getNormalEvents();
		vector<Event> floatingEvents = commandPtr->getEventVector();
		string emptyFeedback;
		vector<tm> tmVec = updater.getTempMainDisplayLabel();

		updater.setAllEvents(normalEvents, floatingEvents, emptyFeedback, tmVec, LogicUpdater::GARBAGE_INT);
		break;
							}

	case Parser::UNDO:
	case Parser::REDO: {
		vector<Event> normalEvents, floatingEvents, tempEvents = commandPtr->getEventVector();
		setEventVector(normalEvents, floatingEvents, tempEvents);

		string feedback = "";
		vector<tm> tmVec;
		if (normalEvents.empty()) { //no normal events to show
			tmVec = updater.getTempMainDisplayLabel();
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

		updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT);
		break;
					   }


	case Parser::ERROR_: {
		delete commandPtr;
		commandPtr = NULL;
		isDone = false;

		string feedback = userEvent.getFeedback();
		updater.setFeedbackStrings(feedback);
		break;
						 }

	default:
		break;
	}
}

void Logic::setEventVector(vector<Event>& normal, vector<Event>& floating, vector<Event> original) {
	if (original.empty()) {
		return;
	}

	int i = 0;

	while (original[i].getName() != LogicUpdater::NEW_DAY_MESSAGE) {
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
		if (index > updater.getTotalNumEvents()) {
			return INVALID_NUMBER;
		} else {
			return updater.getIDFromIndex(index);
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