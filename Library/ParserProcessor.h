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

	std::string keywordMonths[NUMBER_OF_KEYWORDS_MONTHS];
	std::string keywordTime[NUMBER_OF_KEYWORDS_TIME];

public:
	ParserProcessor();

	Event processEvent(std::vector<std::string>);
	int extractEventIndex(std::string);
	Event extractEventName(std::vector<std::string>);
};

#endif