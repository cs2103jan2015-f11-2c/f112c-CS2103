#include "UIShow.h"


UIShow::UIShow(void)
{
}


UIShow::~UIShow(void)
{
}

//Variables that cannot be initialized in UIShow.h
const std::string UIShow::COMMAND_SHOW = "show";
const std::string UIShow::SHOW_DAY = "show today";
const std::string UIShow::SHOW_WEEK = "show week";
const std::string UIShow::SHOW_MONTH = "show month";
const std::string UIShow::SHOW_ALL = "show all";
const std::string UIShow::SHOW_ARCHIVE = "show archive";
const std::string UIShow::SHOW_FLOAT = "show floating";


std::string UIShow::getShowDay(){
	return SHOW_DAY;
}

std::string UIShow::getShowWeek(){
	return SHOW_WEEK;
}

std::string UIShow::getShowMonth(){
	return SHOW_MONTH;
}

std::string UIShow::getShowAll(){
	return SHOW_ALL;
}

std::string UIShow::getShowArchive(){
	return SHOW_ARCHIVE;
}

std::string UIShow::getShowFloat(){
	return SHOW_FLOAT;
}

std::string UIShow::displayNext(std::string currentMainDisplayLabel, std::vector<tm> mainDisplayDate){
	if (currentMainDisplayLabel == "Commands"){
		return "Commands";
	}

	if (currentMainDisplayLabel == "Help Introduction"){
		return "help";
	}

	std::string newShowCommand = "";

	//function to check whether it is single or multiple day
	bool isSingleDate = checkIsSingleDate(mainDisplayDate);
	if ( isSingleDate ){
		tm newDateToShow = shiftDate(mainDisplayDate[0],1);
		newShowCommand = COMMAND_SHOW + " " + convertFromTmToStr(newDateToShow);
	} else {
		int numDaysToShift = countNumDays (mainDisplayDate[0], mainDisplayDate[1] + 1);
		tm newStartDate = shiftDate(mainDisplayDate[0], numDaysToShift);
		tm newEndDate = shiftDate(mainDisplayDate[1], numDaysToShift);
		newShowCommand = COMMAND_SHOW + " " + convertFromTmToStr(newStartDate) + " to " + convertFromTmToStr(newEndDate);
	}
	return newShowCommand;
	
}



std::string UIShow::displayBack(std::string currentMainDisplayLabel, std::vector<tm> mainDisplayDate){
	//show back the same stuffs
	if (currentMainDisplayLabel == "Commands"){
		return "Commands";
	}

	if (currentMainDisplayLabel == "Help Introduction"){
		return "help";
	}
	
	std::string newShowCommand = "";

	//function to check whether it is single or multiple day
	bool isSingleDate = checkIsSingleDate(mainDisplayDate);
	if ( isSingleDate ){
		tm newDateToShow = shiftDate(mainDisplayDate[0],-1);
		newShowCommand = COMMAND_SHOW + " " + convertFromTmToStr(newDateToShow);
	} else {
		int numDaysToShift = countNumDays (mainDisplayDate[0], mainDisplayDate[1]) + 1;
		tm newStartDate = shiftDate(mainDisplayDate[0], -numDaysToShift);
		tm newEndDate = shiftDate(mainDisplayDate[1], -numDaysToShift);
		newShowCommand = COMMAND_SHOW + " " + convertFromTmToStr(newStartDate) + " to " + convertFromTmToStr(newEndDate);
	}
	return newShowCommand;
}

int UIShow::countNumDays(tm startDay, tm endDay){
	initializeTime(startDay);
	initializeTime(endDay);
	std::time_t start = std::mktime(&startDay);
	std::time_t end = std::mktime(&endDay);

	int dayDifference = std::difftime(end,start)/(60*60*24);

	return dayDifference;
}

void UIShow::initializeTime(tm date){
	date.tm_hour = 0;
	date.tm_min = 0;
	date.tm_sec = 0;
}



std::string UIShow::convertFromTmToStr(tm date){
	std::string dateString = "";

	Conversion convert;
	dateString += convert.intToString(date.tm_mday);
	dateString += convert.intToMonth(date.tm_mon);
	dateString += " ";
	dateString += convert.intToString(date.tm_year + 1900);

	return dateString;
}

tm UIShow::shiftDate(tm date, int numDaysToShift){
	time_t t = time(0);
	struct tm* newDatePtr = localtime(&t);

	newDatePtr->tm_mday = date.tm_mday + numDaysToShift;
	newDatePtr->tm_mon = date.tm_mon;
	newDatePtr->tm_year = date.tm_year;
	std::mktime(newDatePtr);

	struct tm newDate;
	newDate.tm_mday = newDatePtr->tm_mday;
	newDate.tm_mon = newDatePtr->tm_mon;
	newDate.tm_year = newDatePtr->tm_year;
	
	return newDate;
}


bool UIShow::checkIsSingleDate(std::vector<tm> mainDisplayDate){
	bool isSingleDate = false;

	if(mainDisplayDate[0].tm_mday == mainDisplayDate[1].tm_mday && mainDisplayDate[0].tm_mon == mainDisplayDate[1].tm_mon && mainDisplayDate[0].tm_year == mainDisplayDate[1].tm_year){
			isSingleDate = true;
		}
	return isSingleDate;
}

std::string  UIShow::generateDisplayFromCalender(std::string currentMainDisplayLabel, std::string chosenDate){
	if (currentMainDisplayLabel == "Commands"){
		return "Commands";
	}

	if (currentMainDisplayLabel == "Help Introduction"){
		return "help";
	}
	//Generate new command


}

