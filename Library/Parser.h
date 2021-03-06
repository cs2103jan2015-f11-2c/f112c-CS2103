//@author A0111379H

#pragma once

#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Event.h"
#include "InputStringSplit.h"
#include "ParserProcessor.h"
#include "ParserLog.h"

class Parser
{
public:
	//constructor, destructor
	Parser(std::string);
	~Parser(void);

	enum CommandType {
		ADDFLOAT, 
		ADD, 
		DELETE_, 
		EDIT,
		ERROR_,
		SEARCH,
		SHOW,
		SHOWFLOAT,
		SHOWALL,
		SHOWIMPORTANT,
		SHOWALLIMPORTANT,
		SHOWCOMPLETE,
		SHOWWEEK,
		SHOWMONTH,
		UNDO,
		REDO,
		COMPLETE,
		UNCOMPLETE
	};

	static const std::string TOKENISE_ORIGINAL_STRING;

private:
	ParserLog logger;
	InputStringSplit splitter;
	ParserProcessor processor;

	Parser::CommandType typeOfCommand;
	std::string command;
	std::string details;
	std::string original;
	Event tempEventStore;
	std::string nameOfEvent;

	static const int NUMBER_OF_KEYWORDS_COMMANDS = 13;
	std::string keywordCommands[NUMBER_OF_KEYWORDS_COMMANDS];

public:
	//getters
	Parser::CommandType getCommandType();
	std::string getCommand();
	std::string getDetails();
	std::string getOriginal();
	Event getEvent();
	std::string getNameOfEvent();

	//main methods
	void processInput();
	void tokenizeOriginalString();
	void determineCommandType();
	void determineAddCommand();
	void determineDelCommand();
	void determineEditCommand();
	void determineShowCommand();
	void determineCompleteCommand();
	void determineUncompleteCommand();
	void determineOtherCommand();
	bool checkCommandExist();
	bool checkCommandUndoRedo();
	std::string createFeedback(std::string);
};		

#endif