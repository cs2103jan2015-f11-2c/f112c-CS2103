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

std::string UIShow::getCurrentCommand(){
	return currentCommand;
}


std::string UIShow::displayNext(std::string currentMainDisplayLabel, std::vector<tm> mainDisplayDate){
	if (currentMainDisplayLabel == "Commands"){
		return "";
	}

	if (currentMainDisplayLabel == "Help Introduction"){
		return "";
	}

	if (currentMainDisplayLabel == "Search Mode"){
		return "";
	}

	if (currentMainDisplayLabel == "Shortcuts"){
		return "";
	}

	if (currentMainDisplayLabel.substr(0,6) == "[Week]"){
		time_t now;
		struct tm front;
		struct tm back;

		time(&now);
		front = *localtime(&now);
		back = *localtime(&now);

		front = mainDisplayDate[1];
		front.tm_mday += 1;
		std::mktime(&front);

		back = front;
		back.tm_mday += 6;
		std::mktime(&back);

		std::string newCommand = COMMAND_SHOW + " " + convertFromTmToStr(front) + " to " + convertFromTmToStr(back);

		return newCommand;
	}

	if (currentMainDisplayLabel.substr(0,7) == "[Month]"){
		assert(mainDisplayDate[0].tm_mon == mainDisplayDate[1].tm_mon);

		time_t now;
		struct tm nextMonth;

		time(&now);
		nextMonth = *localtime(&now);
		nextMonth = mainDisplayDate[0];
		nextMonth.tm_mon ++;
		std::mktime(&nextMonth);

		std::string nextMonthString = intToMonth(nextMonth.tm_mon);
		std::string yearString = intToString(nextMonth.tm_year);

		std::string newCommand = COMMAND_SHOW + " " + nextMonthString + " " + yearString;
		
		return newCommand;
	}


	std::string newShowCommand = "";

	//function to check whether it is single or multiple day
	bool isSingleDate = checkIsSingleDate(mainDisplayDate);
	if ( isSingleDate ){
		tm newDateToShow = shiftDate(mainDisplayDate[0],1);
		newShowCommand = COMMAND_SHOW + " " + convertFromTmToStr(newDateToShow);
	} else {
		int numDaysToShift = countNumDays (mainDisplayDate[0], mainDisplayDate[1]) + 1;
		tm newStartDate = shiftDate(mainDisplayDate[0], numDaysToShift);
		tm newEndDate = shiftDate(mainDisplayDate[1], numDaysToShift);
		newShowCommand = COMMAND_SHOW + " " + convertFromTmToStr(newStartDate) + " to " + convertFromTmToStr(newEndDate);
	}
	return newShowCommand;
	
}



std::string UIShow::displayBack(std::string currentMainDisplayLabel, std::vector<tm> mainDisplayDate){
	//show back the same stuffs
	if (currentMainDisplayLabel == "Commands"){
		return "";
	}

	if (currentMainDisplayLabel == "Help Introduction"){
		return "";
	}

	if (currentMainDisplayLabel == "Search Mode"){
		return "";
	}
	
	if (currentMainDisplayLabel == "Shortcuts"){
		return "";
	}

	if (currentMainDisplayLabel.substr(0,6) == "[Week]"){
		time_t now;
		struct tm front;
		struct tm back;

		time(&now);
		front = *localtime(&now);
		back = *localtime(&now);

		back = mainDisplayDate[1];
		back.tm_mday -= 7;
		std::mktime(&back);

		front = back;
		front.tm_mday -= 6;
		std::mktime(&front);

		std::string newCommand = COMMAND_SHOW + " " + convertFromTmToStr(front) + " to " + convertFromTmToStr(back);

		return newCommand;
	}

	if (currentMainDisplayLabel.substr(0,7) == "[Month]"){
		assert(mainDisplayDate[0].tm_mon == mainDisplayDate[1].tm_mon);

		time_t now;
		struct tm nextMonth;

		time(&now);
		nextMonth = *localtime(&now);
		nextMonth = mainDisplayDate[0];
		nextMonth.tm_mon --;
		std::mktime(&nextMonth);

		std::string nextMonthString = intToMonth(nextMonth.tm_mon);
		std::string yearString = intToString(nextMonth.tm_year);

		std::string newCommand = COMMAND_SHOW + " " + nextMonthString + " " + yearString;
		
		return newCommand;
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

void UIShow:: setCurrentCommand(std::string currentMainDisplayLabel, std::vector<tm> mainDisplayDate){
	currentCommand = generateCurrentCommand(currentMainDisplayLabel, mainDisplayDate);
}

std::string UIShow::generateCurrentCommand(std::string currentMainDisplayLabel, std::vector<tm> mainDisplayDate){
	//show back the same stuffs
	if (currentMainDisplayLabel == "Commands"){
		return "Commands";
	}

	if (currentMainDisplayLabel == "Help Introduction"){
		return "Help";
	}

	if (currentMainDisplayLabel == "Search Mode"){
		return "Search";
	}
	
	if (currentMainDisplayLabel == "Shortcuts"){
		return "Shortcuts";
	}

	std::string newShowCommand = "";

	//function to check whether it is single or multiple day
	bool isSingleDate = checkIsSingleDate(mainDisplayDate);
	if ( isSingleDate ){
		newShowCommand = COMMAND_SHOW + " " + convertFromTmToStr(mainDisplayDate[0]);
	} else {
		newShowCommand = COMMAND_SHOW + " " + convertFromTmToStr(mainDisplayDate[0]) + " to " + convertFromTmToStr(mainDisplayDate[1]);
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

	dateString += intToString(date.tm_mday);
	dateString += intToMonth(date.tm_mon);
	dateString += " ";
	dateString += intToString(date.tm_year + 1900);

	return dateString;
}


std::string UIShow::intToString (int num){
	std::string outString;
	std::ostringstream oss;
	oss << num;
	return oss.str();
}

int UIShow::stringToInt (std::string str){
	int outNum;
	std::istringstream in(str);
	in >> outNum;
	return outNum;
}

std::string UIShow::intToMonth (int monthInNum){
	if(monthInNum == 0){
		return "jan";
	} else if(monthInNum  == 1){
		return "feb";
	} else if(monthInNum  == 2){
		return "mar";
	} else if(monthInNum  == 3){
		return "apr";
	} else if(monthInNum  == 4){
		return "may";
	} else if(monthInNum  == 5){
		return "jun";
	} else if(monthInNum  == 6){
		return "jul";
	} else if(monthInNum  == 7){
		return "aug";
	} else if(monthInNum  == 8){
		return "sep";
	} else if(monthInNum  == 9){
		return "oct";
	} else if(monthInNum  == 10){
		return "nov";
	} else if(monthInNum  == 11){
		return "dec";
	} else {
		return "Invalid month";
	}
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



std::string  UIShow::generateDisplayFromCalender(std::string startDate, std::string endDate){
	 int i=0;
	
	 std::string startDateDay = "";
	 for (;std::isdigit(startDate[i]);i++){
			startDateDay += startDate[i];
	 }

	 i++;

	 std::string startDateMonth = "";
	 for (; std::isdigit(startDate[i]);i++){
		startDateMonth += startDate[i];
	 }

	 int startDateMonthNum = stringToInt(startDateMonth);
	 std::string startDateMonthString = intToMonth(startDateMonthNum-1);

	 i++;

	 std::string startDateYear = "";
	 for (; std::isdigit(startDate[i]);i++){
		startDateYear += startDate[i];
	 }

	 i=0;
	 std::string endDateDay = "";
	  
	 for (; std::isdigit(endDate[i]);i++){
		 endDateDay += endDate[i];
	 }

	 i++;

	 std::string endDateMonth = "";
	 for (; std::isdigit(endDate[i]);i++){
		 endDateMonth += endDate[i];
	 }
	 int endDateMonthNum = stringToInt(endDateMonth);
	 std::string endDateMonthString = intToMonth(endDateMonthNum-1);

	 i++;

	 std::string endDateYear = "";
	 for (; std::isdigit(endDate[i]);i++){
		 endDateYear += endDate[i];
	 }

	 std::string command = COMMAND_SHOW + " " + startDateDay + startDateMonthString + " " + startDateYear + " to " + endDateDay + endDateMonthString + " " + endDateYear;
	 
	 return command;
}


