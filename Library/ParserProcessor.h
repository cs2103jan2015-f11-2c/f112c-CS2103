//@author A0111379H

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
	static const std::string ADD_EVENT_CORRECTOR;
	static const std::string EDIT_EVENT_CORRECTOR;
	static const std::string EVENT_MK_TIME_CORRECTOR;
	static const std::string PROCESS_SHOW_EVENT;
	static const std::string IDENTIFY_EVENT_NAME;
	static const std::string IDENTIFY_DAY;
	static const std::string IDENTIFY_DATE;
	static const std::string IDENTIFY_TIME;
	static const std::string IDENTIFY_DEADLINE;
	static const std::string IDENTIFY_IMPORTANCE;
	static const std::string SYSTEM_SHOW;
	static const std::string SHOW_YEAR;

	static const std::string CONVERT_NORMAL_TO_FLOAT;

	static const int NUMBER_OF_KEYWORDS_MONTHS = 23;
	static const int NUMBER_OF_KEYWORDS_TIME = 2;
	static const int NUMBER_OF_KEYWORDS_DAYS = 18;
	static const int NUMBER_OF_DAYSINAWEEK = 7;

	static const std::string LOCKUP_USED_INFORMATION;
	
	static const int LOWER_RANGE_YEAR = 1970;
	static const int HIGHER_RANGE_YEAR = 3000;
	static const int TM_YEAR_ADJUSTMENT = 1900;
	static const int POSSIBLE_YEAR_INTEGER = 1300;
	static const int INVALID_NUMBER = -1;
	static const int MAX_HOUR = 12;
	static const int MAX_MINUTE = 60;
	static const int MORNING_TIME = 12;
	static const int MIDNIGHT_TIME = 0;
	static const int MORNING_AFTERNOON_DIFFERENTIAL = 12;
	static const int DO_NOT_TOUCH = 100;

	std::string keywordMonths[NUMBER_OF_KEYWORDS_MONTHS];
	std::string keywordTime[NUMBER_OF_KEYWORDS_TIME];
	std::string keywordDay[NUMBER_OF_KEYWORDS_DAYS];
	
	//boolean variables for Add and Edit command
	bool matchFound;
	bool startDayFound;
	bool endDayFound;
	bool startTimeFound;
	bool endTimeFound;
	bool afterTwelve;
	bool nameFound;
	bool firstTriggerKeyword;
	int nameIndex;
	int semiColonIndex;
	bool toFound;
	bool deadlineFound;
	bool importanceFound;
	bool normalToFloat;

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
	
	bool findExactWord(std::string,std::string);

	bool identifyNormaltoFloat(int);
	int identifyDay(int);

	int identifyDate(int);
	int checkYear(int,int*);
	int checkDay(int,int*);
	int checkDayTo(int,int*);
	void assignDate(int,int,int,int);

	int identifyTime(int);
	int extractFirstTimeInteger(int,int*);
	timeSet extractHourMin(int,int,int*);
	timeSet extractHourMinTo(int,int*);
	void assignTime(timeSet,timeSet);

	int identifyDeadline(int);
	int identifyImportance(int);

	void identifyEventName(int);
	std::string setEventName(int);
	void addEventCorrector();
	void checkStartBeforeEnd();
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