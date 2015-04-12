//@author A0111230J

#include "UICommandSuggestion.h"


UICommandSuggestion::UICommandSuggestion(void)
{
	setUpsuggestionAdd();
	setUpsuggestionDelete();
	setUpsuggestionEdit();
	setUpsuggestionSearch();
	setUpsuggestionShow();

	setKeywordCommands();
	setKeywordDay();
	setKeywordMonths();
	setKeywordTime();
	setKeywordOthers();

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

const std::string UICommandSuggestion::BLANK_SPACE = " ";
const std::string UICommandSuggestion::LEAVE_A_LINE = "\n";
const std::string UICommandSuggestion::DASH = "-";
const std::string UICommandSuggestion::SEMI_COLON = ";";
const std::string UICommandSuggestion::WORD_DUE = "due";

const std::string UICommandSuggestion::SYMBOL_EVENT = "[Event]";
const std::string UICommandSuggestion::SYMBOL_INDEX_OF_EVENT = "[Index of Event]";
const std::string UICommandSuggestion::SYMBOL_DATE = "[Date]";
const std::string UICommandSuggestion::SYMBOL_NEW_DATE = "[New date]";
const std::string UICommandSuggestion::SYMBOL_START_DATE = "[Start date]";
const std::string UICommandSuggestion::SYMBOL_END_DATE = "[End date]";
const std::string UICommandSuggestion::SYMBOL_START_TIME = "[Start time]";
const std::string UICommandSuggestion::SYMBOL_END_TIME = "[End time]";
const std::string UICommandSuggestion::SYMBOL_NEW_EVENT = "[New Event]";
const std::string UICommandSuggestion::SYMBOL_NEW_START_TIME = "[New start time]";
const std::string UICommandSuggestion::SYMBOL_NEW_END_TIME = "[New end time]";



void UICommandSuggestion::setUpsuggestionAdd(){
	_suggestionAdd.push_back(COMMAND_ADD);
	_suggestionAdd.push_back(BLANK_SPACE + SYMBOL_EVENT + LEAVE_A_LINE);

	_suggestionAdd.push_back(COMMAND_ADD);
	_suggestionAdd.push_back(BLANK_SPACE + SYMBOL_EVENT + BLANK_SPACE + SYMBOL_START_TIME + BLANK_SPACE);
	_suggestionAdd.push_back(DASH);
	_suggestionAdd.push_back(BLANK_SPACE + SYMBOL_END_TIME + LEAVE_A_LINE);

	_suggestionAdd.push_back(COMMAND_ADD);
	_suggestionAdd.push_back(BLANK_SPACE + SYMBOL_EVENT + BLANK_SPACE);
	_suggestionAdd.push_back(WORD_DUE);
	_suggestionAdd.push_back(BLANK_SPACE + SYMBOL_DATE + BLANK_SPACE + SYMBOL_END_TIME);


}

void UICommandSuggestion::setUpsuggestionDelete(){
	_suggestionDelete.push_back(COMMAND_DELETE);
	_suggestionDelete.push_back(BLANK_SPACE + SYMBOL_EVENT + LEAVE_A_LINE);

	_suggestionDelete.push_back(COMMAND_DELETE);
	_suggestionDelete.push_back(BLANK_SPACE + SYMBOL_INDEX_OF_EVENT);

}
void UICommandSuggestion::setUpsuggestionEdit(){
	_suggestionEdit.push_back(COMMAND_EDIT);
	_suggestionEdit.push_back(BLANK_SPACE + SYMBOL_EVENT + BLANK_SPACE);
	_suggestionEdit.push_back(SEMI_COLON);
	_suggestionEdit.push_back(BLANK_SPACE + SYMBOL_NEW_EVENT +LEAVE_A_LINE);

	_suggestionEdit.push_back(COMMAND_EDIT);
	_suggestionEdit.push_back(BLANK_SPACE + SYMBOL_EVENT + BLANK_SPACE);
	_suggestionEdit.push_back(SEMI_COLON);
	_suggestionEdit.push_back(BLANK_SPACE + SYMBOL_NEW_START_TIME + BLANK_SPACE);
	_suggestionEdit.push_back(DASH);
	_suggestionEdit.push_back(BLANK_SPACE + SYMBOL_NEW_END_TIME + LEAVE_A_LINE);

	_suggestionEdit.push_back(COMMAND_EDIT);
	_suggestionEdit.push_back(BLANK_SPACE + SYMBOL_INDEX_OF_EVENT + BLANK_SPACE);
	_suggestionEdit.push_back(SEMI_COLON);
	_suggestionEdit.push_back(BLANK_SPACE + SYMBOL_NEW_DATE);
}

void UICommandSuggestion::setUpsuggestionSearch(){
	_suggestionSearch.push_back(COMMAND_SEARCH);
	_suggestionSearch.push_back(BLANK_SPACE + SYMBOL_EVENT + LEAVE_A_LINE);

	_suggestionSearch.push_back(COMMAND_SEARCH);
	_suggestionSearch.push_back(BLANK_SPACE + SYMBOL_DATE);
}

void UICommandSuggestion::setUpsuggestionShow(){
	_suggestionShow.push_back(COMMAND_SHOW);
	_suggestionShow.push_back(BLANK_SPACE + SYMBOL_DATE + LEAVE_A_LINE);

	_suggestionShow.push_back(COMMAND_SHOW);
	_suggestionShow.push_back(BLANK_SPACE + SYMBOL_START_DATE + BLANK_SPACE);
	_suggestionShow.push_back(DASH);
	_suggestionShow.push_back(BLANK_SPACE + SYMBOL_END_DATE);
}


UICommandSuggestion::ComdType UICommandSuggestion::getComdType (std::string comdInString){
	UICommandSuggestion::ComdType typeOfComd;

	if(comdInString.size()>=COMMAND_ADD.size() &&  comdInString.substr(0,COMMAND_ADD.size())== COMMAND_ADD){
		typeOfComd = ADD_;
	} else if (comdInString.size()>=COMMAND_DELETE.size() &&  comdInString.substr(0,COMMAND_DELETE.size()) == COMMAND_DELETE){
		typeOfComd = DELETE_;
	} else if (comdInString.size()>=COMMAND_EDIT.size() &&  comdInString.substr(0,COMMAND_EDIT.size()) == COMMAND_EDIT){
		typeOfComd = EDIT_;
	} else if (comdInString.size()>=COMMAND_SEARCH.size() &&  comdInString.substr(0,COMMAND_SEARCH.size()) == COMMAND_SEARCH){
		typeOfComd = SEARCH_;
	} else if (comdInString.size()>=COMMAND_SHOW.size() &&  comdInString.substr(0,COMMAND_SHOW.size()) == COMMAND_SHOW){
		typeOfComd = SHOW_;
	} else if (comdInString == COMMAND_AD || comdInString == COMMAND_DELET || comdInString == COMMAND_EDI || comdInString == COMMAND_SEARC || comdInString == COMMAND_SHO || comdInString.empty()){
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

	_userActionsIndex = _userActions.size() - 1 ;
}


void UICommandSuggestion::initializeUserActionsIndex(){
	_userActionsIndex = MIN_ACTION_INDEX - 1;
}

//numToShift 1 or -1
void UICommandSuggestion::setUserActionsIndex(int numToShift){
	assert(numToShift == 1 || numToShift == -1);

	if (numToShift == 1 && _userActionsIndex < _userActions.size() - 1){
		_userActionsIndex += numToShift;
	}

	if (numToShift == -1 && _userActionsIndex > MIN_ACTION_INDEX){
		_userActionsIndex += numToShift;
	}

	assert(_userActionsIndex>=-1 && _userActionsIndex<=2);
}


std::string UICommandSuggestion::getSpecificUserAction(){
	if(!_userActions.empty()){
		return _userActions[_userActionsIndex];
	}else {
		return "";
	}
}

void UICommandSuggestion::upKeyPressed(){
	setUserActionsIndex(-1);
}

void UICommandSuggestion::downKeyPressed(){
	setUserActionsIndex(1);
}


void UICommandSuggestion::setKeywordCommands(){
	_keywordCommands.push_back ("add");
	_keywordCommands.push_back ("del");
	_keywordCommands.push_back ("delete");
	_keywordCommands.push_back ("edit");
	_keywordCommands.push_back ("show");
	_keywordCommands.push_back ("search");
	_keywordCommands.push_back ("undo");
	_keywordCommands.push_back ("redo");
	_keywordCommands.push_back ("done");
	_keywordCommands.push_back ("completed");
	_keywordCommands.push_back ("complete");
	_keywordCommands.push_back ("uncomplete");
	_keywordCommands.push_back ("undone");
	_keywordCommands.push_back ("back");
	_keywordCommands.push_back ("bk");
}

void UICommandSuggestion::setKeywordMonths(){	
	_keywordMonths.push_back ("jan");
	_keywordMonths.push_back ("january");
	_keywordMonths.push_back ("feb");
	_keywordMonths.push_back ("february");
	_keywordMonths.push_back ("mar");
	_keywordMonths.push_back ("march");
	_keywordMonths.push_back ("apr");
	_keywordMonths.push_back ("april");
	_keywordMonths.push_back ("may");
	_keywordMonths.push_back ("jun");
	_keywordMonths.push_back ( "june");
	_keywordMonths.push_back ( "jul");
	_keywordMonths.push_back ("july");
	_keywordMonths.push_back ("aug");
	_keywordMonths.push_back ("august");
	_keywordMonths.push_back ( "sep");
	_keywordMonths.push_back ("september");
	_keywordMonths.push_back ("oct");
	_keywordMonths.push_back ("october");
	_keywordMonths.push_back ("nov");
	_keywordMonths.push_back ("november");
	_keywordMonths.push_back ("dec");
	_keywordMonths.push_back ("december");
	_keywordMonths.push_back ("week");
	_keywordMonths.push_back ("wk");
	_keywordMonths.push_back ("month");
	_keywordMonths.push_back ("mth");
	_keywordMonths.push_back ("year");
	_keywordMonths.push_back ("yr");
}

void UICommandSuggestion::setKeywordTime(){
	_keywordTime.push_back ( "am");
	_keywordTime.push_back ("pm");
}

void UICommandSuggestion::setKeywordDay(){
	_keywordDay.push_back ("today");
	_keywordDay.push_back ("tdy");
	_keywordDay.push_back ("tomorrow");
	_keywordDay.push_back ("tmr");
	_keywordDay.push_back ("mon");
	_keywordDay.push_back ( "monday");
	_keywordDay.push_back ("tues");
	_keywordDay.push_back ( "tuesday");
	_keywordDay.push_back ("wed");
	_keywordDay.push_back ("wednesday");
	_keywordDay.push_back ("thurs");
	_keywordDay.push_back ("thursday");
	_keywordDay.push_back ("fri");
	_keywordDay.push_back ("friday");
	_keywordDay.push_back ("sat");
	_keywordDay.push_back ("saturday");
	_keywordDay.push_back ("sun");
	_keywordDay.push_back ("sunday");
}

void UICommandSuggestion::setKeywordOthers(){
	_keywordOthers.push_back ("to");
	_keywordOthers.push_back ("due");
	_keywordOthers.push_back ("by");	
	_keywordCommands.push_back ("next");
	_keywordOthers.push_back ("nxt");
	_keywordOthers.push_back ("all");
}

std::vector<std::string> UICommandSuggestion::tokenizeString(std::string input){
	std::vector<std::string> tokenVect;

	int start = 0;
	int end = 0;

	std::string token = "";

	for (int i=0; i<input.size();i++){
		if(input[i] != ' '){
			token += input[i];
		} else if(token != ""){
			tokenVect.push_back(token);
			token = "";
			tokenVect.push_back(" ");
		} else {
			tokenVect.push_back(" ");
		}

	}

	tokenVect.push_back(token);

	return tokenVect;
}

std::vector<std::string> UICommandSuggestion::getKeyWordCommandsVect(){
	return _keywordCommands;
}

std::vector<std::string> UICommandSuggestion::getKeyWordMonthsVect(){
	return _keywordMonths;
}

std::vector<std::string> UICommandSuggestion::getKeyWordTimeVect(){
	return _keywordTime;
}

std::vector<std::string> UICommandSuggestion::getKeyWordDayVect(){
	return _keywordDay;
}

std::vector<std::string> UICommandSuggestion::getkeywordOthersVect(){
	return _keywordOthers;
}