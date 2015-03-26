#include "Parser.h"

const std::string Parser::TOKENISE_ORIGINAL_STRING = "tokeniseOriginalString";

Parser::Parser(std::string input)
{
	logger.logParserStart(input);
	original = input;
	//this->retrieveCategories();
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
		details = splitter.extractDetails(original);
	
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

/*void Parser::retrieveCategories(){
	std::string category;
	std::ifstream readCategories;
	readCategories.open("categories.txt");
	while(std::getline(readCategories,category)){
		categories.push_back(category);
	}
	readCategories.close();

	return;
}*/