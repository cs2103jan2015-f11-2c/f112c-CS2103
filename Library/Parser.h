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

class Parser
{
public:
	//constructor, destructor
	Parser(std::string);
	~Parser(void);

	enum commandType {
		ADDFLOAT, 
		ADD, 
		DELETE_, 
		EDIT, 
		SHOW
	};

private:
	Parser::commandType typeOfCommand;
	InputStringSplit splitter;
	ParserProcessor processor;
	std::string command;
	std::string details;
	std::string original;
	Event tempEventStore;
	std::string nameOfEvent;
	std::vector<std::string> categories;

public:
	//getters
	Parser::commandType getCommandType();
	std::string getCommand();
	std::string getDetails();
	std::string getOriginal();
	Event getEvent();
	std::string getNameOfEvent();

	//main methods
	void tokenizeOriginalString();	//identify first command and call corresponding function to further identify
	void retrieveCategories();	//retrieve all categories created from storage txt file 

	//show
	void identifyShowCommand();	//determine what show cType it is based on system categories or user categories. Perform check for user categories if it exists
};		

#endif