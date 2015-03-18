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
	static const std::string LOCKUP_USED_INFORMATION;

	std::string keywordMonths[NUMBER_OF_KEYWORDS_MONTHS];
	std::string keywordTime[NUMBER_OF_KEYWORDS_TIME];
	
	//boolean variables for Add and Edit command
	bool matchFound;
	bool startDayFound;
	bool endDayFound;
	bool startTimeFound;
	bool endTimeFound;
	bool afterTwelve;
	bool nameFound;

	//boolean variables for Show command
	//to check if Show is a range of days 
	bool oneMatchFound;
	bool twoMatchFound;
	//to identify what type of Show 
	bool systemShowDay;
	bool systemShowWeek;
	bool systemShowMonth;
	bool userShowDay;
	bool userShowRangeOfDays;
	bool userShowMonth;
	bool userShowRangeOfMonths;

	Event tempEventStore;
	struct tm* now;

	std::vector<std::string> fragmentedWords;

public:
	ParserProcessor();

	Event processAddEvent(std::vector<std::string>);
	Event processEditEvent(std::vector<std::string>);
	bool identifyEventName(int);
	//bool identifyAtDue(std::vector<std::string>, int);
	bool identifyDate(int);
	bool identifyTime(int);
	void addEventCorrector();
	void editEventCorrector();
	void eventMktimeCorrector();

	Event processShowEvent(std::vector<std::string>);
};

#endif