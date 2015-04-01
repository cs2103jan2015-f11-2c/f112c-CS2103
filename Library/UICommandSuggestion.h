#pragma once

#ifndef UICOMMANDSUGGESTION_H_
#define UICOMMANDSUGGESTION_H_

#include <iostream>
#include <string>
#include <vector>

class UICommandSuggestion
{
public:
	UICommandSuggestion(void);
	~UICommandSuggestion(void);

	enum ComdType {
		ADD_,
		DELETE_,
		EDIT_,
		SEARCH_,
		SHOW_,
		UNDISPLAY_,
		INVALID_
	};

	//Commands
	static const std::string COMMAND_ADD;
	static const std::string COMMAND_DELETE;
	static const std::string COMMAND_EDIT;
	static const std::string COMMAND_SEARCH;
	static const std::string COMMAND_SHOW;
	static const std::string COMMAND_UNDO;
	static const std::string COMMAND_REDO;
	static const std::string COMMAND_EXIT;
	static const std::string COMMAND_HELP;

	static const std::string COMMAND_AD;
	static const std::string COMMAND_DELET;
	static const std::string COMMAND_EDI;
	static const std::string COMMAND_SEARC;
	static const std::string COMMAND_SHO;

	static const std::string SUGGESTION_ADD_1;
	static const std::string SUGGESTION_ADD_2;
	static const std::string SUGGESTION_ADD_3;

	static const std::string SUGGESTION_DELETE_1;
	static const std::string SUGGESTION_DELETE_2;

	static const std::string SUGGESTION_EDIT_1;
	static const std::string SUGGESTION_EDIT_2;

	static const std::string SUGGESTION_SEARCH_1;
	static const std::string SUGGESTION_SEARCH_2;

	static const std::string SUGGESTION_SHOW_1;
	static const std::string SUGGESTION_SHOW_2;
	static const std::string SUGGESTION_SHOW_3;

	
private: 
	std::vector<std::string> _suggestionAdd;
	std::vector<std::string> _suggestionDelete;
	std::vector<std::string> _suggestionEdit;
	std::vector<std::string> _suggestionSearch;
	std::vector<std::string> _suggestionShow;

	void setUpsuggestionAdd();
	void setUpsuggestionDelete();
	void setUpsuggestionEdit();
	void setUpsuggestionSearch();
	void setUpsuggestionShow();

public:
	//functions
	ComdType getComdType (std::string);

	std::vector<std::string> getSuggestionAdd();
	std::vector<std::string> getSuggestionDelete();
	std::vector<std::string> getSuggestionEdit();
	std::vector<std::string> getSuggestionSearch();
	std::vector<std::string> getSuggestionShow();
};
#endif