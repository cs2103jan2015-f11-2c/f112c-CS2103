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

	logger.logParserStart(input);
	original = input;
	this->tokenizeOriginalString();
}

Parser::~Parser(void)
{
}

	//GETTERS
Parser::commandType Parser::getCommandType(){
	return typeOfCommand;
}

std::string Parser::getCommand(){
	return command;
}

std::string Parser::getDetails(){
	return details;
}

std::string Parser::getOriginal(){
	return original;
}

Event Parser::getEvent(){
	return tempEventStore;
}

std::string Parser::getNameOfEvent(){
	return nameOfEvent;
}

//MAIN METHODS
//Function takes in the input from the user and determines the command type and organises the information provided into an Event form. Throws exception if the command is unknown.
//These are done by calling InputStringSplit object to separate the input string into its components, and then calling the ParserProcessor object to retrieve the information 
//and organise them into the Event format. 
//Receives any thrown exceptions from the InputStringSplit and ParserProcessor objects and sets the feedback to the user, to be returned to Logic.
void Parser::tokenizeOriginalString(){
	logger.logParserEnterFunc(TOKENISE_ORIGINAL_STRING);

	try {
		command = splitter.extractFirstWord(original);
		if(checkCommandExist()){
			if(!checkCommandUndoRedo()){
				details = splitter.extractDetails(original);
			}
		} else {
			details = original;
			command = "add";
		}
	
		std::vector<std::string> fragmentedWords;
		if(command == "add"){
			fragmentedWords = splitter.fragmentAddString(details);
			tempEventStore = processor.processAddEvent(fragmentedWords);
			if(tempEventStore.getIsFloating() == true){
				typeOfCommand = Parser::ADDFLOAT;
			} else {
				typeOfCommand = Parser::ADD;
			}
		} else if(command == "delete" || command == "del"){
			nameOfEvent = splitter.extractDelEventName(details);
			typeOfCommand = Parser::DELETE_;
		} else if(command == "edit"){
			nameOfEvent = splitter.extractEditEventName(details);
			details = splitter.removeEditEventName(details,nameOfEvent);
			fragmentedWords = splitter.fragmentEditString(details);
			tempEventStore = processor.processEditEvent(fragmentedWords);
			typeOfCommand = Parser::EDIT;
		} else if(command == "show"){
			nameOfEvent = details;
			fragmentedWords = splitter.fragmentShowString(details);
			tempEventStore = processor.processShowEvent(fragmentedWords);
			if(tempEventStore.getName() == "floating" || tempEventStore.getName() == "float"){
				typeOfCommand = Parser::SHOWFLOAT;
			} else if(tempEventStore.getName() == "all"){
				typeOfCommand = Parser::SHOWALL;
			} else if(tempEventStore.getName() == "due"){
				typeOfCommand = Parser::SHOWDUE;
			} else if(tempEventStore.getName() == "specificimportance"){
				typeOfCommand = Parser::SHOWIMPORTANT;
			} else if(tempEventStore.getName() == "important" || tempEventStore.getName() == "impt"){
				typeOfCommand = Parser::SHOWALLIMPORTANT;
			} else {
				typeOfCommand = Parser::SHOW;
			}
		} else if(command == "search"){
			nameOfEvent = details;
			typeOfCommand = Parser::SEARCH;
		} else if(command == "undo"){
			typeOfCommand = Parser::UNDO;
		} else if(command == "redo"){
			typeOfCommand = Parser::REDO;
		} else {
			throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_COMMAND);
		}
		logger.logParserSuccess(original);
	} catch (ParserExceptions& e){
		tempEventStore.setFeedback(createFeedback(e.getExceptionCode()));
		typeOfCommand = Parser::ERROR_;
		logger.logParserFailure(original);
	}
	return;
}

//Checks with a list of commands that Parser recognises to confirm whether the command is supported.
bool Parser::checkCommandExist(){
	bool commandExist = false;

	for(int j = 0; j < NUMBER_OF_KEYWORDS_COMMANDS; j++){
		if(command == keywordCommands[j]){
			commandExist = true;
		}
	}
	return commandExist;
}

//Checks whether the command is an undo or redo command
bool Parser::checkCommandUndoRedo(){
	bool isUndoRedo = false;
	if(command == "undo" || command == "redo"){
		isUndoRedo = true;
	}
	return isUndoRedo;
}

//Sets the feedback based on what exception code was thrown to be returned to Logic and displayed to the user.
std::string Parser::createFeedback(std::string errorCode){
	if(errorCode == ParserExceptions::ERROR_MISSING_INPUT){
		return "Error: Missing input.";
	}
	if(errorCode == ParserExceptions::ERROR_NO_NAME){
		return "Error: No event name found. Please type ';' after an event name.";
	}
	if(errorCode == ParserExceptions::ERROR_TOO_MANY_DATES){
		return "Error: Too many date inputs detected.";
	}
	if(errorCode == ParserExceptions::ERROR_TOO_MANY_TIMES){
		return "Error: Too many time inputs detected.";
	}
	if(errorCode == ParserExceptions::ERROR_MISSING_DAY){
		return "Error: No day input found before month.";
	}
	if(errorCode == ParserExceptions::ERROR_UNUSED_INTEGERS){
		return "Error: Wrong formatting, not all information has been successfully recorded.";
	}
	if(errorCode == ParserExceptions::ERROR_MISSING_HOUR_MIN){
		return "Error: No hour/minute input before am/pm.";
	}
	if(errorCode == ParserExceptions::ERROR_TOO_MANY_DEL){
		return "Error: Too many inputs detected. Input index only, or event name only ending with ';'.";
	}
	if(errorCode == ParserExceptions::ERROR_MISSING_INDEX){
		return "Error: No event index or event name found. Please type ';' after the event name.";
	}
	if(errorCode == ParserExceptions::ERROR_INSUFFICIENT_INFO){
		return "Error: Not enough information to execute command.";
	}
	if(errorCode == ParserExceptions::ERROR_UNKNOWN_COMMAND){
		return "Error: Unknown command.";
	}
	if(errorCode == ParserExceptions::ERROR_UNKNOWN_DATE){
		return "Error: Unknown date input.";
	}
	if(errorCode == ParserExceptions::ERROR_UNKNOWN_HOUR){
		return "Error: Invalid hour input for time.";
	}
	if(errorCode == ParserExceptions::ERROR_UNKNOWN_MINUTE){
		return "Error: Invalid minutes input for time.";
	}
	if(errorCode == ParserExceptions::ERROR_START_AFTER_END){
		return "Error: Start day/time is later than End day/time";
	}
}
