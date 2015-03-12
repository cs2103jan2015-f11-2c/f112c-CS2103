#include "Parser.h"

Parser::Parser(std::string input)
{
	original = input;
	this->retrieveCategories();
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
		nameOfEvent = splitter.extractEventName(details);
		typeOfCommand = Parser::DELETE_;
	} else if(command == "edit"){
		nameOfEvent = splitter.extractEditEventName(details);
		details = splitter.removeEditEventName(details,nameOfEvent);
		fragmentedWords = splitter.fragmentEditString(details);
		tempEventStore = processor.processEditEvent(fragmentedWords);
		typeOfCommand = Parser::EDIT;
	} else if(command == "show"){
		this->identifyShowCommand();
	}

	return;
}

void Parser::retrieveCategories(){
	std::string category;
	std::ifstream readCategories;
	readCategories.open("categories.txt");
	while(std::getline(readCategories,category)){
		categories.push_back(category);
	}
	readCategories.close();

	return;
}

	//SHOW
//Possible show commands:
// -show Day
// -show School
void Parser::identifyShowCommand(){
	if(details == "day"){  //system categories
		typeOfCommand = SHOWDAY;
	} else if(details == "month"){
		typeOfCommand = SHOWMTH;
	} else if(details == "year"){
		typeOfCommand = SHOWYR;
	} else {  //check if category exists for user categories
		/*bool userCategoryFound = false;
		for(int i = 0; i < categories.size() && !userCategoryFound; i++){
			if(details == categories[i]){
				userCategoryFound = true;
			}
		}
		if(userCategoryFound){
		*/	typeOfCommand = SHOWUSER;
			tempEventStore.setName(details);
		} /*
		else {
			typeOfCommand = ERROR_;
		}*/
	
	return;
}