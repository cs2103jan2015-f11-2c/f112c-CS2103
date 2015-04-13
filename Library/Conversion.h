//@author A0111379H

#pragma once

#ifndef CONVERSION_H
#define CONVERSION_H

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

#include "Event.h"

const string LABEL_STARTYEAR = "Start Year: ";
const string LABEL_STARTMONTH = "Start Month: ";
const string LABEL_STARTDAY = "Start Day: ";
const string LABEL_STARTHOUR = "Start Hour: ";
const string LABEL_STARTMIN = "Start Min: ";
const string LABEL_ENDYEAR = "End Year: ";
const string LABEL_ENDMONTH = "End Month: ";
const string LABEL_ENDDAY = "End Day: ";
const string LABEL_ENDHOUR = "End Hour: ";
const string LABEL_ENDMIN = "End Min: ";

class Conversion
{
public:
	// Variables
	static const int base;

	Conversion(void);
	~Conversion(void);

	std::string boolToString(bool);
	bool stringToBool (std::string);

	std::string eventToString(Event);
	Event stringToEvent(std::string);

	int monthToInt (std::string);
	std::string intToMonth (int);

	std::string intToDayOfWeek (int);
	int dayOfWeekToInt (std::string);

	std::string intToTime (int);
	int timeToInt (std::string);

	std::string intToString (int);
	int stringToInt (std::string);

	std::string toLowerCase(std::string);

	std::string tmToString(Event convertEvent);

	int determineLastDayOfMth(int month, int year);
	bool isLeapYear(int year);
};

#endif

