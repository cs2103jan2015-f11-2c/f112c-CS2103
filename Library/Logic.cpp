#include "Logic.h"

//for logging
const string Logic::LOG_FILE_NAME = "LogicLog.txt";
const string Logic::CREATING_ADD = "creating add command";
const string Logic::CREATED_ADD = "created add command";
const string Logic::CREATING_DELETE = "creating delete command";
const string Logic::CREATED_DELETE = "created delete command";
const string Logic::CREATING_EDIT = "creating edit command";
const string Logic::CREATED_EDIT = "created edit command";
const string Logic::CREATING_SHOW = "creating show command";
const string Logic::CREATED_SHOW = "created show command";
const string Logic::CREATING_SHOWALL = "creating show all command";
const string Logic::CREATED_SHOWALL = "created show all command";
const string Logic::CREATING_SHOWFLOAT = "creating showfloat command";
const string Logic::CREATED_SHOWFLOAT = "created showfloat command";
const string Logic::CREATING_SEARCH = "creating search command";
const string Logic::CREATED_SEARCH = "created search command";
const string Logic::QUEUEING_UNDO = "queueing undo";
const string Logic::QUEUEING_REDO = "queueing redo";
const string Logic::CASE_0 = "entered case 0";
const string Logic::CASE_1 = "entered case 1";

const int Logic::INVALID_NUMBER = -1;
const string Logic::EMPTY_STRING = "";


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
EventFacade Logic::getEventStorage() {
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
//called by UI with original user input string, returns true if command executed thoroughly (e.g. if command is invalid, return false)
bool Logic::executeUserInput(string input) {
	parserPtr = new Parser(input);

	Parser::commandType commandType = parserPtr->getCommandType();
	Event userEvent = parserPtr->getEvent();
	string nameOfEvent = parserPtr->getNameOfEvent();
	bool isDone = true;

	Command* commandPtr = queueCommand(executor, commandType, userEvent, nameOfEvent);
	try {
		setUpdater(commandPtr, commandType, userEvent, nameOfEvent);
	} catch (bool isProperCommand) {
		if (!isProperCommand) {
			isDone = false;
		}
	}
	deleteParserPtr();

	return isDone;
}

//create command object, call executor to execute it
Command* Logic::queueCommand(Executor& executor, Parser::commandType command, Event userEvent, string nameOfEvent) {
	switch (command) {
	case Parser::ADD:
	case Parser::ADDFLOAT: {
		log(CREATING_ADD);
		Command* addCommand = new AddCommand(&eventStore, userEvent);
		log(CREATED_ADD);
		return executor.execute(addCommand);
						   }

						   /*case Parser::COMPLETE: {
						   break;
						   }*/

	case Parser::DELETE_: {
		log(CREATING_DELETE);
		string name = convertUserInputToName(nameOfEvent);

		Event eventToDelete;
		eventToDelete.setName(name);

		Command* deleteCommand = new DeleteCommand(&eventStore, eventToDelete);
		log(CREATED_DELETE);
		return executor.execute(deleteCommand);
						  }

	case Parser::EDIT: {
		log(CREATING_EDIT);
		string name = convertUserInputToName(nameOfEvent);

		Event eventToEdit;
		eventToEdit.setName(name);

		Command* editCommand = new EditCommand(&eventStore, eventToEdit, userEvent);
		log(CREATED_EDIT);
		return executor.execute(editCommand);
					   }

	case Parser::SEARCH: {
		log(CREATING_SEARCH);

		Command* searchCommand = new SearchCommand(&eventStore, nameOfEvent);
		log(CREATED_SEARCH);
		return executor.execute(searchCommand);
						 }

	case Parser::SHOW: {
		log(CREATING_SHOW);
		Command* showCommand = new ShowCommand(&eventStore, userEvent);
		log(CREATED_SHOW);
		return executor.execute(showCommand);
					   }

	case Parser::SHOWALL: {
		log(CREATING_SHOWALL);
		Command* showAllCommand = new ShowAllCommand(&eventStore);
		log(CREATED_SHOWALL);
		return executor.execute(showAllCommand);
						  }

						  /*case Parser::SHOWDUE: {
						  break;
						  }*/

	case Parser::SHOWFLOAT: {
		log(CREATING_SHOWFLOAT);
		Command* showFloatCommand = new ShowFloatCommand(&eventStore);
		log(CREATED_SHOWFLOAT);
		return executor.execute(showFloatCommand);
							}

							/*case Parser::SHOWIMPORTANT: {
							break;
							}*/

	case Parser::UNDO: {
		log(QUEUEING_UNDO);
		return executor.undo();
					   }

	case Parser::REDO: {
		log(QUEUEING_REDO);
		return executor.redo();
					   }

	case Parser::ERROR_: {
		return new NullCommand;
						 }

	default: {
		return new NullCommand;
			 }
	}

}

//update new information for UI to display
void Logic::setUpdater(Command* commandPtr, Parser::commandType command, Event userEvent, string nameOfEvent) {
	try {
		bool isDone = true;

		switch (command) {
		case Parser::ADD: 
		case Parser::ADDFLOAT: {		
			vector<Event> normalEvents, floatingEvents;

			setOneEventVector(normalEvents, floatingEvents, commandPtr, updater);
			vector<tm> tmVec = getTmVecFromEvents(normalEvents, updater);
			string feedback = userEvent.getName() + LogicUpdater::ADDED_MESSAGE;
			int id = userEvent.getID();

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id);
			break;
							   }

							   /*case Parser::COMPLETE: {
							   break;
							   }*/

		case Parser::DELETE_: {
			vector<Event> normalEvents, floatingEvents, tempEvents = commandPtr->getEventVector() ;

			if (!commandPtr->getIsExecuted()) {
				setEventVectors(normalEvents, floatingEvents, tempEvents);

				//more than 1 exact match
				if ( (!floatingEvents.empty() && floatingEvents[0].getName() == nameOfEvent) |
					(!normalEvents.empty() && normalEvents[1].getName() == nameOfEvent) ) {
						vector<tm> tmVec = getTmVecFromEvents(normalEvents, updater);
						updater.setAllEvents(normalEvents, floatingEvents, LogicUpdater::CHOOSE_EVENT_MESSAGE, tmVec, LogicUpdater::GARBAGE_INT);
						return;
				}

				//at least 1 partial match
				if (!tempEvents.empty() && tempEvents[0].getID() != INVALID_NUMBER) {
					string feedback = nameOfEvent + LogicUpdater::PARTIAL_EVENT_FOUND_MESSAGE;
					vector<tm> tmVec = getTmVecFromEvents(normalEvents, updater);

					updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT);
					return;
				}
			}

			//no event found
			if (!tempEvents.empty() && tempEvents[0].getID() == INVALID_NUMBER) {
				string feedback = nameOfEvent + LogicUpdater::EVENT_NOT_FOUND_MESSAGE;
				updater.setFeedbackStrings(feedback);
				throw !isDone;
			}

			//successful delete
			setOneEventVector(normalEvents, floatingEvents, commandPtr, updater);
			Event deletedEvent = commandPtr->getEvent();
			string feedback = deletedEvent.getName() + LogicUpdater::DELETED_MESSAGE;
			vector<tm> tmVec = updater.getTempMainDisplayLabel();

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT);
			break;
							  }

		case Parser::EDIT: {
			vector<Event> normalEvents, floatingEvents, tempEvents = commandPtr->getEventVector();

			if (!commandPtr->getIsExecuted()) {
				setEventVectors(normalEvents, floatingEvents, tempEvents);

				//more than 1 exact match
				if ( (!floatingEvents.empty() && floatingEvents[0].getName() == nameOfEvent) |
					(!normalEvents.empty() && normalEvents[1].getName() == nameOfEvent) ) {
						vector<tm> tmVec = getTmVecFromEvents(normalEvents, updater);
						updater.setAllEvents(normalEvents, floatingEvents, LogicUpdater::CHOOSE_EVENT_MESSAGE, tmVec, LogicUpdater::GARBAGE_INT);
						return;
				}

				//at least 1 partial match
				if (!tempEvents.empty() && tempEvents[0].getID() != INVALID_NUMBER) {
					string feedback = nameOfEvent + LogicUpdater::EVENT_NOT_FOUND_MESSAGE;
					vector<tm> tmVec = getTmVecFromEvents(normalEvents, updater);

					updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT);
					return;
				}
			}

			//no event found 
			if (!tempEvents.empty() && tempEvents[0].getID() == INVALID_NUMBER) {
				string feedback = nameOfEvent + LogicUpdater::EVENT_NOT_FOUND_MESSAGE;
				updater.setFeedbackStrings(feedback);
				throw false;
			}

			//successful edit 
			setOneEventVector(normalEvents, floatingEvents, commandPtr, updater);
			Event oldEvent = commandPtr->getEvent();
			int id = oldEvent.getID();
			vector<tm> tmVec = getTmVecFromEvents(normalEvents, updater);
			string feedback = oldEvent.getName() + LogicUpdater::EDITED_MESSAGE;

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id);
			break;
						   }

		case Parser::SEARCH: {
			vector<Event> normalEvents, floatingEvents;

			setEventVectors(normalEvents, floatingEvents, commandPtr->getEventVector());
			vector<tm> tmVec = getTmVecFromEvents(normalEvents, updater);

			updater.setAllEvents(normalEvents, floatingEvents, EMPTY_STRING, tmVec, LogicUpdater::GARBAGE_INT);
			break;
							 }

		case Parser::SHOW: {
			vector<Event> normalEvents = commandPtr->getEventVector();
			vector<Event> floatingEvents = updater.getFloatingEvents();
			string feedback = LogicUpdater::SHOW_MESSAGE + nameOfEvent;
			vector<tm> tmVec;
			tmVec.push_back(userEvent.getStartDate());
			tmVec.push_back(userEvent.getEndDate());

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT);
			break;
						   }

		case Parser::SHOWALL: {
			vector<Event> normalEvents, floatingEvents;

			setEventVectors(normalEvents, floatingEvents, commandPtr->getEventVector());
			string feedback = LogicUpdater::SHOW_MESSAGE + nameOfEvent;
			vector<tm> tmVec = getTmVecFromEvents(normalEvents, updater);

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT);
			break;
							  }

							  /*case Parser::SHOWDUE: {
							  break;
							  }*/

		case Parser::SHOWFLOAT: {
			vector<Event> normalEvents = updater.getNormalEvents();
			vector<Event> floatingEvents = commandPtr->getEventVector();
			vector<tm> tmVec = updater.getTempMainDisplayLabel();

			updater.setAllEvents(normalEvents, floatingEvents, EMPTY_STRING, tmVec, LogicUpdater::GARBAGE_INT);
			break;
								}

								/*case Parser::SHOWIMPORTANT: {
								break;
								}*/

		case Parser::UNDO:
		case Parser::REDO: {
			if (commandPtr->getEvent().getID() == INVALID_NUMBER) {
				throw false;
			}

			vector<Event> normalEvents, floatingEvents;
			setOneEventVector(normalEvents, floatingEvents, commandPtr, updater);

			string feedback;
			if (command == Parser::UNDO) {
				feedback = LogicUpdater::UNDO_MESSAGE;
			} else {
				feedback = LogicUpdater::REDO_MESSAGE;
			}

			vector<tm> tmVec = getTmVecFromEvents(normalEvents, updater);

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT);
			break;
						   }


		case Parser::ERROR_: {
			updater.setFeedbackStrings(userEvent.getFeedback());
			throw false;
			break;
							 }
		}
	} catch (bool isProperCommand) {
		if (!isProperCommand) {
			delete commandPtr;
			commandPtr = NULL;
			throw isProperCommand;
		}
	}
}

void Logic::setEventVectors(vector<Event>& normal, vector<Event>& floating, vector<Event> original) {
	if (original.empty()) {
		return;
	}

	unsigned int i = 0;
	//push all floating events from original into floating vector
	while (original[i].getName() != LogicUpdater::NEW_DAY_MESSAGE) {
		floating.push_back(original[i]);
		i++;
		if (i == original.size()) {
			return;
		}
	}
	//remaining events are normal, push them into normal vector
	for (; i < original.size() ; i++) {
		normal.push_back(original[i]);
	}
}

void Logic::setOneEventVector(vector<Event>& normal, vector<Event>& floating, Command* commandPtr, LogicUpdater updater) {
	if (commandPtr->getIsFloating()) {
		normal = updater.getNormalEvents();
		floating = commandPtr->getEventVector();
	} else {
		normal = commandPtr->getEventVector();
		floating = updater.getFloatingEvents();
	}
}

vector<tm> Logic::getTmVecFromEvents(vector<Event> normalEvents, LogicUpdater updater) {
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

	return tmVec;
}

void Logic::deleteParserPtr() {
	delete parserPtr;
	parserPtr = NULL;
}


//OTHERS

//returns true if input string consists of only numeric digits
bool Logic::isNumber(string s) {
	for (unsigned int i = 0 ; i < s.size() ; i++) {
		if (!isdigit(s[i])) {
			return false;
		}
	}
	return true;
}

//returns id of event if found in updater, -1 otherwise
string Logic::convertUserInputToName(string input) {
	if (isNumber(input)) {
		int index = std::stoi(input);

		if (index == Command::SIZE_ZERO | index > updater.getTotalNumEvents()) {
			return EMPTY_STRING;
		} else {
			return updater.getNameFromIndex(index);
		}
	} else {
		return input;
	}
}


//LOG
void Logic::log(string logString) {
	ofstream outFile(LOG_FILE_NAME);

	logStrings.push_back(logString);
	for (unsigned int i = 0 ; i < logStrings.size() ; i++) {
		outFile << logStrings[i] << endl;
	}
	outFile.close();
}

void Logic::log(int logInt) {
	ostringstream outString;
	outString << logInt;

	ofstream outFile(LOG_FILE_NAME);

	logStrings.push_back(outString.str());
	for (unsigned int i = 0 ; i < logStrings.size() ; i++) {
		outFile << logStrings[i] << endl;
	}
	outFile.close();
}

void Logic::log(string logString, int logInt) {
	ostringstream outString;
	outString << " " << logInt;

	ofstream outFile(LOG_FILE_NAME);

	logStrings.push_back(logString + outString.str());
	for (unsigned int i = 0 ; i < logStrings.size() ; i++) {
		outFile << logStrings[i] << endl;
	}
	outFile.close();
}
