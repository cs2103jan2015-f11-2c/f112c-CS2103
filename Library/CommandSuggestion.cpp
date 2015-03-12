#include "CommandSuggestion.h"


CommandSuggestion::CommandSuggestion(void)
{
	setUpsuggestionAdd();
	setUpsuggestionDelete();
	setUpsuggestionEdit();
	setUpsuggestionSearch();
	setUpsuggestionShow();
}


CommandSuggestion::~CommandSuggestion(void)
{
}

// static strings that cannot initialise in "CommandSuggestion.h"
const std::string CommandSuggestion::COMMAND_ADD = "add";
const std::string CommandSuggestion::COMMAND_DELETE = "delete";
const std::string CommandSuggestion::COMMAND_EDIT = "edit";
const std::string CommandSuggestion::COMMAND_SEARCH = "search";
const std::string CommandSuggestion::COMMAND_SHOW = "show";
const std::string CommandSuggestion::COMMAND_UNDO = "undo";
const std::string CommandSuggestion::COMMAND_REDO = "redo";
const std::string CommandSuggestion::COMMAND_EXIT = "exit";
const std::string CommandSuggestion::COMMAND_HELP = "help";

const std::string CommandSuggestion::COMMAND_AD = "ad";
const std::string CommandSuggestion::COMMAND_DELET = "delet";
const std::string CommandSuggestion::COMMAND_EDI = "edi";
const std::string CommandSuggestion::COMMAND_SEARC = "searc";
const std::string CommandSuggestion::COMMAND_SHO = "sho";

const std::string CommandSuggestion::SUGGESTION_ADD_1 = " add lunch";
const std::string CommandSuggestion::SUGGESTION_ADD_2 = " add CS2103 exam @10feb 11am-2pm";
const std::string CommandSuggestion::SUGGESTION_ADD_3 = " add Holidays @15june-30june 9am-9am";

const std::string CommandSuggestion::SUGGESTION_DELETE_1 = " delete 2";
const std::string CommandSuggestion::SUGGESTION_DELETE_2 =  " delete CS2103 exam" ;

const std::string CommandSuggestion::SUGGESTION_EDIT_1 = " edit 4 time 4pm-6pm";
const std::string CommandSuggestion::SUGGESTION_EDIT_2 =  " delete CS2103 exam" ;

const std::string CommandSuggestion::SUGGESTION_SEARCH_1 = " search CS2103 exam";
const std::string CommandSuggestion::SUGGESTION_SEARCH_2 = " search 10feb";

const std::string CommandSuggestion::SUGGESTION_SHOW_1 = " show 10feb";
const std::string CommandSuggestion::SUGGESTION_SHOW_2 = " show week 10feb(date where the week is in)";
const std::string CommandSuggestion::SUGGESTION_SHOW_3 = " show month 3 (which month)";


void CommandSuggestion::setUpsuggestionAdd(){
	_suggestionAdd.push_back(SUGGESTION_ADD_1);
	_suggestionAdd.push_back(SUGGESTION_ADD_2);
	_suggestionAdd.push_back(SUGGESTION_ADD_3);
}

void CommandSuggestion::setUpsuggestionDelete(){
	_suggestionDelete.push_back(SUGGESTION_DELETE_1);
	_suggestionDelete.push_back(SUGGESTION_DELETE_2);

}
void CommandSuggestion::setUpsuggestionEdit(){
	_suggestionEdit.push_back(SUGGESTION_EDIT_1);
	_suggestionEdit.push_back(SUGGESTION_EDIT_2);
}

void CommandSuggestion::setUpsuggestionSearch(){
	_suggestionSearch.push_back(SUGGESTION_SEARCH_1);
	_suggestionSearch.push_back(SUGGESTION_SEARCH_2);
}

void CommandSuggestion::setUpsuggestionShow(){
	_suggestionShow.push_back(SUGGESTION_SHOW_1);
	_suggestionShow.push_back(SUGGESTION_SHOW_2);
	_suggestionShow.push_back(SUGGESTION_SHOW_3);
}


CommandSuggestion::ComdType CommandSuggestion::getComdType (std::string comdInString){
	CommandSuggestion::ComdType typeOfComd;

	if(comdInString == COMMAND_ADD){
		typeOfComd = ADD_;
	} else if (comdInString == COMMAND_DELETE){
		typeOfComd = DELETE_;
	} else if (comdInString == COMMAND_EDIT){
		typeOfComd = EDIT_;
	} else if (comdInString == COMMAND_SEARCH){
		typeOfComd = SEARCH_;
	} else if (comdInString == COMMAND_SHOW){
		typeOfComd = SHOW_;
	} else if (comdInString == COMMAND_AD || comdInString == COMMAND_DELET || comdInString == COMMAND_EDI || comdInString == COMMAND_SEARC || comdInString == COMMAND_SHO){
		typeOfComd = UNDISPLAY_;
	} else {
		typeOfComd = INVALID_;
	}
	
	return typeOfComd;
}


std::vector<std::string>  CommandSuggestion::getSuggestionAdd(){
	return _suggestionAdd;
}

std::vector<std::string>  CommandSuggestion::getSuggestionDelete(){
	return _suggestionDelete;
}

std::vector<std::string>  CommandSuggestion::getSuggestionEdit(){
	return _suggestionEdit;
}

std::vector<std::string>  CommandSuggestion::getSuggestionSearch(){
	return _suggestionSearch;
}

std::vector<std::string>  CommandSuggestion::getSuggestionShow(){
	return _suggestionShow;
}








