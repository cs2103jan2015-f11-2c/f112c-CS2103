//@author A0111379H

#include "Parser.h"

const std::string Parser::TOKENISE_ORIGINAL_STRING = "tokeniseOriginalString";

Parser::Parser(std::string input)
{
	keywordCommands[0] = "add";
	keywordCommands[1] = "del";
	keywordCommands[2] = "delete";
	keywordCommands[3] = "edit";
	keywordCommands[4] = "show";
	keywordCommands[5] = "search";
	keywordCommands[6] = "undo";
	keywordCommands[7] = "redo";
	keywordCommands[8] = "done";
	keywordCommands[9] = "completed";
	keywordCommands[10] = "complete";
	keywordCommands[11] = "uncomplete";
	keywordCommands[12] = "undone";

	logger.logParserStart(input);
	original = input;
	this->processInput();
}

Parser::~Parser(void)
{
}

	//GETTERS
Parser::CommandType Parser::getCommandType() {
	return typeOfCommand;
}

std::string Parser::getCommand() {
	return command;
}

std::string Parser::getDetails() {
	return details;
}

std::string Parser::getOriginal() {
	return original;
}

Event Parser::getEvent() {
	return tempEventStore;
}

std::string Parser::getNameOfEvent() {
	return nameOfEvent;
}

//MAIN METHODS
//Function takes in the input from the user and determines the command type and organises the information provided into an Event form. Throws exception if the command is unknown.
//These are done by calling InputStringSplit object to separate the input string into its components, and then calling the ParserProcessor object to retrieve the information 
//and organise them into the Event format. 
//Receives any thrown exceptions from the InputStringSplit and ParserProcessor objects and sets the feedback to the user, to be returned to Logic.
void Parser::processInput() {
	try {
		tokenizeOriginalString();
		determineCommandType();
		logger.logParserSuccess(original);
	} catch (ParserExceptions& e) {
		tempEventStore.setFeedback(createFeedback(e.getExceptionCode()));
		typeOfCommand = Parser::ERROR_;
		logger.logParserFailure(original);
	}
}

//Function splits the input string into command and details.
void Parser::tokenizeOriginalString() {
	logger.logParserEnterFunc(TOKENISE_ORIGINAL_STRING);

	try {
		command = splitter.extractFirstWord(original);
		if (checkCommandExist()) {
			if (!checkCommandUndoRedo()) {
				details = splitter.extractDetails(original);
			}
		} else {
			details = original;
			command = "add";
		}
	} catch (ParserExceptions& e) {
		throw e;
	}
}

void Parser::determineCommandType() {
	try {
		if (command == "add") {
			determineAddCommand();
		} else if (command == "delete" || command == "del") {
			determineDelCommand();
		} else if (command == "edit") {
			determineEditCommand();
		} else if (command == "show") {
			determineShowCommand();
		} else if (command == "done" || command == "completed" || command == "complete") {
			determineCompleteCommand();
		} else if (command == "uncomplete" || command == "undone"){
			determineUncompleteCommand();
		} else if (command == "search" || command == "undo" || command == "redo") {
			determineOtherCommand();
		} else {
			throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_COMMAND);
		}
	} catch (ParserExceptions& e) {
		throw e;
	}
	return;
}

//@author A0111230J

void Parser::determineAddCommand() {
	std::vector<std::string> fragmentedWords;

	try {
		fragmentedWords = splitter.fragmentString(details);
		tempEventStore = processor.processAddEvent(fragmentedWords);
		if (tempEventStore.getIsFloating() == true) {
			typeOfCommand = Parser::ADDFLOAT;
		} else {
			typeOfCommand = Parser::ADD;
		}
	} catch (ParserExceptions& e) {
		throw e;
	}
}

void Parser::determineDelCommand() {
	try {
		nameOfEvent = details;
		typeOfCommand = Parser::DELETE_;
	} catch (ParserExceptions& e) {
		throw e;
	}
}

void Parser::determineEditCommand() {
	std::vector<std::string> fragmentedWords;
	
	try {
		nameOfEvent = splitter.extractEditEventName(details);
		details = splitter.removeEditEventName(details,nameOfEvent);
		fragmentedWords = splitter.fragmentString(details);
		tempEventStore = processor.processEditEvent(fragmentedWords);
		typeOfCommand = Parser::EDIT;
	} catch (ParserExceptions& e) {
		throw e;
	}
}

void Parser::determineShowCommand() {
	std::vector<std::string> fragmentedWords;
	
	try {
		nameOfEvent = details;
		fragmentedWords = splitter.fragmentString(details);
		tempEventStore = processor.processShowEvent(fragmentedWords);
		if (tempEventStore.getName() == "floating" || tempEventStore.getName() == "float") {
			typeOfCommand = Parser::SHOWFLOAT;
		} else if (tempEventStore.getName() == "all") {
			typeOfCommand = Parser::SHOWALL;
		} else if (tempEventStore.getName() == "specificimportance") {
			typeOfCommand = Parser::SHOWIMPORTANT;
		} else if (tempEventStore.getName() == "important" || tempEventStore.getName() == "impt") {
			typeOfCommand = Parser::SHOWALLIMPORTANT;
		} else if (tempEventStore.getName() == "completed" || tempEventStore.getName() == "done" || tempEventStore.getName() == "complete") {
			typeOfCommand = Parser::SHOWCOMPLETE;
		} else if (tempEventStore.getName() == "week") {
			typeOfCommand = Parser::SHOWWEEK;
		} else if (tempEventStore.getName() == "month") {
			typeOfCommand = Parser::SHOWMONTH;
		} else {
			typeOfCommand = Parser::SHOW;
		}
	} catch (ParserExceptions& e) {
		throw e;
	}
}

void Parser::determineCompleteCommand() {
	nameOfEvent = details;
	typeOfCommand = Parser::COMPLETE;
}

void Parser::determineUncompleteCommand() {
	nameOfEvent = details;
	typeOfCommand = Parser::UNCOMPLETE;
}

void Parser::determineOtherCommand() {
	if (command == "search") {
		nameOfEvent = details;
		typeOfCommand = Parser::SEARCH;
	} else if (command == "undo") {
		typeOfCommand = Parser::UNDO;
	} else if (command == "redo") {
		typeOfCommand = Parser::REDO;
	}
}

//Checks with a list of commands that Parser recognises to confirm whether the command is supported.
bool Parser::checkCommandExist() {
	bool commandExist = false;

	for (int j = 0; j < NUMBER_OF_KEYWORDS_COMMANDS; j++) {
		if (command == keywordCommands[j]) {
			commandExist = true;
		}
	}
	return commandExist;
}

//Checks whether the command is an undo or redo command
bool Parser::checkCommandUndoRedo() {
	bool isUndoRedo = false;
	if (command == "undo" || command == "redo") {
		isUndoRedo = true;
	}
	return isUndoRedo;
}

//@author A0111379H

//Sets the feedback based on what exception code was thrown to be returned to Logic and displayed to the user.
std::string Parser::createFeedback(std::string errorCode) {
	std::string tempFeedback;
	if (errorCode == ParserExceptions::ERROR_MISSING_INPUT) {
		tempFeedback = "Error: Invalid input.";
	}
	if (errorCode == ParserExceptions::ERROR_TOO_MANY_DATES) {
		tempFeedback = "Error: Exceeded maximum of 2 date inputs.";
	}
	if (errorCode == ParserExceptions::ERROR_TOO_MANY_TIMES) {
		tempFeedback = "Error: Exceeded maximum of 2 time inputs.";
	}
	if (errorCode == ParserExceptions::ERROR_MISSING_DAY) {
		tempFeedback = "Error: No day input found before month.";
	}
	if (errorCode == ParserExceptions::ERROR_UNUSED_INFORMATION) {
		tempFeedback = "Error: Wrong formatting, not all information has been successfully recorded.";
	}
	if (errorCode == ParserExceptions::ERROR_MISSING_HOUR_MIN) {
		tempFeedback = "Error: No hour/minute input before am/pm.";
	}
	if (errorCode == ParserExceptions::ERROR_MISSING_INDEX) {
		tempFeedback = "Error: No event index or event name found.";
	}
	if (errorCode == ParserExceptions::ERROR_INSUFFICIENT_INFO) {
		tempFeedback = "Error: Not enough information to execute command.";
	}
	if (errorCode == ParserExceptions::ERROR_UNKNOWN_COMMAND) {
		tempFeedback = "Error: Unknown command.";
	}
	if (errorCode == ParserExceptions::ERROR_UNKNOWN_DATE) {
		tempFeedback = "Error: Unknown date input.";
	}
	if (errorCode == ParserExceptions::ERROR_UNKNOWN_HOUR) {
		tempFeedback = "Error: Invalid hour input for time.";
	}
	if (errorCode == ParserExceptions::ERROR_UNKNOWN_MINUTE) {
		tempFeedback = "Error: Invalid minutes input for time.";
	}
	if (errorCode == ParserExceptions::ERROR_START_AFTER_END) {
		tempFeedback = "Error: Start day is later than End day";
	}
	if (errorCode == ParserExceptions::ERROR_NO_SHOW) {
		tempFeedback = "Error: No registered show found. Please use search instead.";
	}
	if (errorCode == ParserExceptions::ERROR_DUE_TOO_MANY_DATES) {
		tempFeedback = "Error: Exceeded maximum of 1 date input for deadline events.";
	}
	if (errorCode == ParserExceptions::ERROR_DUE_TOO_MANY_TIMES) {
		tempFeedback = "Error: Exceeded maximum of 1 time input for deadline events";
	}
	if (errorCode == ParserExceptions::ERROR_INVALID_YEAR) {
		tempFeedback = "Error: Year input out of range. Accepted range: 1971 - 2999";
	}
	if (errorCode == ParserExceptions::ERROR_NO_EDIT_TO_DEADLINE) {
		tempFeedback = "Error: Cannot edit to deadline events";
	}
	return tempFeedback;
}
