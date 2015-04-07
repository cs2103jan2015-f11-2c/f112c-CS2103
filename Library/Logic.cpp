#include "Logic.h"


const int Logic::INVALID_NUMBER = -1;
const string Logic::EMPTY_STRING = "";
const string Logic::COMMA_SPACE = ", ";
const char Logic::CHAR_OPEN_SQUARE_BRACKET = '[';
const char Logic::CHAR_CLOSE_SQUARE_BRACKET = ']';


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

	Command* commandPtr = queueCommand(commandType, userEvent, nameOfEvent);
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
Command* Logic::queueCommand(Parser::commandType command, Event userEvent, string nameOfEvent) {
	assert(isProperCommand(command));

	try {
		switch (command) {
		case Parser::ADD:
		case Parser::ADDFLOAT: {
			Command* addCommand = new AddCommand(&eventFacade, userEvent, updater.getTempMainDisplayLabel());
			logger.log(LogicLog::CREATED + LogicLog::ADD);
			return executor.execute(addCommand);
							   }

		case Parser::COMPLETE: {
			int id = convertNameToID(nameOfEvent);

			Event eventToComplete;
			eventToComplete.setName(nameOfEvent);
			if (id != INVALID_NUMBER) {
				eventToComplete = updater.getEventFromID(id);
			}

			Command* completeCommand = new CompleteCommand(&eventFacade, id, eventToComplete, updater.getTempMainDisplayLabel());
			logger.log(LogicLog::CREATED + LogicLog::COMPLETE);
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

			Command* deleteCommand = new DeleteCommand(&eventFacade, id, eventToDelete, updater.getTempMainDisplayLabel());
			logger.log(LogicLog::CREATED + LogicLog::DELETE);
			return executor.execute(deleteCommand);
							  }

		case Parser::EDIT: {
			int id = convertNameToID(nameOfEvent);

			Event eventToEdit;
			eventToEdit.setName(nameOfEvent);
			if (id != INVALID_NUMBER) {
				eventToEdit = updater.getEventFromID(id);
			}

			Command* editCommand = new EditCommand(&eventFacade, id, eventToEdit, userEvent, updater.getTempMainDisplayLabel());
			logger.log(LogicLog::CREATED + LogicLog::EDIT);
			return executor.execute(editCommand);
						   }

		case Parser::SEARCH: {
			Command* searchCommand = new SearchCommand(&eventFacade, nameOfEvent);
			logger.log(LogicLog::CREATED + LogicLog::SEARCH);
			return executor.execute(searchCommand);
							 }

		case Parser::SHOW: 
		case Parser::SHOWWEEK:
		case Parser::SHOWMONTH: {
			Command* showCommand = new ShowCommand(&eventFacade, userEvent);
			logger.log(LogicLog::CREATED + LogicLog::SHOW);
			return executor.execute(showCommand);
								}

		case Parser::SHOWALL: {
			Command* showAllCommand = new ShowAllCommand(&eventFacade);
			logger.log(LogicLog::CREATED + LogicLog::SHOWALL);
			return executor.execute(showAllCommand);
							  }

		case Parser::SHOWALLIMPORTANT: {
			Command* showAllImportantCommand = new ShowAllImportantCommand(&eventFacade);
			logger.log(LogicLog::CREATED + LogicLog::SHOWALLIMPORTANT);
			return executor.execute(showAllImportantCommand);
									   }

		case Parser::SHOWCOMPLETE: {
			Command* showCompletedCommand = new ShowCompletedCommand(&eventFacade);
			logger.log(LogicLog::CREATED + LogicLog::SHOWCOMPLETED);
			return executor.execute(showCompletedCommand);
								   }

								   /*case Parser::SHOWDUE: {
								   break;
								   }*/

		case Parser::SHOWFLOAT: {
			Command* showFloatCommand = new ShowFloatCommand(&eventFacade);
			logger.log(LogicLog::CREATED + LogicLog::SHOWFLOAT);
			return executor.execute(showFloatCommand);
								}

		case Parser::SHOWIMPORTANT: {
			Command* showImportanceCommand = new ShowImportanceCommand(&eventFacade, userEvent.getImportanceLevel());
			logger.log(LogicLog::CREATED + LogicLog::SHOWIMPORTANCE);
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
		vector<Event> normalEvents, floatingEvents;

		switch (command) {
		case Parser::ADD: {
			vector<tm> tmVec;
			setOneEventVector(normalEvents, floatingEvents, commandPtr, tmVec);	

			string feedback = LogicUpdater::ADDED_MESSAGE + userEvent.getName() + COMMA_SPACE;
			if (isSameDate(userEvent.getStartDate(),userEvent.getEndDate())) {
				feedback += updater.setSingleDayString(userEvent.getStartDate());
			} else {
				feedback += updater.setMultipleDaysString(userEvent.getStartDate(),userEvent.getEndDate());
			}

			int id = userEvent.getID();

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id, lastShowType);
			break;
						  }

		case Parser::ADDFLOAT: {		
			vector<tm> tmVec;
			setOneEventVector(normalEvents, floatingEvents, commandPtr, tmVec);
			string feedback = LogicUpdater::ADDED_MESSAGE + userEvent.getName();
			int id = userEvent.getID();

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id, lastShowType);
			break;
							   }

		case Parser::COMPLETE:
		case Parser::DELETE_: {
			vector<Event> tempEvents = commandPtr->getEventVector();

			if (!commandPtr->getIsExecuted()) { //2 cases
				setEventVectors(normalEvents, floatingEvents, tempEvents);

				//case 1: more than 1 exact match
				if ( (!floatingEvents.empty() && floatingEvents[0].getName() == nameOfEvent) |
					(!normalEvents.empty() && normalEvents[1].getName() == nameOfEvent) ) {
						vector<tm> tmVec = getTmVecFromEvents(normalEvents);

						updater.setAllEvents(normalEvents, floatingEvents, LogicUpdater::CHOOSE_EVENT_MESSAGE, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
						return;
				}

				//case 2: at least 1 partial match
				if (!tempEvents.empty() && tempEvents[0].getID() != INVALID_NUMBER) {
					string feedback = nameOfEvent + LogicUpdater::PARTIAL_EVENT_FOUND_MESSAGE;
					vector<tm> tmVec = getTmVecFromEvents(normalEvents);

					updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
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
			vector<tm> tmVec;
			setOneEventVector(normalEvents, floatingEvents, commandPtr, tmVec);

			Event doneEvent = commandPtr->getEvent();
			string feedback;
			if (command == Parser::DELETE_) { //for delete
				feedback = LogicUpdater::DELETED_MESSAGE + doneEvent.getName();
			} else { //for complete
				feedback = LogicUpdater::COMPLETED_MESSAGE + doneEvent.getName();
			}
			if (!doneEvent.getIsFloating()) {
				if (isSameDate(doneEvent.getStartDate(),doneEvent.getEndDate())) {
					feedback += COMMA_SPACE + updater.setSingleDayString(doneEvent.getStartDate());
				} else {
					feedback += COMMA_SPACE + updater.setMultipleDaysString(doneEvent.getStartDate(),doneEvent.getEndDate());
				}
			}
			
			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
			break;
							  }

		case Parser::EDIT: {
			vector<Event> tempEvents = commandPtr->getEventVector();

			if (!commandPtr->getIsExecuted()) { //2 cases
				setEventVectors(normalEvents, floatingEvents, tempEvents);

				//case 1: more than 1 exact match
				if ( (!floatingEvents.empty() && floatingEvents[0].getName() == nameOfEvent) |
					(!normalEvents.empty() && normalEvents[1].getName() == nameOfEvent) ) {
						vector<tm> tmVec = getTmVecFromEvents(normalEvents);
						updater.setAllEvents(normalEvents, floatingEvents, LogicUpdater::CHOOSE_EVENT_MESSAGE, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
						return;
				}

				//case 2: at least 1 partial match
				if (!tempEvents.empty() && tempEvents[0].getID() != INVALID_NUMBER) {
					string feedback = nameOfEvent + LogicUpdater::PARTIAL_EVENT_FOUND_MESSAGE;
					vector<tm> tmVec = getTmVecFromEvents(normalEvents);

					updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
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
			vector<tm> tmVec;
			setOneEventVector(normalEvents, floatingEvents, commandPtr, tmVec);
			
			Event oldEvent = commandPtr->getEvent();
			int id = oldEvent.getID();
			string feedback = LogicUpdater::EDITED_MESSAGE + oldEvent.getName();
			if (!oldEvent.getIsFloating()) {
				if (isSameDate(oldEvent.getStartDate(),userEvent.getEndDate())) {
					feedback += COMMA_SPACE + updater.setSingleDayString(oldEvent.getStartDate());
				} else {
					feedback += COMMA_SPACE + updater.setMultipleDaysString(oldEvent.getStartDate(),oldEvent.getEndDate());
				}
			}

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id, lastShowType);
			break;
						   }

		case Parser::SEARCH: {
			setEventVectors(normalEvents, floatingEvents, commandPtr->getEventVector());
			vector<tm> tmVec = getTmVecFromEvents(normalEvents);

			updater.setAllEvents(normalEvents, floatingEvents, EMPTY_STRING, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
			break;
							 }

		case Parser::SHOW: 
		case Parser:: SHOWWEEK:
		case Parser:: SHOWMONTH: {
			normalEvents = commandPtr->getEventVector();
			floatingEvents = updater.getFloatingEvents();

			vector<tm> tmVec;
			tmVec.push_back(userEvent.getStartDate());
			tmVec.push_back(userEvent.getEndDate());

			lastShowType = LogicUpdater::EMPTY_STRING;
			if (command == Parser::SHOWWEEK) {
				lastShowType = LogicUpdater::WORD_WEEK;
			}
			if (command == Parser::SHOWMONTH) {
				lastShowType = LogicUpdater::WORD_MONTH;
			}

			string feedback = LogicUpdater::SHOW_MESSAGE;
			if (isSameDate(userEvent.getStartDate(),userEvent.getEndDate())) {
				feedback += updater.setSingleDayString(userEvent.getStartDate());
			} else {
				feedback += updater.setMultipleDaysString(userEvent.getStartDate(),userEvent.getEndDate());
			}
			removeLabel(feedback);

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
			break;
								 }

		case Parser::SHOWALL:
		case Parser::SHOWALLIMPORTANT:
		case Parser::SHOWCOMPLETE:
		case Parser::SHOWIMPORTANT: {
			setEventVectors(normalEvents, floatingEvents, commandPtr->getEventVector());
			string feedback = LogicUpdater::SHOW_MESSAGE + nameOfEvent;
			vector<tm> tmVec = getTmVecFromEvents(normalEvents);
			
			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
			break;
									}

									/*case Parser::SHOWDUE: {
									break;
									}*/

		case Parser::SHOWFLOAT: {
			normalEvents = updater.getNormalEvents();
			floatingEvents = commandPtr->getEventVector();
			vector<tm> tmVec = updater.getTempMainDisplayLabel();

			updater.setAllEvents(normalEvents, floatingEvents, EMPTY_STRING, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
			break;
								}

		case Parser::UNDO:
		case Parser::REDO: {
			if (commandPtr->getEvent().getID() == INVALID_NUMBER) {
				throw false;
			}

			vector<tm> tmVec;
			setOneEventVector(normalEvents, floatingEvents, commandPtr, tmVec);

			string feedback;
			if (command == Parser::UNDO) {
				feedback = LogicUpdater::UNDO_MESSAGE;
			} else {
				feedback = LogicUpdater::REDO_MESSAGE;
			}		

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
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

void Logic::setOneEventVector(vector<Event>& normal, vector<Event>& floating, Command* commandPtr, vector<tm>& tmVec) {
	if (commandPtr->getIsFloating()) {
		floating = commandPtr->getEventVector();

		tmVec = updater.getTempMainDisplayLabel();
		Event dummyEvent;
		dummyEvent.setStartEndDate(tmVec);
		Command* tempCmd = queueCommand(Parser::SHOW, dummyEvent, EMPTY_STRING);
		normal = tempCmd->getEventVector();

	} else {
		normal = commandPtr->getEventVector();
		
		tmVec = getTmVecFromEvents(normal);
		Event dummyEvent;
		dummyEvent.setStartEndDate(tmVec);
		Command* tempCmd = queueCommand(Parser::SHOWFLOAT, dummyEvent, EMPTY_STRING);
		floating = tempCmd->getEventVector();
	}
}

vector<tm> Logic::getTmVecFromEvents(vector<Event> normalEvents) {
	vector<tm> tmVec, currentShowingTM = updater.getTempMainDisplayLabel();

	if (normalEvents.empty()) { //no normal events to show
		tmVec = updater.getTempMainDisplayLabel();

	} else { //at least 1 normal event to show, if it falls within current show range, keep current range
		tmVec.push_back(normalEvents[1].getStartDate());
		tmVec.push_back(normalEvents[normalEvents.size() - 1].getEndDate());

		if (tmVec[0].tm_year >= currentShowingTM[0].tm_year &&
			tmVec[0].tm_mon >= currentShowingTM[0].tm_mon &&
			tmVec[0].tm_mday >= currentShowingTM[0].tm_mday &&
			tmVec[1].tm_year <= currentShowingTM[1].tm_year &&
			tmVec[1].tm_mon <= currentShowingTM[1].tm_mon &&
			tmVec[1].tm_mday <= currentShowingTM[1].tm_mday) {
				tmVec = currentShowingTM;
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

void Logic::removeLabel(string& feedback) {
	for (int i = 0; i < feedback.size(); i++) {
		if (feedback[i] == CHAR_OPEN_SQUARE_BRACKET) {
			feedback.erase(feedback.begin() + i);
			while (feedback[i] != CHAR_CLOSE_SQUARE_BRACKET) {
				feedback.erase(feedback.begin() + i);
			}
			feedback.erase(feedback.begin() + i);
			feedback.erase(feedback.begin() + i);
		}
	}
}