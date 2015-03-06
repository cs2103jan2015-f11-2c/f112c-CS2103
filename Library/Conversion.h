#pragma once

#ifndef CONVERSION_H
#define CONVERSION_H

#include <iostream>
#include <string>

#include "Event.h"

class Conversion
{
public:
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

	std::string intToString (int);
	int stringToInt (std::string);

};

#endif

