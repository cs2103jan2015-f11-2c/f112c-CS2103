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
		} else if(command == "delete"){
			nameOfEvent = splitter.extractDelEventName(details);
			typeOfCommand = Parser::DELETE_;
		} else if(command == "edit"){
			nameOfEvent = splitter.extractEditEventName(details);
			details = splitter.removeEditEventName(details,nameOfEvent);
			fragmentedWords = splitter.fragmentEditString(details);
			tempEventStore = processor.processEditEvent(fragmentedWords);
			typeOfCommand = Parser::EDIT;
		} else if(command == "show"){
			fragmentedWords = splitter.fragmentShowString(details);
			tempEventStore = processor.processShowEvent(fragmentedWords);
			typeOfCommand = Parser::SHOW;
		} else if(command == "search"){
			typeOfCommand = Parser::SEARCH;
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