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
	static const std::string FRAGMENT_ADD_STRING;
	static const std::string FRAGMENT_EDIT_STRING;
	static const std::string FRAGMENT_SHOW_STRING;

	static const std::string CONVERT_NORMAL_TO_FLOAT;

	InputStringSplit();

	std::string extractFirstWord(std::string);
	std::string extractDetails(std::string);
	//std::string extractDelDoneEventName(std::string);
	std::string extractEditEventName(std::string);
	std::string removeEditEventName(std::string, std::string);
	std::vector<std::string> fragmentAddString(std::string);
	std::vector<std::string> fragmentEditString(std::string);
	std::vector<std::string> fragmentShowString(std::string);
};

#endif