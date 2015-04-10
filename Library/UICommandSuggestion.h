/**
 * This class is used to store and retrieve information to suggest to the user.
 * It supports a total of 5 commands (add,delete,edit,search,show).
 * A command in std::string form is passed in through function getCommandType() and the corresponding ComdType will be returned to the caller.
 * [WARNING - command passed in must be in small caps]
 * Caller can make use of the returned ComdType to call the respective getters ( getSuggestionAdd(),getSuggestionDelete(),getSuggestionEdit(),
 * getSuggestionSearch() or getSuggestionShow() ) to receive object of std::vector<std::string> which contains the respective suggestion information.
 * In the case where ComdType is UNDISPLAY_ or INVALID, caller can choose to execute otherwise.

 * @author A0111230J
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

	static const int MIN_ACTION_INDEX = 0;
	static const int MAX_ACTION_INDEX = 2;



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
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Static variables which contain the respective suggestion information for each command
* ===================================================================================================================================================================
*/
	static const std::string SUGGESTION_ADD_1;
	static const std::string SUGGESTION_ADD_2;
	static const std::string SUGGESTION_ADD_3;
	static const std::string SUGGESTION_ADD_4;

	static const std::string SUGGESTION_DELETE_1;
	static const std::string SUGGESTION_DELETE_2;

	static const std::string SUGGESTION_EDIT_1;
	static const std::string SUGGESTION_EDIT_2;
	static const std::string SUGGESTION_EDIT_3;
	static const std::string SUGGESTION_EDIT_4;

	static const std::string SUGGESTION_SEARCH_1;
	static const std::string SUGGESTION_SEARCH_2;

	static const std::string SUGGESTION_SHOW_1;
	static const std::string SUGGESTION_SHOW_2;
	static const std::string SUGGESTION_SHOW_3;
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

};
#endif