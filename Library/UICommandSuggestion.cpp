#include "UICommandSuggestion.h"


UICommandSuggestion::UICommandSuggestion(void)
{
	setUpsuggestionAdd();
	setUpsuggestionDelete();
	setUpsuggestionEdit();
	setUpsuggestionSearch();
	setUpsuggestionShow();
}


UICommandSuggestion::~UICommandSuggestion(void)
{
}

// static strings that cannot initialise in "UICommandSuggestion.h"
const std::string UICommandSuggestion::COMMAND_ADD = "add";
const std::string UICommandSuggestion::COMMAND_DELETE = "delete";
const std::string UICommandSuggestion::COMMAND_EDIT = "edit";
const std::string UICommandSuggestion::COMMAND_SEARCH = "search";
const std::string UICommandSuggestion::COMMAND_SHOW = "show";

const std::string UICommandSuggestion::COMMAND_AD = "ad";
const std::string UICommandSuggestion::COMMAND_DELET = "delet";
const std::string UICommandSuggestion::COMMAND_EDI = "edi";
const std::string UICommandSuggestion::COMMAND_SEARC = "searc";
const std::string UICommandSuggestion::COMMAND_SHO = "sho";

const std::string UICommandSuggestion::SUGGESTION_ADD_1 = " add CS2103 finals; 8feb 8am to 1015am (1 day event)";
const std::string UICommandSuggestion::SUGGESTION_ADD_2 = " add Holidays; 17-19apr 9.30-11.45pm (event over several days)";
const std::string UICommandSuggestion::SUGGESTION_ADD_3 = " add Go for a run; 9am (Today)";

const std::string UICommandSuggestion::SUGGESTION_DELETE_1 = " delete 2";
const std::string UICommandSuggestion::SUGGESTION_DELETE_2 =  " delete Study;";

const std::string UICommandSuggestion::SUGGESTION_EDIT_1 = " edit CS2103 finals; CS2103 V0.5; (change name) ";
const std::string UICommandSuggestion::SUGGESTION_EDIT_2 =  " edit CS2103 finals; 9am-10am (change time)" ;

const std::string UICommandSuggestion::SUGGESTION_SEARCH_1 = " search CS2103 exam";
const std::string UICommandSuggestion::SUGGESTION_SEARCH_2 = " search 10feb";

const std::string UICommandSuggestion::SUGGESTION_SHOW_1 = " show 10feb";
const std::string UICommandSuggestion::SUGGESTION_SHOW_2 = " show 14-18apr";
const std::string UICommandSuggestion::SUGGESTION_SHOW_3 = " show month mar";


void UICommandSuggestion::setUpsuggestionAdd(){
	_suggestionAdd.push_back(SUGGESTION_ADD_1);
	_suggestionAdd.push_back(SUGGESTION_ADD_2);
	_suggestionAdd.push_back(SUGGESTION_ADD_3);
}

void UICommandSuggestion::setUpsuggestionDelete(){
	_suggestionDelete.push_back(SUGGESTION_DELETE_1);
	_suggestionDelete.push_back(SUGGESTION_DELETE_2);

}
void UICommandSuggestion::setUpsuggestionEdit(){
	_suggestionEdit.push_back(SUGGESTION_EDIT_1);
	_suggestionEdit.push_back(SUGGESTION_EDIT_2);
}

void UICommandSuggestion::setUpsuggestionSearch(){
	_suggestionSearch.push_back(SUGGESTION_SEARCH_1);
	_suggestionSearch.push_back(SUGGESTION_SEARCH_2);
}

void UICommandSuggestion::setUpsuggestionShow(){
	_suggestionShow.push_back(SUGGESTION_SHOW_1);
	_suggestionShow.push_back(SUGGESTION_SHOW_2);
	_suggestionShow.push_back(SUGGESTION_SHOW_3);
}


UICommandSuggestion::ComdType UICommandSuggestion::getComdType (std::string comdInString){
	UICommandSuggestion::ComdType typeOfComd;

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


std::vector<std::string>  UICommandSuggestion::getSuggestionAdd(){
	return _suggestionAdd;
}

std::vector<std::string>  UICommandSuggestion::getSuggestionDelete(){
	return _suggestionDelete;
}

std::vector<std::string>  UICommandSuggestion::getSuggestionEdit(){
	return _suggestionEdit;
}

std::vector<std::string>  UICommandSuggestion::getSuggestionSearch(){
	return _suggestionSearch;
}

std::vector<std::string>  UICommandSuggestion::getSuggestionShow(){
	return _suggestionShow;
}








