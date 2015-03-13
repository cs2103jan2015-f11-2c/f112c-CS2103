#pragma once

#ifndef CONVERSION_H
#define CONVERSION_H

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

#include "Event.h"

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

	string tmToString(Event convertEvent);


};

#endif

