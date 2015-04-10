#include "UICommandSuggestion.h"


UICommandSuggestion::UICommandSuggestion(void)
{
	setUpsuggestionAdd();
	setUpsuggestionDelete();
	setUpsuggestionEdit();
	setUpsuggestionSearch();
	setUpsuggestionShow();

	initializeUserActionsIndex();
}


UICommandSuggestion::~UICommandSuggestion(void)
{
}



// static strings that cannot initialise in "UICommandSuggestion.h"
const std::string UICommandSuggestion::COMMAND_ADD = "add";
const std::string UICommandSuggestion::COMMAND_DELETE = "del";
const std::string UICommandSuggestion::COMMAND_EDIT = "edit";
const std::string UICommandSuggestion::COMMAND_SEARCH = "search";
const std::string UICommandSuggestion::COMMAND_SHOW = "show";

const std::string UICommandSuggestion::COMMAND_AD = "ad";
const std::string UICommandSuggestion::COMMAND_DELET = "de";
const std::string UICommandSuggestion::COMMAND_EDI = "edi";
const std::string UICommandSuggestion::COMMAND_SEARC = "searc";
const std::string UICommandSuggestion::COMMAND_SHO = "sho";

const std::string UICommandSuggestion::SUGGESTION_ADD_1 = " add Exercise daily; (Ongoing event)";
const std::string UICommandSuggestion::SUGGESTION_ADD_2 = " add Overseas trip; 17apr 9.30pm - 19apr 11.45pm (Normal event)";
const std::string UICommandSuggestion::SUGGESTION_ADD_3 = " add Project final report; due 3may 9am (Event with deadline)";
const std::string UICommandSuggestion::SUGGESTION_ADD_4 = " add Final exam; !!! 5may 10-11.15am (Event with importance)";

const std::string UICommandSuggestion::SUGGESTION_DELETE_1 = " del 2";
const std::string UICommandSuggestion::SUGGESTION_DELETE_2 =  " del Study;";

const std::string UICommandSuggestion::SUGGESTION_EDIT_1 = " edit Lecture quiz; Final exam; (change name only) ";
const std::string UICommandSuggestion::SUGGESTION_EDIT_2 =  " edit Lecture quiz; 9am-10am (change time only)" ;
const std::string UICommandSuggestion::SUGGESTION_EDIT_3 =  " edit Lecture quiz; 22may (change date only)" ;
const std::string UICommandSuggestion::SUGGESTION_EDIT_4 =  " edit Lecture quiz; Final exam; 22may 9am-10am (multiple changes)" ;


const std::string UICommandSuggestion::SUGGESTION_SEARCH_1 = " search CS2103 exam";
const std::string UICommandSuggestion::SUGGESTION_SEARCH_2 = " search 10feb";

const std::string UICommandSuggestion::SUGGESTION_SHOW_1 = " show apr-may";
const std::string UICommandSuggestion::SUGGESTION_SHOW_2 = " show 10apr-3may";
const std::string UICommandSuggestion::SUGGESTION_SHOW_3 = " show tues-fri";


void UICommandSuggestion::setUpsuggestionAdd(){
	_suggestionAdd.push_back(SUGGESTION_ADD_1);
	_suggestionAdd.push_back(SUGGESTION_ADD_2);
	_suggestionAdd.push_back(SUGGESTION_ADD_3);
	_suggestionAdd.push_back(SUGGESTION_ADD_4);
}

void UICommandSuggestion::setUpsuggestionDelete(){
	_suggestionDelete.push_back(SUGGESTION_DELETE_1);
	_suggestionDelete.push_back(SUGGESTION_DELETE_2);

}
void UICommandSuggestion::setUpsuggestionEdit(){
	_suggestionEdit.push_back(SUGGESTION_EDIT_1);
	_suggestionEdit.push_back(SUGGESTION_EDIT_2);
	_suggestionEdit.push_back(SUGGESTION_EDIT_3);
	_suggestionEdit.push_back(SUGGESTION_EDIT_4);
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

void UICommandSuggestion::setUserActions(std::string latestUserAction){
	_userActions.push_back(latestUserAction);

	if (_userActions.size()>3){
		_userActions.erase(_userActions.begin());
	}

	assert(_userActions.size() <= 3);

	_userActionsIndex = _userActions.size() -1 ;
}

std::vector<std::string> UICommandSuggestion::getUserActions(){
	return _userActions;
}

void UICommandSuggestion::initializeUserActionsIndex(){
	_userActionsIndex = MIN_ACTION_INDEX - 1;
}

//numToShift 1 or -1
void UICommandSuggestion::setUserActionsIndex(int numToShift){
	assert(numToShift == 1 || numToShift == -1);

	if (numToShift == 1 && _userActionsIndex < MAX_ACTION_INDEX){
		_userActionsIndex += numToShift;
	}

	if (numToShift == -1 && _userActionsIndex > MIN_ACTION_INDEX){
		_userActionsIndex += numToShift;
	}

	if (_userActionsIndex >= _userActions.size()){
		_userActionsIndex -= 1;
	}

	if (_userActionsIndex < -1){
		_userActionsIndex += 1;
	}

	assert(_userActionsIndex>=-1 && _userActionsIndex<=2);
}

int UICommandSuggestion::getUserActionsIndex(){
	return _userActionsIndex;
}

std::string UICommandSuggestion::getSpecificUserAction(){
	if(!_userActions.empty()){
		return _userActions[_userActionsIndex];
	}else {
		return "";
	}
}




