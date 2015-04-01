#pragma once

#ifndef UISHOW_H
#define UISHOW_H

#include <iostream>
#include <string>
#include <ctime>
#include <cctype>
#include <vector>
#include <sstream>
#include <assert.h>

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

	std::string currentCommand;

	//getters
	std::string getShowDay();
	std::string getShowWeek();
	std::string getShowMonth();
	std::string getShowAll();
	std::string getShowArchive();
	std::string getShowFloat();

	//Pre-condition : function setCurrentCommand must be executed first before this function is being called
	std::string getCurrentCommand();

	//Pre-condition : Non
	//This function takes in a string that contains that date(s)/labels that is being displayed in the main display currently
	//It returns the string which contain the command to display the next date(s)/labels based on what it has received
	//e.g. It takes in 10 Feb. It will return show 11feb
	//e.g. It takes in 10 Feb - 20 Feb. It will return show 20feb - 2mar (Next 10 days)
	//e.g. It takes in Mar. It will return show Apr
	std::string displayNext(std::string, std::vector<tm>);

	//Pre-condition : Non
	//This function takes in a string that contains that date(s)/labels that is being displayed in the main display currently
	//It returns the string which contain the command to display the previous date(s)/labels based on what it has received
	//e.g. It takes in 10 Feb. It will return show 9beb
	//e.g. It takes in 10 Feb - 20 Feb. It will return show 31jan - 9feb (Previous 10 days)
	//e.g. It takes in Mar. It will return show Feb
	std::string displayBack(std::string, std::vector<tm>);

	//Pre-condition : Non
	//Use in conjuction with function generateCurrentCommand & store it in currentCommand
	void setCurrentCommand(std::string, std::vector<tm>);

	//Pre-condition : Non
	//This function should combine with COMMAND_SHOW (at the front) to generate a proper command 
	//This function takes in a string that contains that date(s) from calendar in it's specific format of dd/mm/yyyy in string form
	//and return it's equivalent show command
	std::string generateDisplayFromCalender(std::string,std::string);

    //Pre-condition : Non
	//This function takes in a string that contains that date(s)/labels that is being displayed in the main display currently
	//It returns the string which contain the command to display this same date(s)/labels based on what is has received 
	//e.g. It takes in 10 Feb. It will return 10 Feb
	//e.g. It takes in 10 Feb - 20 Feb. It will return show 10 Feb - 20 Feb.
	//e.g. It takes in Mar. It will return show Feb
	std::string generateCurrentCommand(std::string, std::vector<tm>);

	//Pass in the date and the number of days to be shifted. It will return the shifted tm
	// Can accept any int (positive and negative)
	tm shiftDate(tm, int);

	std::string convertFromTmToStr(tm);

	int countNumDays(tm, tm);

	void initializeTime(tm);
	
	bool checkIsSingleDate(std::vector<tm>);

	std::string intToString(int);

	int stringToInt(std::string);

	std::string intToMonth(int);

};
#endif

