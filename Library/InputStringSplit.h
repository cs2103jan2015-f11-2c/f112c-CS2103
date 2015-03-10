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
	std::vector<std::string> fragmentAddString(std::string);
	std::vector<std::string> fragmentDeleteString(std::string);
	std::vector<std::string> fragmentEditString(std::string);
};

#endif