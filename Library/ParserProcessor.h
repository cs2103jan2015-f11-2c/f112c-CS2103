#pragma once

#ifndef PARSERPROCESSOR_H
#define PARSERPROCESSOR_H

#include <string>
#include <vector>
#include "Event.h"
#include "Conversion.h"
#include "ParserExceptions.h"
#include "ParserLog.h"

class ParserProcessor {
private:
	static const std::string PROCESS_ADD_EVENT;
	static const std::string PROCESS_EDIT_EVENT;
	static const std::string IDENTIFY_EVENT_NAME;
	static const std::string IDENTIFY_DAY;
	static const std::string IDENTIFY_DATE;
	static const std::string IDENTIFY_TIME;
	static const std::string ADD_EVENT_CORRECTOR;
	static const std::string EDIT_EVENT_CORRECTOR;
	static const std::string EVENT_MK_TIME_CORRECTOR;
	static const std::string PROCESS_SHOW_EVENT;

	static const int NUMBER_OF_KEYWORDS_MONTHS = 12;
	static const int NUMBER_OF_KEYWORDS_TIME = 2;
	static const int NUMBER_OF_KEYWORDS_DAYS = 11;
	static const int NUMBER_OF_DAYSINAWEEK = 7;
	static const int NUMBER_OF_KEYWORDS_SPECIAL = 3;
	static const std::string LOCKUP_USED_INFORMATION;
	
	std::string keywordMonths[NUMBER_OF_KEYWORDS_MONTHS];
	std::string keywordTime[NUMBER_OF_KEYWORDS_TIME];
	std::string keywordDay[NUMBER_OF_KEYWORDS_DAYS];
	std::string keywordSpecial[NUMBER_OF_KEYWORDS_SPECIAL];
	
	//boolean variables for Add and Edit command
	bool matchFound;
	bool startDayFound;
	bool endDayFound;
	bool startTimeFound;
	bool endTimeFound;
	bool afterTwelve;
	bool nameFound;
	bool toFound;
	bool deadlineFound;

	//boolean variables for Show command
	//to check if Show is a range of days 
	bool oneMatchFound;
	bool twoMatchFound;
	//to identify what type of Show 
	bool systemShowDay;
	bool systemShowWeek;
	bool systemShowMonth;
	bool systemShowYear;
	bool systemShowOthers;
	bool userShowDay;
	bool userShowRangeOfDays;
	bool userShowMonth;
	bool userShowRangeOfMonths;

	Event tempEventStore;
	ParserLog logger;
	std::vector<std::string> fragmentedWords;
	struct tm* now;

public:
	struct timeSet {
		int hour;
		int minute;
	};

	ParserProcessor();

	Event processAddEvent(std::vector<std::string>);
	Event processEditEvent(std::vector<std::string>);
	
	bool identifyEventName(int);
	bool identifyDay(int);

	bool identifyDate(int);
	int checkYear(int,int*);
	int checkDay(int,int*);
	int checkDayTo(int,int*);
	void assignDate(int,int,int,int);

	bool identifyTime(int);
	int extractFirstTimeInteger(int,int*);
	timeSet extractHourMin(int,int,int*);
	timeSet extractHourMinTo(int,int*);
	void assignTime(timeSet,timeSet);

	bool identifyDeadline(int);
	bool identifyImportance(int);

	void addEventCorrector();
	void editEventCorrector();
	void eventMktimeCorrector();

	Event processShowEvent(std::vector<std::string>);
	bool checkShowByYear(int);
	bool checkSystemBasedShow(int);
	bool identifyShowDay(int);
	bool identifyShowDate(int);
	int checkShowDay(int,int*);
	int checkShowDayTo(int,int*);
	void assignShowDate(int,int,int,int);
	void showEventCorrector();
};

#endif