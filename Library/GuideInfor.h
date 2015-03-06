#pragma once

#ifndef GUIDEINFOR_H
#define GUIDEINFOR_H

#include <iostream>
#include <string>

class GuideInfor
{
public:
	GuideInfor(void);
	~GuideInfor(void);

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
	
	//Information to display for help guide
	static const int NUM_ADD = 10;
	static const int NUM_DELETE = 6;
	static const int NUM_EDIT = 6;
	static const int NUM_SEARCH = 8;
	static const int NUM_SHOW = 7;

	static const std::string HELP_GUIDE_INTRO;
	static const std::string HELP_GUIDE_ADD [NUM_ADD];
	static const std::string HELP_GUIDE_DELETE [NUM_DELETE];
	static const std::string HELP_GUIDE_EDIT [NUM_EDIT];
	static const std::string HELP_GUIDE_SEARCH [NUM_SEARCH];
	static const std::string HELP_GUIDE_SHOW [NUM_SHOW];
	static const std::string HELP_GUIDE_UNDO;
	static const std::string HELP_GUIDE_REDO;
	static const std::string HELP_GUIDE_EXIT;
	static const std::string HELP_GUIDE_HELP;


	//Information to display for suggestBar
	static const int NUM_SUGGESTION_ADD = 3;
	static const int NUM_SUGGESTION_DELETE = 2;
	static const int NUM_SUGGESTION_EDIT = 2;
	static const int NUM_SUGGESTION_SEARCH = 2;
	static const int NUM_SUGGESTION_SHOW = 3;

	static const std::string SUGGESTION_ADD[NUM_SUGGESTION_ADD];
	static const std::string SUGGESTION_DELETE[NUM_SUGGESTION_DELETE];
	static const std::string SUGGESTION_EDIT[NUM_SUGGESTION_EDIT];
	static const std::string SUGGESTION_SEARCH[NUM_SUGGESTION_SEARCH];
	static const std::string SUGGESTION_SHOW[NUM_SUGGESTION_SHOW];








	//Getters
	std::string getCommandAdd();
	std::string getCommandDelete();
	std::string getCommandEdit();
	std::string getCommandSearch();
	std::string getCommandShow();
	std::string getCommandUndo();
	std::string getCommandRedo();
	std::string getCommandExit();
	std::string getCommandHelp();

	std::string getHelpIntro();
	std::string getHelpAdd();
	std::string getHelpDelete();
	std::string getHelpEdit();
	std::string getHelpSearch();
	std::string getHelpShow();
	std::string getHelpUndo();
	std::string getHelpRedo();
	std::string getHelpExit();
	std::string getHelpHelp();

	std::string getSuggestionAdd(int);
	std::string getSuggestionDelete(int);
	std::string getSuggestionEdit(int);
	std::string getSuggestionSearch(int);
	std::string getSuggestionShow(int);

	const int getSuggestionAddArrarySize();
	const int getSuggestionDeleteArrarySize();
	const int getSuggestionEditArrarySize();
	const int getSuggestionSearchArrarySize();
	const int getSuggestionShowArrarySize();


	//Function

	//To convert all inputs into lowercase
	std::string lowerCase(std::string);
};
#endif

