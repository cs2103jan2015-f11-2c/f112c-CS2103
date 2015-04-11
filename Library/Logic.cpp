//@author A0111089L
#include "Logic.h"


const string Logic::EMPTY_STRING = "";
const string Logic::COMMA_SPACE = ", ";
const string Logic::EXCLAMATION_MARK = "!";
const char Logic::CHAR_OPEN_SQUARE_BRACKET = '[';
const char Logic::CHAR_CLOSE_SQUARE_BRACKET = ']';



//CONSTRUCTOR, DESTRUCTOR
Logic::Logic() {
	parserPtr = NULL;
	lastID = eventFacade.getDataID() + Command::SIZE_ONE;
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



//MAIN API
//returns true if command executed thoroughly, false otherwise
bool Logic::executeUserInput(string input) {
	bool isDone = true;

	try {
		throw isDataRead();
	} catch (bool isRead) {
		if (isRead == false) {
			return !isDone;
		}
	}

	parserPtr = new Parser(input);
	Parser::CommandType commandType = parserPtr->getCommandType();
	Event userEvent = parserPtr->getEvent();
	string nameOfEvent = parserPtr->getNameOfEvent();
	deleteParserPtr();

	Command* commandPtr = queueCommand(commandType, userEvent, nameOfEvent);
	try {
		setUpdater(commandPtr, commandType, userEvent, nameOfEvent);
	} catch (bool isProperCommand) {
		if (!isProperCommand) {
			isDone = false;
		}
	}

	return isDone;
}

//returns true if data successfully read from file, false otherwise
bool Logic::isDataRead() {
	if (!eventFacade.dataRead()) {
		updater.setFeedbackStrings(LogicUpdater::FILE_NOT_READ_MESSAGE);
		return false;
	}
	return true;
}

//dynamically creates command object, call executor to execute it
Command* Logic::queueCommand(Parser::CommandType command, Event& userEvent, string nameOfEvent) {
	assert(isProperCommand(command));
	
	try {
		switch (command) {
		case Parser::ADD:
		case Parser::ADDFLOAT: {
			setNewID(userEvent);

			Command* addCommand = new AddCommand(&eventFacade, userEvent, updater.getTempMainDisplayLabel());
			logger.log(LogicLog::CREATED + LogicLog::ADD);
			return executor.execute(addCommand);
							   }

		case Parser::COMPLETE: {
			int id = convertNameToID(nameOfEvent);
			Event eventToComplete = createTempEvent(nameOfEvent, id);

			if (eventToComplete.getIsCompleted()) {
				return new NullCommand;
			}

			Command* completeCommand = new CompleteCommand(&eventFacade, id, eventToComplete, updater.getTempMainDisplayLabel());
			logger.log(LogicLog::CREATED + LogicLog::COMPLETE);
			return executor.execute(completeCommand);
							   }

		case Parser::UNCOMPLETE: {
			vector<Event> resultEvents = getExactMatches(nameOfEvent);
			
			Command* uncompleteCommand = new UncompleteCommand(&eventFacade, resultEvents, updater.getTempMainDisplayLabel());
			logger.log(LogicLog::CREATED + LogicLog::UNCOMPLETE);
			return executor.execute(uncompleteCommand);
								 }

		case Parser::DELETE_: {
			int id = convertNameToID(nameOfEvent);
			Event eventToDelete = createTempEvent(nameOfEvent, id);
			
			if (eventToDelete.getIsCompleted()) {
				return new NullCommand;
			}

			Command* deleteCommand = new DeleteCommand(&eventFacade, id, eventToDelete, updater.getTempMainDisplayLabel());
			logger.log(LogicLog::CREATED + LogicLog::DELETE);
			return executor.execute(deleteCommand);
							  }

		case Parser::EDIT: {
			int id = convertNameToID(nameOfEvent);
			Event eventToEdit = createTempEvent(nameOfEvent, id);

			if (eventToEdit.getIsCompleted()) {
				throw false;
			}
			
			if (eventToEdit.getIsDeadline() && !isSameDate(userEvent.getStartDate(), userEvent.getEndDate())) {
				throw false;
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

		case Parser::SHOWFLOAT: {
			Command* showFloatCommand = new ShowFloatCommand(&eventFacade);
			logger.log(LogicLog::CREATED + LogicLog::SHOWFLOAT);
			return executor.execute(showFloatCommand);
								}

		case Parser::SHOWIMPORTANT: {
			Command* showImportanceCommand = new ShowImportanceCommand(&eventFacade, userEvent.getImportanceLevel());
			logger.log(LogicLog::CREATED + LogicLog::SHOWIMPORTANCE);
			return executor.execute(showImportanceCommand);
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
void Logic::setUpdater(Command* commandPtr, Parser::CommandType command, Event userEvent, string nameOfEvent) {
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

			clearRedo();
			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id, lastShowType);
			break;
						  }

		case Parser::ADDFLOAT: {		
			vector<tm> tmVec;
			setOneEventVector(normalEvents, floatingEvents, commandPtr, tmVec);
			string feedback = LogicUpdater::ADDED_MESSAGE + userEvent.getName();
			int id = userEvent.getID();

			clearRedo();
			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id, lastShowType);
			break;
							   }

		case Parser::COMPLETE:
		case Parser::DELETE_: {
			vector<Event> tempEvents = commandPtr->getEventVector();

			//2 cases
			if (!commandPtr->getIsExecuted()) { 
				setEventVectors(normalEvents, floatingEvents, tempEvents);

				//case 1: more than 1 exact match
				if ( (!floatingEvents.empty() && floatingEvents[Command::SIZE_ZERO].getName() == nameOfEvent) |
					(!normalEvents.empty() && normalEvents[Command::SIZE_ONE].getName() == nameOfEvent) ) {
						vector<tm> tmVec = getTmVecFromEvents(normalEvents);

						updater.setAllEvents(normalEvents, floatingEvents, LogicUpdater::CHOOSE_EVENT_MESSAGE, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
						return;
				}

				//case 2: at least 1 partial match
				if (!tempEvents.empty() && tempEvents[Command::SIZE_ZERO].getID() != Command::INVALID_NUMBER) {
					string feedback = nameOfEvent + LogicUpdater::PARTIAL_EVENT_FOUND_MESSAGE;
					vector<tm> tmVec = getTmVecFromEvents(normalEvents);

					updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
					return;
				}
			}

			//no event found
			if (!tempEvents.empty() && tempEvents[Command::SIZE_ZERO].getID() == Command::INVALID_NUMBER) {
				string feedback = nameOfEvent + LogicUpdater::EVENT_NOT_FOUND_MESSAGE;

				updater.setFeedbackStrings(feedback);
				throw !isDone;
			}

			//successful complete/delete
			if (commandPtr->getIsUndoable() == false) { //user tried to change completed event
				updater.setFeedbackStrings(LogicUpdater::DONE_EVENT_ERROR_MESSAGE);
				throw !isDone;
			}

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
				if (isSameDate(doneEvent.getStartDate(), doneEvent.getEndDate())) {
					feedback += COMMA_SPACE + updater.setSingleDayString(doneEvent.getStartDate());
				} else {
					feedback += COMMA_SPACE + updater.setMultipleDaysString(doneEvent.getStartDate(), doneEvent.getEndDate());
				}
			}

			if (command != Parser::UNCOMPLETE) {
				clearRedo();
			}
			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
			break;
							  }

		case Parser::UNCOMPLETE: {
			vector<Event> tempEvents = commandPtr->getEventVector();

			//more than 1 exact match
			if (!commandPtr->getIsExecuted()) { 
				setEventVectors(normalEvents, floatingEvents, tempEvents);
				vector<tm> tmVec = getTmVecFromEvents(normalEvents);
				updater.setAllEvents(normalEvents, floatingEvents, LogicUpdater::CHOOSE_EVENT_MESSAGE, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
				return;
			}

			Event uncompletedEvent = commandPtr->getEvent();
			int id = uncompletedEvent.getID();
			
			//no event found 
			if (id == Command::INVALID_NUMBER) {
				string feedback = nameOfEvent + LogicUpdater::EVENT_NOT_FOUND_MESSAGE;
				updater.setFeedbackStrings(feedback);
				throw !isDone;
			}

			//successful uncomplete
			vector<tm> tmVec;
			setOneEventVector(normalEvents, floatingEvents, commandPtr, tmVec);

			string feedback = LogicUpdater::UNCOMPLETED_MESSAGE + uncompletedEvent.getName();
			if (!uncompletedEvent.getIsFloating()) {
				if (isSameDate(uncompletedEvent.getStartDate(), uncompletedEvent.getEndDate())) {
					feedback += COMMA_SPACE + updater.setSingleDayString(uncompletedEvent.getStartDate());
				} else {
					feedback += COMMA_SPACE + updater.setMultipleDaysString(uncompletedEvent.getStartDate(), uncompletedEvent.getEndDate());
				}
			}

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, id, lastShowType);
			break;
								 }

		case Parser::EDIT: {
			vector<Event> tempEvents = commandPtr->getEventVector();

			//2 cases
			if (!commandPtr->getIsExecuted()) { 
				setEventVectors(normalEvents, floatingEvents, tempEvents);

				//case 1: more than 1 exact match
				if ( (!floatingEvents.empty() && floatingEvents[Command::SIZE_ZERO].getName() == nameOfEvent) |
					(!normalEvents.empty() && normalEvents[Command::SIZE_ONE].getName() == nameOfEvent) ) {
						vector<tm> tmVec = getTmVecFromEvents(normalEvents);

						updater.setAllEvents(normalEvents, floatingEvents, LogicUpdater::CHOOSE_EVENT_MESSAGE, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
						return;
				}

				//case 2: at least 1 partial match
				if (!tempEvents.empty() && tempEvents[Command::SIZE_ZERO].getID() != Command::INVALID_NUMBER) {
					string feedback = nameOfEvent + LogicUpdater::PARTIAL_EVENT_FOUND_MESSAGE;
					vector<tm> tmVec = getTmVecFromEvents(normalEvents);

					updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
					return;
				}
			}

			//no event found 
			if (!tempEvents.empty() && tempEvents[Command::SIZE_ZERO].getID() == Command::INVALID_NUMBER) {
				string feedback = nameOfEvent + LogicUpdater::EVENT_NOT_FOUND_MESSAGE;
				updater.setFeedbackStrings(feedback);
				throw !isDone;
			}

			//successful edit 
			if (commandPtr->getIsUndoable() == false) { 
				if (userEvent.getIsCompleted()) { //user tried to change completed event
					updater.setFeedbackStrings(LogicUpdater::DONE_EVENT_ERROR_MESSAGE);
				} else { //user tried to edit deadline event to have more than one time
					updater.setFeedbackStrings(LogicUpdater::DEADLINE_EVENT_ERROR_MESSAGE);
				}
				throw !isDone;
			}

			vector<tm> tmVec;
			setOneEventVector(normalEvents, floatingEvents, commandPtr, tmVec);

			Event oldEvent = commandPtr->getEvent();
			int id = oldEvent.getID();

			string feedback = LogicUpdater::EDITED_MESSAGE + oldEvent.getName();
			if (!oldEvent.getIsFloating()) {
				if (isSameDate(oldEvent.getStartDate(), oldEvent.getEndDate())) {
					feedback += COMMA_SPACE + updater.setSingleDayString(oldEvent.getStartDate());
				} else {
					feedback += COMMA_SPACE + updater.setMultipleDaysString(oldEvent.getStartDate(), oldEvent.getEndDate());
				}
			}

			clearRedo();
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
			Command* tempCmd = queueCommand(Parser::SHOWFLOAT, userEvent, nameOfEvent);
			floatingEvents = tempCmd->getEventVector();

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
			string feedback = showTypeToString(command, userEvent.getImportanceLevel());
			vector<tm> tmVec = getTmVecFromEvents(normalEvents);

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
			break;
									}

		case Parser::SHOWFLOAT: {
			normalEvents = updater.getNormalEvents();
			floatingEvents = commandPtr->getEventVector();
			vector<tm> tmVec = updater.getTempMainDisplayLabel();

			updater.setAllEvents(normalEvents, floatingEvents, EMPTY_STRING, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
			break;
								}

		case Parser::UNDO: {
			if (commandPtr->getEvent().getID() == Command::INVALID_NUMBER) {
				updater.setFeedbackStrings(LogicUpdater::NO_MORE_UNDO_MESSAGE);
				throw !isDone;
			}

			vector<tm> tmVec;
			setOneEventVector(normalEvents, floatingEvents, commandPtr, tmVec);
			string feedback = LogicUpdater::UNDO_MESSAGE;

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
			break;
						   }

		case Parser::REDO: {
			if (commandPtr->getEvent().getID() == Command::INVALID_NUMBER) {
				updater.setFeedbackStrings(LogicUpdater::NO_MORE_REDO_MESSAGE);
				throw !isDone;
			}

			vector<tm> tmVec;
			setOneEventVector(normalEvents, floatingEvents, commandPtr, tmVec);
			string feedback = LogicUpdater::REDO_MESSAGE;

			updater.setAllEvents(normalEvents, floatingEvents, feedback, tmVec, LogicUpdater::GARBAGE_INT, lastShowType);
			break;
						   }


		case Parser::ERROR_: {
			updater.setFeedbackStrings(userEvent.getFeedback());
			throw !isDone;
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
	
	unsigned int i = Command::SIZE_ZERO;
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
		Command* tempCmd = queueCommand(Parser::SHOWFLOAT, dummyEvent, EMPTY_STRING);
		floating = tempCmd->getEventVector();
	}
}

vector<tm> Logic::getTmVecFromEvents(vector<Event> normalEvents) {
	vector<tm> tmVec, currentShowingTM = updater.getTempMainDisplayLabel();

	if (normalEvents.empty()) { //no normal events to show
		tmVec = updater.getTempMainDisplayLabel();

	} else { //at least 1 normal event to show, if it falls within current show range then return current range, if not then return new range
		tmVec.push_back(normalEvents[Command::SIZE_ONE].getStartDate());
		tmVec.push_back(normalEvents[normalEvents.size() - 1].getEndDate());

		if (tmVec[Command::SIZE_ZERO].tm_year >= currentShowingTM[Command::SIZE_ZERO].tm_year &&
			tmVec[Command::SIZE_ZERO].tm_mon >= currentShowingTM[Command::SIZE_ZERO].tm_mon &&
			tmVec[Command::SIZE_ZERO].tm_mday >= currentShowingTM[Command::SIZE_ZERO].tm_mday &&
			tmVec[Command::SIZE_ONE].tm_year <= currentShowingTM[Command::SIZE_ONE].tm_year &&
			tmVec[Command::SIZE_ONE].tm_mon <= currentShowingTM[Command::SIZE_ONE].tm_mon &&
			tmVec[Command::SIZE_ONE].tm_mday <= currentShowingTM[Command::SIZE_ONE].tm_mday) {
				tmVec = currentShowingTM;
		} 
	}

	return tmVec;
}

void Logic::deleteParserPtr() {
	delete parserPtr;
	parserPtr = NULL;
}



//SUPPORTING METHODS
bool Logic::isProperCommand(Parser::CommandType commandType) {
	return ( (commandType == Parser::ADD) |
		(commandType == Parser::ADDFLOAT) |
		(commandType == Parser::COMPLETE) |
		(commandType == Parser::UNCOMPLETE) |
		(commandType == Parser::DELETE_) |
		(commandType == Parser::EDIT) |
		(commandType == Parser::SEARCH) |
		(commandType == Parser::SHOW) |
		(commandType == Parser::SHOWWEEK) |
		(commandType == Parser::SHOWMONTH) |
		(commandType == Parser::SHOWALL) |
		(commandType == Parser::SHOWALLIMPORTANT) |
		(commandType == Parser::SHOWCOMPLETE) |
		(commandType == Parser::SHOWFLOAT) |
		(commandType == Parser::SHOWIMPORTANT) |
		(commandType == Parser::UNDO) |
		(commandType == Parser::REDO) |
		(commandType == Parser::ERROR_) );
}

//returns true if input string consists of only numeric digits, false otherwise
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

//returns true if 2 input dates have same mday and mon and year, false otherwise
bool Logic::isSameDate(tm date1, tm date2) {
	return(date1.tm_mday == date2.tm_mday &&
		date1.tm_mon == date2.tm_mon &&
		date1.tm_year == date2.tm_year);
}

string Logic::showTypeToString(Parser::CommandType cmd, int importance) {
	switch (cmd) {
	case Parser::SHOWALL: {
		return LogicUpdater::SHOWALL_MESSAGE;
						  }

	case Parser::SHOWALLIMPORTANT: {
		return LogicUpdater::SHOWALLIMPORTANT_MESSAGE;
								   }

	case Parser::SHOWCOMPLETE: {
		return LogicUpdater::SHOWCOMPLETE_MESSAGE;
							   }

	case Parser::SHOWIMPORTANT: {
		string cmdString = LogicUpdater::SHOWIMPORTANT_MESSAGE;
		int countImportance = Command::SIZE_ZERO;
		while (countImportance != importance) {
			cmdString += EXCLAMATION_MARK;
			countImportance++;
		}
		return cmdString;
								}

	default: {
		return LogicLog::ERROR;
			 }
	}
}

//returns id of event if found in updater, -1 otherwise
int Logic::convertNameToID(string name) {
	if (isNumber(name)) {
		int index = std::stoi(name);

		if (index <= Command::SIZE_ZERO) {
			return Command::INVALID_NUMBER;
		}

		if (index > updater.getTotalNumEvents()) {
			return Command::INVALID_NUMBER;
		} else {
			return updater.getIDFromIndex(index);
		}
	} else {
		return Command::INVALID_NUMBER;
	}
}

//removes label enclosed by "[]" from input string
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

//set id for newly added event
void Logic::setNewID(Event& userEvent) {
	userEvent.setID(lastID);
	lastID++;
}


void Logic::clearRedo() {
	executor.clearRedo();
}

//returns temporary event with name taken from user input, if id is found in updater it returns the exact event
Event Logic::createTempEvent(string name, int id) {
	Event tempEvent;
	tempEvent.setName(name);
	if (id != Command::INVALID_NUMBER) {
		tempEvent = updater.getEventFromID(id);
	}
	return tempEvent;
}

vector<Event> Logic::getExactMatches(string name) {
	int index = Command::INVALID_NUMBER;
	if (isNumber(name)) {
		index = std::stoi(name);

		if (index <= Command::SIZE_ZERO | index > updater.getTotalNumEvents()) {
			index = Command::INVALID_NUMBER;
		}
	}
	
	return updater.getExactNameMatches(index, name);
}