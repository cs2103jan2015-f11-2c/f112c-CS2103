#pragma once

#ifndef UISHOW_H
#define UISHOW_H

#include <iostream>
#include <string>
#include <ctime>
#include <vector>

#include "Conversion.h"

class UIShow
{
public:
	UIShow(void);
	~UIShow(void);

	static const std::string COMMAND_SHOW;
	static const std::string SHOW_DAY;
	static const std::string SHOW_WEEK;
	static const std::string SHOW_MONTH;
	static const std::string SHOW_ALL;
	static const std::string SHOW_ARCHIVE;
	static const std::string SHOW_FLOAT;

	//getters
	std::string getShowDay();
	std::string getShowWeek();
	std::string getShowMonth();
	std::string getShowAll();
	std::string getShowArchive();
	std::string getShowFloat();

	//functions

	//Pre-condition : Non
	//This function should combine with COMMAND_SHOW (at the front) to generate a proper command 
	//This function takes in a string that contains that date(s) that is being displayed in the main display currently
	//It returns the string which contain the command to display the next date(s) based on that it has received
	//e.g. It takes in 10 Feb. It will return 11 Feb
	//e.g. It takes in 10 Feb - 20 Feb. It will return 20 Feb - 2 Mar (Next 10 days)
	//e.g. It takes in Mar. It will return Apr
	std::string displayNext(std::string, std::vector<tm>);


	//Pre-condition : Non
	//This function should combine with COMMAND_SHOW (at the front) to generate a proper command 
	//This function takes in a string that contains that date(s) that is being displayed in the main display currently
	//It returns the string which contain the command to display the previous date(s) based on that it has received
	//e.g. It takes in 10 Feb. It will return 09 Feb
	//e.g. It takes in 10 Feb - 20 Feb. It will return 31 Jan - 9 Feb (Previous 10 days)
	//e.g. It takes in Mar. It will return Feb
	std::string displayBack(std::string, std::vector<tm>);


	//Private:

	//Pass in the date and the number of days to be shifted. It will return the shifted tm
	// Can accept any int (positive and negative)
	tm shiftDate(tm, int);

	std::string convertFromTmToStr(tm);

	int countNumDays(tm, tm);

	void initializeTime(tm);
	
	bool checkIsSingleDate(std::vector<tm>);
//===================================================================================================================================================================
	//Pre-condition : Non
	//This function should combine with COMMAND_SHOW (at the front) to generate a proper command 
	//This function takes in a string that contains that date(s) that is being displayed in the main display currently
	//and the date selected in string form
	//It returns the string which contain the command to display based on that it has received
	//e.g. It takes in 10 Feb (first string) & 20 Feb (second string) It will return 20 Feb
	//e.g. It takes in 10 Feb - 20 Feb (first string) & 1 Mar (second string), it will return 1 Mar - 10 Mar
	//e.g. It takes in Mar(first string) & 10 Apr (second string); it will return month apr
	std::string generateDisplayFromCalender(std::string,std::string);

};
#endif

