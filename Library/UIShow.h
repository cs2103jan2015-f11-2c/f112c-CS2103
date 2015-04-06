/**
 * This class is used to generate commands related to "show" by calling the respective public methods and passing in the required data (if required)
 * The commands generated should be passed to Logic for further execution
 * [WARNING - This class does not execute any command, it purely generate command that are passed on for execution]
 
 * @author A0111230J
 */

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
	//Constructor and destructor
	UIShow(void);
	~UIShow(void);

/*
* =================================================================================================================================================================== 
* Static variables which contain the respective commands
* ===================================================================================================================================================================
*/
public:
	static const std::string COMMAND_SHOW;
	static const std::string SHOW_DAY;
	static const std::string SHOW_WEEK;
	static const std::string SHOW_MONTH;
	static const std::string SHOW_ALL;
	static const std::string SHOW_DONE;
	static const std::string SHOW_FLOAT;

	static const std::string WORD_COMMANDS;
	static const std::string WORD_HELP_INTRO;
	static const std::string WORD_HELP;
	static const std::string WORD_SEARCH_MODE;
	static const std::string WORD_SHORTCUTS;

	static const std::string LABEL_WEEK;
	static const std::string LABEL_MONTH;

private:
	std::string _currentCommand;
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Public getters to retrive the respective commands
* ===================================================================================================================================================================
*/
public:
	std::string getShowDay();
	std::string getShowWeek();
	std::string getShowMonth();
	std::string getShowAll();
	std::string getShowDone();
	std::string getShowFloat();

	//Pre-condition : function setCurrentCommand must be executed first before this function is being called
	std::string getCurrentCommand();
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Functions to support the execution of the Public methods below
* ===================================================================================================================================================================
*/
	//Pre-condition : Non
	//This function takes in a string that contains that date(s)/labels that is being displayed in the main display currently
	//It returns the string which contain the command to display this same date(s)/labels based on what is has received 
	//e.g. It takes in 10 Feb. It will return 10 Feb
	//e.g. It takes in 10 Feb - 20 Feb. It will return show 10 Feb - 20 Feb.
	//e.g. It takes in Mar. It will return show Feb
	std::string generateCurrentCommand(std::string, std::vector<tm>);

	//Pre-condition : Valid date ( 1 <= month day <=31 , 1 <= month <= 12 , 70 <= year <= 1100) 
	//Pass in the date and the number of days to be shifted. It will return the shifted tm
	//Can accept any int (positive and negative)
	tm shiftDate(tm, int);

	//Pre-condition : Valid date ( 1 <= month day <=31 , 1 <= month <= 12 , 70 <= year <= 1100) 
	std::string generateShowWeekForNext(tm);

	//Pre-condition : Valid date ( 1 <= month day <=31 , 1 <= month <= 12 , 70 <= year <= 1100) 
	std::string generateShowMonthForNext(tm);

	//Pre-condition : Valid date ( 1 <= month day <=31 , 1 <= month <= 12 , 70 <= year <= 1100) 
	std::string generateShowWeekForBack(tm);

	//Pre-condition : Valid date ( 1 <= month day <=31 , 1 <= month <= 12 , 70 <= year <= 1100) 
	std::string generateShowMonthForBack(tm);

	//Pre-condition : Valid date ( 1 <= month day <=31 , 1 <= month <= 12 , 1970 <= year <= 3000 )
	//[WARNING - assertion failure if date is invalid]
	//Pass in the date in dd/MM/YYYY form
	//Returns date in dd Month YYYY std::string form
	std::string generateDateString(std::string);

	//Pre-condition : Valid date ( 1 <= month day <=31 , 1 <= month <= 12 , 70 <= year <= 1100) 
	std::string convertFromTmToStr(tm);

	//Pre-condition : Valid date ( 1 <= month day <=31 , 1 <= month <= 12 , 70 <= year <= 1100 )
	//Pass in the 2 dates in tm type
	//Return number of days between these 2 dates. 
	//[Remarks - All return numbers will be non-negative regardless the order of dates passed in] 
	int countNumDays(tm, tm);

	void initializeTime(tm);
	//Pre-condition : size of vector should be 2
	//				  Valid date ( 1 <= month day <=31 , 1 <= month <= 12 , 70 <= year <= 1100 )
	bool checkIsSingleDate(std::vector<tm>);
	
	//Pre-condition : string must not be empty
	int stringToInt(std::string);

	std::string intToString(int);

	std::string intToMonth(int);
//===================================================================================================================================================================

/*
* =================================================================================================================================================================== 
* Public methods and their respective APIs
* ===================================================================================================================================================================
*/
	//Pre-condition : Non
	//This function takes in a string that contains that date(s)/labels that is being displayed in the main display currently
	//It returns the string which contain the command to display the next date(s)/labels based on what it has received
	//Validity of the input and output dates are checked
	//e.g. It takes in 10 Feb. It will return show 11feb
	//e.g. It takes in 10 Feb - 20 Feb. It will return show 20feb - 2mar (Next 10 days)
	//e.g. It takes in Mar. It will return show Apr
	std::string displayNext(std::string, std::vector<tm>);

	//Pre-condition : Non
	//This function takes in a string that contains that date(s)/labels that is being displayed in the main display currently
	//It returns the string which contain the command to display the previous date(s)/labels based on what it has received
	//Validity of the input and output dates are checked
	//e.g. It takes in 10 Feb. It will return show 9beb
	//e.g. It takes in 10 Feb - 20 Feb. It will return show 31jan - 9feb (Previous 10 days)
	//e.g. It takes in Mar. It will return show Feb
	std::string displayBack(std::string, std::vector<tm>);

	//Pre-condition : Non
	//This function should combine with COMMAND_SHOW (at the front) to generate a proper command 
	//This function takes in a string that contains that date(s) from calendar in it's specific format of dd/mm/yyyy in string form
	//and return it's equivalent show command
	//Validity of the input and output dates are checked
	std::string generateDisplayFromCalender(std::string,std::string);

	//Pre-condition : Non
	//Use in conjuction with function generateCurrentCommand & store it in currentCommand
	void setCurrentCommand(std::string, std::vector<tm>);
//===================================================================================================================================================================

};
#endif

