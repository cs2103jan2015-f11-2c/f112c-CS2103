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
	UIHelp(void);
	~UIHelp(void);

private:
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

public:
	//public getter

	//Return a short introduction/teaching guide to caller
	std::vector<LogicUpdater::EVENT_STRING> getHelpIntroduction();
	
	//Return a list of commands to caller
	std::vector<LogicUpdater::EVENT_STRING> getHelpCommands();

	//Return a list of shortcuts to caller
	std::vector<LogicUpdater::EVENT_STRING> getHelpShortcuts();
	
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

};

#endif

