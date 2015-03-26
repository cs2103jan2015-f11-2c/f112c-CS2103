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
		tempEventStore.setFeedback(e.getfeedback());
		typeOfCommand = Parser::ERROR_;
		logger.logParserFailure(original);
	}
	return;
}

bool Parser::checkCommandExist(){
	bool commandExist = false;

	for(int j = 0; j < NUMBER_OF_KEYWORDS_COMMANDS; j++){
		if(command == keywordCommands[j]){
			commandExist = true;
		}
	}
	return commandExist;
}

bool Parser::checkCommandUndoRedo(){
	bool isUndoRedo = false;
	if(command == "undo" || command == "redo"){
		isUndoRedo = true;
	}
	return isUndoRedo;
}