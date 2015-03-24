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

	//function to check whether it is single or multiple day

	bool isSingleDate = checkIsSingleDate(mainDisplayDate);
	if ( isSingleDate ){

		// Forward by 1 day
	} else {
		// Count number of days 
		// Forward by this no. of days
	}
	
	
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
		// Count number of days 
		// backward by this no. of days
	}
	
	return newShowCommand;
}

std::string UIShow::convertFromTmToStr(tm date){
	std::string dateString = "";

	Conversion convert;
	dateString += convert.intToString(date.tm_mday);
	dateString += convert.intToMonth(date.tm_mon);
	dateString += " ";
	dateString += convert.intToString(date.tm_year);

	return dateString;
}

tm UIShow::shiftDate(tm date, int numDaysToShift){
	time_t t = time(0);
	struct tm* newDatePtr = localtime(&t);

	newDatePtr->tm_mday = date.tm_mday + numDaysToShift;
	newDatePtr->tm_mon = date.tm_mon;
	newDatePtr->tm_year = date.tm_year;
	mktime(newDatePtr);

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

