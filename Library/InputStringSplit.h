//@author A0111379H

#pragma once

#ifndef INPUTSTRINGSPLIT_H
#define INPUTSTRINGSPLIT_H

#include <string>
#include <vector>
#include <iostream>
#include <assert.h>
#include <cctype>
#include "ParserExceptions.h"
#include "ParserLog.h"

class InputStringSplit {
private: 
	ParserLog logger;
	
public:
	static const std::string EXTRACT_FIRST_WORD;
	static const std::string EXTRACT_DETAILS;
	static const std::string EXTRACT_DEL_DONE_EVENT_NAME;
	static const std::string EXTRACT_EDIT_EVENT_NAME;
	static const std::string REMOVE_EDIT_EVENT_NAME;
	static const std::string FRAGMENT_STRING;
	static const std::string FRAGMENT_SHOW_STRING;

	static const std::string CONVERT_NORMAL_TO_FLOAT;
	static const int SECOND_INSTANCE = 2;

	InputStringSplit();

	std::string extractFirstWord(std::string);
	std::string extractDetails(std::string);
	std::string extractEditEventName(std::string);
	std::string removeEditEventName(std::string, std::string);
	std::vector<std::string> fragmentString(std::string);
	//std::vector<std::string> fragmentShowString(std::string);
};

#endif