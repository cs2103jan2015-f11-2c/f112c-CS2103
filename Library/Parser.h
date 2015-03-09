#pragma once

#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Event.h"
//#include "InputStringSplit.h"
//#include "ParserProcessor.h"

class Parser
{
public:
	//constructor, destructor
	Parser(std::string);
	~Parser(void);

	enum commandType {
		ADDFLOAT, 
		ADDFULLDAY, 
		ADD, 
		ADDSTART, 
		ADDMULFULLDAYS, 
		ADDMULDAYS, 
		DELETE_, 
		EDIT, 
		SHOWDAY, 
		SHOWMTH, 
		SHOWYR, 
		SHOWUSER, 
		ERROR_
	};

private:
	commandType typeOfCommand;
	//InputStringSplit splitter;
	//ParserProcessor processor;
	std::string command;
	std::string details;
	std::string original;
	Event tempEventStore;
	int index;
	std::vector<std::string> categories;

public:
	//getters
	commandType getCommandType();
	std::string getCommand();
	std::string getDetails();
	std::string getOriginal();
	Event getEvent();
	int getIndex();

	//main methods
	void tokenizeOriginalString();	//identify first command and call corresponding function to further identify
	void retrieveCategories();	//retrieve all categories created from storage txt file 

	//add
	void identifyAddCommand();	//identify which add command to use and arrange the added information into an Event format
	int mthToInt(std::string);  //converts month from string to int
	void timeToInt(int&, int&, std::string);	//converts time from string to integers
	bool extractEventName();	//extract name of event from details string
	bool extractEventDate();	//extract date of event from details string
	bool extractEventTime();	//extract time of event from details string

	//delete
	void setDeleteCommand();	//set index and cType for delete
	
	//edit
	void setEditCommand();	//set index and cType for edit and calls identifyDetailToEdit
	void identifyDetailToEdit();	//identify what detail is being edited and insert information to edit into Event format

	//show
	void identifyShowCommand();	//determine what show cType it is based on system categories or user categories. Perform check for user categories if it exists
};		
#endif


