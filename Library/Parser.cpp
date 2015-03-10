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

int Parser::getIndex(){
	return index;
}

//MAIN METHODS
void Parser::tokenizeOriginalString(){
	command = splitter.extractFirstWord(original);
	details = splitter.extractDetails(original);

	std::vector<std::string> fragmentedWords;
	if(command == "add"){
		fragmentedWords = splitter.fragmentAddString(details);
		tempEventStore = processor.processEvent(fragmentedWords);
		typeOfCommand = Parser::ADD;
	}
	else if(command == "delete"){
		fragmentedWords = splitter.fragmentDeleteString(details);
		if(fragmentedWords.size() == 1){
			index = processor.extractEventIndex(fragmentedWords[0]);
			if (index == 0){
				tempEventStore.setName(fragmentedWords[0]);
			}
		} else {
			tempEventStore.setName(details);
		}
		typeOfCommand = Parser::DELETE_;
	}
	else if(command == "edit"){
		index = processor.extractEventIndex(splitter.extractFirstWord(details));
		fragmentedWords = splitter.fragmentEditString(details);
		tempEventStore = processor.processEvent(fragmentedWords);
		typeOfCommand = Parser::EDIT;
	}
	else if(command == "show"){
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

void Parser::identifyDetailToEdit(){
/* INCOMPLETE
	std::string detailToEdit;
	detailToEdit = details.substr(0,details.find_first_of(" "));
	details = details.substr(details.find_first_of(" ")+1);

	if(detailToEdit == "name"){
		eventInfo.name = details;
	}
	else if(detailToEdit == "date"){
		eventInfo.date = details;
	}
	else if(detailToEdit == "time"){
		// INCOMPLETE starttime endtime
		eventInfo.time = details;
	}
	else if(detailToEdit == "tag"){
		eventInfo.tags.push_back(details);
	}
	else if(detailToEdit == "description"){
		eventInfo.description = details;
	}
	else {
		typeOfCommand = ERROR;
	}
*/
	return;
}


	//SHOW
//Possible show commands:
// -show Day
// -show School
void Parser::identifyShowCommand(){
	if(details == "day"){  //system categories
		typeOfCommand = SHOWDAY;
	}
	else if(details == "month"){
		typeOfCommand = SHOWMTH;
	}
	else if(details == "year"){
		typeOfCommand = SHOWYR;
	}
	else {  //check if category exists for user categories
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