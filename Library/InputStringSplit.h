#pragma once

#ifndef INPUTSTRINGSPLIT_H
#define INPUTSTRINGSPLIT_H

#include <string>
#include <vector>
#include <iostream>

class InputStringSplit {
private: 
	
public:
	InputStringSplit();

	std::string extractFirstWord(std::string);
	std::string extractDetails(std::string);
	std::string extractEventName(std::string);
	std::string removeEditEventName(std::string, std::string);
	std::string extractEditEventName(std::string);
	std::vector<std::string> fragmentAddString(std::string);
	std::vector<std::string> fragmentEditString(std::string);
	std::vector<std::string> fragmentShowString(std::string);
};

#endif