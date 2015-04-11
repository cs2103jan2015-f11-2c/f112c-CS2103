//@author A0111230J
/**
 * This class is used to store and retrieve information related to help and commands to suggest to the user.
 * It has a total of 3 public methods ( getHelpIntroduction(), getHelpCommands(), getHelpShortcuts() ) for caller to get the respective 
 * information in std::vector<LogicUpdater::EVENT_STRING> form.
 * No pre-condition is needed to use this class and no imformation is needed to be passed into any of the public methods.
 */

#pragma once

#ifndef UIHELP_H
#define UIHELP_H

#include <iostream>
#include <string>
#include <assert.h>
#include "LogicUpdater.h"

class UIHelp
{
public:

	//Constructors & destructors
	UIHelp(void);
	~UIHelp(void);

/*
* =================================================================================================================================================================== 
* Static variables (integers) which contain the sizes of the arrays which contain the help information
* Static variables (std::string arrays) which contain the help information
* ===================================================================================================================================================================
*/
	static const int NUM_ADD = 10;
	static const int NUM_DELETE = 6;
	static const int NUM_EDIT = 6;
	static const int NUM_DONE = 4;
	static const int NUM_SEARCH = 8;
	static const int NUM_SHOW = 7;
	static const int NUM_COMMANDS = 15;
	static const int NUM_SHORTCUTS = 10;
	
	static const std::string HELP_GUIDE_WELCOME_MESSAGE;
	static const std::string HELP_GUIDE_ADD [NUM_ADD];
	static const std::string HELP_GUIDE_DELETE [NUM_DELETE];
	static const std::string HELP_GUIDE_EDIT [NUM_EDIT];
	static const std::string HELP_GUIDE_DONE [NUM_DONE];
	static const std::string HELP_GUIDE_SEARCH [NUM_SEARCH];
	static const std::string HELP_GUIDE_SHOW [NUM_SHOW];
	static const std::string HELP_GUIDE_UNDO;
	static const std::string HELP_GUIDE_REDO;
	static const std::string HELP_GUIDE_EXIT;
	static const std::string HELP_GUIDE_COMMANDS [NUM_COMMANDS];
	static const std::string HELP_GUIDE_SHORTCUTS [NUM_SHORTCUTS];
//===================================================================================================================================================================


/*
* =================================================================================================================================================================== 
* Functions that convert the respective help information from its storage form(array) into std::string form
* Function convertToEventString() further convert the respective std::string into EVENT_STRING form 
* ===================================================================================================================================================================
*/
private:
	std::string getHelpWelcomeMessage();
	std::string getHelpAdd();
	std::string getHelpDelete();
	std::string getHelpEdit();
	std::string getHelpDone();
	std::string getHelpSearch();
	std::string getHelpShow();
	std::string getHelpUndo();
	std::string getHelpRedo();
	std::string getHelpExit();

	LogicUpdater::EVENT_STRING convertToEventString(std::string);
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Public attributes and their respective APIs
* ===================================================================================================================================================================
*/
public:

	//Pre-condition : None
	//Return a short introduction/teaching guide about the usage of MapleSyrup in std::vector<LogicUpdater::EVENT_STRING> to caller
	std::vector<LogicUpdater::EVENT_STRING> getHelpIntroduction();
	
	//Pre-condition : None
	//Return a list of commands and their description supported in MapleSyrup in std::vector<LogicUpdater::EVENT_STRING> to caller
	std::vector<LogicUpdater::EVENT_STRING> getHelpCommands();

	//Pre-condition : None
	//Return a list of shortcuts and their description supported in MapleSyrup in std::vector<LogicUpdater::EVENT_STRING> to caller
	std::vector<LogicUpdater::EVENT_STRING> getHelpShortcuts();
//===================================================================================================================================================================

};

#endif

