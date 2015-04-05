#include "Logic.h"


const int Logic::INVALID_NUMBER = -1;
const string Logic::EMPTY_STRING = "";
const string Logic::COLON_SPACE = ": ";


//CONSTRUCTOR, DESTRUCTOR
Logic::Logic(void) {
	parserPtr = NULL;
}

Logic::~Logic() {
	deleteParserPtr();
}


//GETTERS
EventFacade Logic::getEventFacade() {
	return eventFacade;
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
	assert(isProperCommand(command));

	try {
		switch (command) {
		case Parser::ADD:
		case Parser::ADDFLOAT: {
			Command* addCommand = new AddCommand(&eventFacade, userEvent);
			logger.log(LogicLog::CREATED_ADD);
			return executor.execute(addCommand);
							   }

		case Parser::COMPLETE: {
			int id = convertNameToID(nameOfEvent);

			Event eventToComplete;
			eventToComplete.setName(nameOfEvent);
			if (id != INVALID_NUMBER) {
				eventToComplete = updater.getEventFromID(id);
			}

			Command* completeCommand = new CompleteCommand(&eventFacade, id, eventToComplete);
			logger.log(LogicLog::CREATED_COMPLETE);
			return executor.execute(completeCommand);
			break;
							   }

		case Parser::DELETE_: {
			int id = convertNameToID(nameOfEvent);

			Event eventToDelete;
			eventToDelete.setName(nameOfEvent);
			if (id != INVALID_NUMBER) {
				eventToDelete = updater.getEventFromID(id);
			}

			Command* deleteCommand = new DeleteCommand(&eventFacade, id, eventToDelete);
			logger.log(LogicLog::CREATED_DELETE);
			return executor.execute(deleteCommand);
							  }

		case Parser::EDIT: {
			int id = convertNameToID(nameOfEvent);

			Event eventToEdit;
			eventToEdit.setName(nameOfEvent);
			if (id != INVALID_NUMBER) {
				eventToEdit = updater.getEventFromID(id);
			}

			Command* editCommand = new EditCommand(&eventFacade, id, eventToEdit, userEvent);
			logger.log(LogicLog::CREATED_EDIT);
			return executor.execute(editCommand);
						   }

		case Parser::SEARCH: {
			Command* searchCommand = new SearchCommand(&eventFacade, nameOfEvent);
			logger.log(LogicLog::CREATED_SEARCH);
			return executor.execute(searchCommand);
							 }

		case Parser::SHOW: 
		case Parser::SHOWWEEK:
		case Parser::SHOWMONTH: {
			Command* showCommand = new ShowCommand(&eventFacade, userEvent);
			logger.log(LogicLog::CREATED_SHOW);
			return executor.execute(showCommand);
								}

		case Parser::SHOWALL: {
			Command* showAllCommand = new ShowAllCommand(&eventFacade);
			logger.log(LogicLog::CREATED_SHOWALL);
			return executor.execute(showAllCommand);
							  }

		case Parser::SHOWALLIMPORTANT: {
			Command* showAllImportantCommand = new ShowAllImportantCommand(&eventFacade);
			logger.log(LogicLog::CREATED_SHOWALLIMPORTANT);
			return executor.execute(showAllImportantCommand);
									   }

		case Parser::SHOWCOMPLETE: {
			Command* showCompletedCommand = new ShowCompletedCommand(&eventFacade);
			logger.log(LogicLog::CREATED_SHOWCOMPLETED);
			return executor.execute(showCompletedCommand);
								   }

								   /*case Parser::SHOWDUE: {
								   break;
								   }*/

		case Parser::SHOWFLOAT: {
			Command* showFloatCommand = new ShowFloatCommand(&eventFacade);
			logger.log(LogicLog::CREATED_SHOWFLOAT);
			return executor.execute(showFloatCommand);
								}

		case Parser::SHOWIMPORTANT: {
			Command* showImportanceCommand = new ShowImportanceCommand(&eventFacade, userEvent.getImportanceLevel());
			logger.log(LogicLog::CREATED_SHOWIMPORTANCE);
			return executor.execute(showImportanceCommand);
			break;
									}

		case Parser::UNDO: {
			logger.log(LogicLog::QUEUEING_UNDO);
			return executor.undo();
						   }

		case Parser::REDO: {
			logger.log(LogicLog::QUEUEING_REDO);
			return executor.redo();
						   }

		default: {
			throw false;
				 }
		}
	} catch (bool) {
		return new NullCommand;
	}
}

//update new information for UI to display
void Logic::setUpdater(Command* commandPtr, Parser::commandType command, Event userEvent, string nameOfEvent) {
	assert(isProperCommand(command));

	try {
		bool isDone = true;

		switch (command) {
		case Parser::ADD: 
		case Parser::ADDFLOAT: {		
			vector<Event> normalEvents, floatingEvents;

			setOneEventVector(normalEvents, floatingEvents, commandPtr, updater);
			vector<tm> tmVec = getTmVecFromEvents(normalEvents, updater);
			string feedback = userEvent.getName() + LogicUpdater::ADDED_MESSAGE;
			if (command == Parser::ADD) {
				if (isSameDate(userEvent.getStartDate(),userEvent.getEndDate())) {
					feedback += COLON_SPACE + updater.setSingleDayString(userEvent.getStartDate());
				} else {
					feedback += COLON_SPACE + updater.setMultipleDaysString(userEvent.getStartDate(),userEvent.getEndDate());
				}
			}
			int id = userEvent.getID();

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id, LogicUpdater::EMPTY_STRING);
			break;
							   }

		case Parser::COMPLETE:
		case Parser::DELETE_: {
			vector<Event> normalEvents, floatingEvents, tempEvents = commandPtr->getEventVector();

			if (!commandPtr->getIsExecuted()) {
				setEventVectors(normalEvents, floatingEvents, tempEvents);

				//more than 1 exact match
				if ( (!floatingEvents.empty() && floatingEvents[0].getName() == nameOfEvent) |
					(!normalEvents.empty() && normalEvents[1].getName() == nameOfEvent) ) {
						vector<tm> tmVec = getTmVecFromEvents(normalEvents, updater);

						updater.setAllEvents(normalEvents, floatingEvents, LogicUpdater::CHOOSE_EVENT_MESSAGE, tmVec, LogicUpdater::GARBAGE_INT, LogicUpdater::EMPTY_STRING);
						return;
				}

				//at least 1 partial match
				if (!tempEvents.empty() && tempEvents[0].getID() != INVALID_NUMBER) {
					string feedback = nameOfEvent + LogicUpdater::PARTIAL_EVENT_FOUND_MESSAGE;
					vector<tm> tmVec = getTmVecFromEvents(normalEvents, updater);

					updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, LogicUpdater::EMPTY_STRING);
					return;
				}
			}

			//no event found
			if (!tempEvents.empty() && tempEvents[0].getID() == INVALID_NUMBER) {
				string feedback = nameOfEvent + LogicUpdater::EVENT_NOT_FOUND_MESSAGE;
				updater.setFeedbackStrings(feedback);
				throw !isDone;
			}

			//successful complete/delete
			setOneEventVector(normalEvents, floatingEvents, commandPtr, updater);
			vector<tm> tmVec = getTmVecFromEvents(normalEvents, updater);
			if (command == Parser::DELETE_) { //for delete
				Event deletedEvent = commandPtr->getEvent();
				string feedback = deletedEvent.getName() + LogicUpdater::DELETED_MESSAGE;

				updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, LogicUpdater::EMPTY_STRING);
				return;
			} else { //for complete
				Event completedEvent = commandPtr->getEvent();
				string feedback = completedEvent.getName() + LogicUpdater::COMPLETED_MESSAGE;

				updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, LogicUpdater::EMPTY_STRING);
				return;
			}
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
						updater.setAllEvents(normalEvents, floatingEvents, LogicUpdater::CHOOSE_EVENT_MESSAGE, tmVec, LogicUpdater::GARBAGE_INT, LogicUpdater::EMPTY_STRING);
						return;
				}

				//at least 1 partial match
				if (!tempEvents.empty() && tempEvents[0].getID() != INVALID_NUMBER) {
					string feedback = nameOfEvent + LogicUpdater::EVENT_NOT_FOUND_MESSAGE;
					vector<tm> tmVec = getTmVecFromEvents(normalEvents, updater);

					updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, LogicUpdater::EMPTY_STRING);
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

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id, LogicUpdater::EMPTY_STRING);
			break;
						   }

		case Parser::SEARCH: {
			vector<Event> normalEvents, floatingEvents;

			setEventVectors(normalEvents, floatingEvents, commandPtr->getEventVector());
			vector<tm> tmVec = getTmVecFromEvents(normalEvents, updater);

			updater.setAllEvents(normalEvents, floatingEvents, EMPTY_STRING, tmVec, LogicUpdater::GARBAGE_INT, LogicUpdater::EMPTY_STRING);
			break;
							 }

		case Parser::SHOW: 
		case Parser:: SHOWWEEK:
		case Parser:: SHOWMONTH: {
			vector<Event> normalEvents = commandPtr->getEventVector();
			vector<Event> floatingEvents = updater.getFloatingEvents();
			string feedback = LogicUpdater::SHOW_MESSAGE + nameOfEvent;
			vector<tm> tmVec;
			tmVec.push_back(userEvent.getStartDate());
			tmVec.push_back(userEvent.getEndDate());
			string showType = LogicUpdater::EMPTY_STRING;
			if (command == Parser::SHOWWEEK) {
				showType = LogicUpdater::WORD_WEEK;
			}
			if (command == Parser::SHOWMONTH) {
				showType = LogicUpdater::WORD_MONTH;
			}

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, showType);
			break;
								 }

		case Parser::SHOWALL:
		case Parser::SHOWALLIMPORTANT:
		case Parser::SHOWCOMPLETE:
		case Parser::SHOWIMPORTANT: {
			vector<Event> normalEvents, floatingEvents;

			setEventVectors(normalEvents, floatingEvents, commandPtr->getEventVector());
			string feedback = LogicUpdater::SHOW_MESSAGE + nameOfEvent;
			vector<tm> tmVec = getTmVecFromEvents(normalEvents, updater);
			
			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, LogicUpdater::EMPTY_STRING);
			break;
									}

									/*case Parser::SHOWDUE: {
									break;
									}*/

		case Parser::SHOWFLOAT: {
			vector<Event> normalEvents = updater.getNormalEvents();
			vector<Event> floatingEvents = commandPtr->getEventVector();
			vector<tm> tmVec = updater.getTempMainDisplayLabel();

			updater.setAllEvents(normalEvents, floatingEvents, EMPTY_STRING, tmVec, LogicUpdater::GARBAGE_INT, LogicUpdater::EMPTY_STRING);
			break;
								}

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

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, LogicUpdater::EMPTY_STRING);
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
	while (original[i].getIsFloating()) {
		floating.push_back(original[i]);
		i++;
		if (i == original.size()) {
			return;
		}
	}
	//remaining events are normal, push them into normal vector
	for (; i < original.size(); i++) {
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
		if (normalEvents.size() > Command::SIZE_TWO) { //if >1 normal event, show end date of last event
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

bool Logic::isProperCommand(Parser::commandType commandType) {
	return ( (commandType == Parser::ADD) |
		(commandType == Parser::ADDFLOAT) |
		(commandType == Parser::COMPLETE) |
		(commandType == Parser::DELETE_) |
		(commandType == Parser::EDIT) |
		(commandType == Parser::SEARCH) |
		(commandType == Parser::SHOW) |
		(commandType == Parser::SHOWWEEK) |
		(commandType == Parser::SHOWMONTH) |
		(commandType == Parser::SHOWALL) |
		(commandType == Parser::SHOWALLIMPORTANT) |
		(commandType == Parser::SHOWCOMPLETE) |
		(commandType == Parser::SHOWDUE) |
		(commandType == Parser::SHOWFLOAT) |
		(commandType == Parser::SHOWIMPORTANT) |
		(commandType == Parser::UNDO) |
		(commandType == Parser::REDO) |
		(commandType == Parser::ERROR_) );
}

//returns true if input string consists of only numeric digits
bool Logic::isNumber(string s) {
	//log if input string is empty
	try {
		if (s.size() == Command::SIZE_ZERO) {
			throw false;
		} else {
			throw true;
		}
	} catch (bool isEmpty) {
		if (isEmpty == false) {
			logger.log(LogicLog::ISNUMBER_INPUT_EMPTY);
			return false;
		}
	}


	for (unsigned int i = 0; i < s.size(); i++) {
		if (!isdigit(s[i])) {
			return false;
		}
	}
	return true;
}

bool Logic::isSameDate(tm date1, tm date2) {
	return(date1.tm_mday == date2.tm_mday &&
		date1.tm_mon == date2.tm_mon &&
		date1.tm_year == date2.tm_year);
}

//returns id of event if found in updater, -1 otherwise
int Logic::convertNameToID(string name) {
	if (isNumber(name)) {
		int index = std::stoi(name);

		if (index == Command::SIZE_ZERO) {
			return INVALID_NUMBER;
		}

		if (index > updater.getTotalNumEvents()) {
			return INVALID_NUMBER;
		} else {
			return updater.getIDFromIndex(index);
		}
	} else {
		return INVALID_NUMBER;
	}
}