//@author A0111230J
/**
 * This class is used to store and retrieve information to suggest to the user.
 * It supports a total of 5 commands (add,delete,edit,search,show).
 * A command in std::string form is passed in through function getCommandType() and the corresponding ComdType will be returned to the caller.
 * [WARNING - command passed in must be in small caps]
 * Caller can make use of the returned ComdType to call the respective getters ( getSuggestionAdd(),getSuggestionDelete(),getSuggestionEdit(),
 * getSuggestionSearch() or getSuggestionShow() ) to receive object of std::vector<std::string> which contains the respective suggestion information.
 * In the case where ComdType is UNDISPLAY_ or INVALID, caller can choose to execute otherwise.
 */

#pragma once

#ifndef UICOMMANDSUGGESTION_H_
#define UICOMMANDSUGGESTION_H_

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

class UICommandSuggestion
{
public:

	//Constructors & destructors
	UICommandSuggestion(void);
	~UICommandSuggestion(void);

	//Enumeration of the various types of commands that will be used
	enum ComdType {
		ADD_,
		DELETE_,
		EDIT_,
		SEARCH_,
		SHOW_,
		UNDISPLAY_,
		INVALID_
	};

//===================================================================================================================================================================

	static const int MIN_ACTION_INDEX = 0;
	static const int MAX_ACTION_INDEX = 2;

	std::vector<std::string> _keywordCommands;
	std::vector<std::string> _keywordMonths;
	std::vector<std::string> _keywordTime;
	std::vector<std::string> _keywordDay;
	std::vector<std::string> _keywordOthers;

/*
* =================================================================================================================================================================== 
* Static variables which contain the respective commands
* ===================================================================================================================================================================
*/
	static const std::string COMMAND_ADD;
	static const std::string COMMAND_DELETE;
	static const std::string COMMAND_EDIT;
	static const std::string COMMAND_SEARCH;
	static const std::string COMMAND_SHOW;

	static const std::string COMMAND_AD;
	static const std::string COMMAND_DELET;
	static const std::string COMMAND_EDI;
	static const std::string COMMAND_SEARC;
	static const std::string COMMAND_SHO;

	static const std::string BLANK_SPACE;
	static const std::string LEAVE_A_LINE;
	static const std::string DASH;
	static const std::string SEMI_COLON;
	static const std::string WORD_DUE;

	static const std::string SYMBOL_EVENT;
	static const std::string SYMBOL_INDEX_OF_EVENT;
	static const std::string SYMBOL_DATE;
	static const std::string SYMBOL_NEW_DATE;
	static const std::string SYMBOL_START_DATE;
	static const std::string SYMBOL_END_DATE;
	static const std::string SYMBOL_START_TIME;
	static const std::string SYMBOL_END_TIME;
	static const std::string SYMBOL_NEW_EVENT;
	static const std::string SYMBOL_NEW_START_TIME;
	static const std::string SYMBOL_NEW_END_TIME;


//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Static variables which contain the respective suggestion information for each command
* ===================================================================================================================================================================
*/

//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Private attributes to house the combined information in std::vector form for each command
* Private methods that are used to construct/set up the respective std::vector of combined information
* ===================================================================================================================================================================
*/
private: 
	std::vector<std::string> _suggestionAdd;
	std::vector<std::string> _suggestionDelete;
	std::vector<std::string> _suggestionEdit;
	std::vector<std::string> _suggestionSearch;
	std::vector<std::string> _suggestionShow;

	std::vector<std::string> _userActions;
	int _userActionsIndex;

	void setUpsuggestionAdd();
	void setUpsuggestionDelete();
	void setUpsuggestionEdit();
	void setUpsuggestionSearch();
	void setUpsuggestionShow();
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Public methods and their respective APIs
* ===================================================================================================================================================================
*/	
public:
	//Pre-condition : std::string passed in to be in lowercase
	//This function takes in a std::string and return the respective command type 
	//E.g. It takes in "add" and return ComdType::ADD_
	//E.g. For an invalid std::string "hello", it will return ComdType::INVALID_
	ComdType getComdType (std::string);

	//Pre-condition : Recommend uses function getComdType to determine the ComdType and ensure match with this function 
	//This function returns a std::vector<std::string> object> which contain the command suggestion related to command add
	std::vector<std::string> getSuggestionAdd();

	//Pre-condition : Recommend uses function getComdType to determine the ComdType and ensure match with this function 
	//This function returns a std::vector<std::string> object> which contain the command suggestion related to command delete
	std::vector<std::string> getSuggestionDelete();

	//Pre-condition : Recommend uses function getComdType to determine the ComdType and ensure match with this function 
	//This function returns a std::vector<std::string> object> which contain the command suggestion related to command edit
	std::vector<std::string> getSuggestionEdit();

	//Pre-condition : Recommend uses function getComdType to determine the ComdType and ensure match with this function 
	//This function returns a std::vector<std::string> object> which contain the command suggestion related to command search
	std::vector<std::string> getSuggestionSearch();

	//Pre-condition : Recommend uses function getComdType to determine the ComdType and ensure match with this function 
	//This function returns a std::vector<std::string> object> which contain the command suggestion related to command show
	std::vector<std::string> getSuggestionShow();

	void setUserActions(std::string);

	std::vector<std::string> getUserActions();

	void initializeUserActionsIndex();

	void setUserActionsIndex(int);

	//Pre-condition: call function setUserActionsIndex() to update _userActionsIndex
	int getUserActionsIndex();

	std::string getSpecificUserAction();

//===================================================================================================================================================================

	void setKeywordCommands();
	void setKeywordMonths();
	void setKeywordTime();
	void setKeywordDay();
	void setKeywordOthers();

	std::vector<std::string> tokenizeString(std::string);

	std::vector<std::string> getKeyWordCommandsVect();
	std::vector<std::string> getKeyWordMonthsVect();
	std::vector<std::string> getKeyWordTimeVect();
	std::vector<std::string> getKeyWordDayVect();
	std::vector<std::string> getkeywordOthersVect();


};
#endif