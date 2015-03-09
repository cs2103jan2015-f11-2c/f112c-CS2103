#pragma once

#ifndef PARSERPROCESSOR_H
#define PARSERPROCESSOR_H

#include <string>
#include <vector>
#include "Event.h"
#include "Conversion.h"

class ParserProcessor {
private:
	static const int NUMBER_OF_KEYWORDS_MONTHS = 12;
	static const int NUMBER_OF_KEYWORDS_TIME = 2;
	static const int NUMBER_OF_KEYWORDS_DETAILS = 4;

	std::string keywordMonths[NUMBER_OF_KEYWORDS_MONTHS];
	std::string keywordTime[NUMBER_OF_KEYWORDS_TIME];
	std::string keywordDetails[NUMBER_OF_KEYWORDS_DETAILS];

public:
	ParserProcessor();

	Event processAddEvent(std::vector<std::string>);
	Event processEditEvent(std::vector<std::string>);
};

#endif