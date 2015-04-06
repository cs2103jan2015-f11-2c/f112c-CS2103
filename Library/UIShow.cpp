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
const std::string UIShow::SHOW_DONE = "show done";
const std::string UIShow::SHOW_FLOAT = "show floating";

const std::string UIShow::WORD_COMMANDS = "Commands";
const std::string UIShow::WORD_HELP_INTRO = "Help Introduction";
const std::string UIShow::WORD_HELP = "Help";
const std::string UIShow::WORD_SEARCH_MODE = "Search Mode";
const std::string UIShow::WORD_SHORTCUTS = "Shortcuts";

const std::string UIShow::LABEL_WEEK = "[Week]";
const std::string UIShow::LABEL_MONTH = "[Month]";


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

std::string UIShow::getShowDone(){
	return SHOW_DONE;
}

std::string UIShow::getShowFloat(){
	return SHOW_FLOAT;
}

std::string UIShow::getCurrentCommand(){
	return _currentCommand;
}


std::string UIShow::displayNext(std::string currentMainDisplayLabel, std::vector<tm> mainDisplayDate){
	assert(!currentMainDisplayLabel.empty());
	assert(mainDisplayDate.size() == 2);
	
	/*
	try {
		if ( mainDisplayDate[0].tm_mday<0 ){

			throw "msg";
	}
	} catch (std::string str){
		return str;
	}
	*/
	
	//exception 0 <= tm_mday <= 30
	//exception 0 <= tm_mon <= 11
	//exception 70 <= tm_year <= 1100
	
	if (currentMainDisplayLabel == WORD_COMMANDS || currentMainDisplayLabel == WORD_HELP_INTRO || currentMainDisplayLabel == WORD_SEARCH_MODE || currentMainDisplayLabel == WORD_SHORTCUTS){
		return "";
	} else if (currentMainDisplayLabel.substr(0,6) == LABEL_WEEK){
		std::string newCommand = generateShowWeekForNext(mainDisplayDate[1]);
		return newCommand;
	} else if (currentMainDisplayLabel.substr(0,7) == LABEL_MONTH){
		assert(mainDisplayDate[0].tm_mon == mainDisplayDate[1].tm_mon);
		std::string newCommand = generateShowMonthForNext(mainDisplayDate[0]);
		return newCommand;
	} else if (checkIsSingleDate(mainDisplayDate) ){
		tm newDateToShow = shiftDate(mainDisplayDate[0],1);
		std::string newCommand = COMMAND_SHOW + " " + convertFromTmToStr(newDateToShow);
		return newCommand;
	} else {
		int numDaysToShift = countNumDays (mainDisplayDate[0], mainDisplayDate[1]) + 1;
		tm newStartDate = shiftDate(mainDisplayDate[0], numDaysToShift);
		tm newEndDate = shiftDate(mainDisplayDate[1], numDaysToShift);
		std::string newCommand = COMMAND_SHOW + " " + convertFromTmToStr(newStartDate) + " to " + convertFromTmToStr(newEndDate);
		return newCommand;
	}
}


std::string UIShow::displayBack(std::string currentMainDisplayLabel, std::vector<tm> mainDisplayDate){
	assert(!currentMainDisplayLabel.empty());
	assert(mainDisplayDate.size() == 2);

	//exception 1 <= month day <=31
	//exception 1 <= month <= 12
	//exception year

	if (currentMainDisplayLabel == WORD_COMMANDS || currentMainDisplayLabel == WORD_HELP_INTRO || currentMainDisplayLabel == WORD_SEARCH_MODE || currentMainDisplayLabel == WORD_SHORTCUTS){
		return "";
	} else if (currentMainDisplayLabel.substr(0,6) == LABEL_WEEK){
		std::string newCommand = generateShowWeekForBack(mainDisplayDate[1]);
		return newCommand;
	} else if (currentMainDisplayLabel.substr(0,7) == LABEL_MONTH){
		assert(mainDisplayDate[0].tm_mon == mainDisplayDate[1].tm_mon);
		std::string newCommand = generateShowMonthForBack(mainDisplayDate[0]);
		return newCommand;
	} else if (checkIsSingleDate(mainDisplayDate) ){
		tm newDateToShow = shiftDate(mainDisplayDate[0],-1);
		 std::string newCommand = COMMAND_SHOW + " " + convertFromTmToStr(newDateToShow);
		 return newCommand;
	} else {
		int numDaysToShift = countNumDays (mainDisplayDate[0], mainDisplayDate[1]) + 1;
		tm newStartDate = shiftDate(mainDisplayDate[0], -numDaysToShift);
		tm newEndDate = shiftDate(mainDisplayDate[1], -numDaysToShift);
		std:: string newCommand = COMMAND_SHOW + " " + convertFromTmToStr(newStartDate) + " to " + convertFromTmToStr(newEndDate);
		return newCommand;
	}
}

std::string  UIShow::generateDisplayFromCalender(std::string startDate, std::string endDate){
	std::string startDateString = generateDateString(startDate);
	std::string endDateString = generateDateString(endDate);
	 
	std::string command = COMMAND_SHOW + " " + startDateString  + " to " + endDateString;
	return command;
}

void UIShow:: setCurrentCommand(std::string currentMainDisplayLabel, std::vector<tm> mainDisplayDate){
	_currentCommand = generateCurrentCommand(currentMainDisplayLabel, mainDisplayDate);
}

std::string UIShow::generateCurrentCommand(std::string currentMainDisplayLabel, std::vector<tm> mainDisplayDate){
	//exception 1 <= month day <=31
	//exception 1 <= month <= 12
	//exception year
	
	if (currentMainDisplayLabel == WORD_COMMANDS){
		return WORD_COMMANDS;
	} else if (currentMainDisplayLabel == WORD_HELP_INTRO){
		return WORD_HELP;
	} else if (currentMainDisplayLabel == WORD_SEARCH_MODE){
		return WORD_SEARCH_MODE;
	} else if (currentMainDisplayLabel == WORD_SHORTCUTS){
		return WORD_SHORTCUTS;
	} else if (currentMainDisplayLabel.substr(0,6) == LABEL_WEEK){
		std::string newShowCommand = SHOW_WEEK + currentMainDisplayLabel.substr(6);
		return newShowCommand;
	} else if (currentMainDisplayLabel.substr(0,7) == LABEL_MONTH){
		std::string newShowCommand = SHOW_MONTH + currentMainDisplayLabel.substr(7);
		return newShowCommand;
	} else {
		std::string newShowCommand = "";

		bool isSingleDate = checkIsSingleDate(mainDisplayDate);
		
		if ( isSingleDate ){
			newShowCommand = COMMAND_SHOW + " " + convertFromTmToStr(mainDisplayDate[0]);
		} else {
			newShowCommand = COMMAND_SHOW + " " + convertFromTmToStr(mainDisplayDate[0]) + " to " + convertFromTmToStr(mainDisplayDate[1]);
		}

		return newShowCommand;
	}
}

tm UIShow::shiftDate(tm date, int numDaysToShift){
	time_t t = time(0);
	struct tm* newDatePtr = localtime(&t);

	newDatePtr->tm_mday = date.tm_mday + numDaysToShift;
	newDatePtr->tm_mon = date.tm_mon;
	newDatePtr->tm_year = date.tm_year;

	std::mktime(newDatePtr);

	//exception 1 <= month day <=31
	//exception 1 <= month <= 12
	//exception year

	struct tm newDate;
	newDate.tm_mday = newDatePtr->tm_mday;
	newDate.tm_mon = newDatePtr->tm_mon;
	newDate.tm_year = newDatePtr->tm_year;
	
	return newDate;
}

std::string UIShow::generateShowWeekForNext(tm endDate){
	time_t now;
	struct tm front;
	struct tm back;

	time(&now);
	front = *localtime(&now);
	back = *localtime(&now);

	front = endDate;
	front.tm_mday += 1;
	std::mktime(&front);

	back = front;
	back.tm_mday += 6;
	std::mktime(&back);

	std::string newCommand = COMMAND_SHOW + " " + convertFromTmToStr(front) + " to " + convertFromTmToStr(back);

	return newCommand;
}

std::string UIShow::generateShowMonthForNext(tm startDate){
	time_t now;
	struct tm nextMonth;

	time(&now);
	nextMonth = *localtime(&now);
	nextMonth = startDate;
	nextMonth.tm_mon ++;
	std::mktime(&nextMonth);

	//exception 1 <= month day <=31
	//exception 1 <= month <= 12
	//exception year

	std::string nextMonthString = intToMonth(nextMonth.tm_mon);
	std::string yearString = intToString(nextMonth.tm_year + 1900);

	std::string newCommand = COMMAND_SHOW + " " + nextMonthString + " " + yearString;
	
	return newCommand;
}

std::string UIShow::generateShowWeekForBack(tm endDate){
	time_t now;
	struct tm front;
	struct tm back;

	time(&now);
	front = *localtime(&now);
	back = *localtime(&now);

	back = endDate;
	back.tm_mday -= 7;
	std::mktime(&back);

	front = back;
	front.tm_mday -= 6;
	std::mktime(&front);

	std::string newCommand = COMMAND_SHOW + " " + convertFromTmToStr(front) + " to " + convertFromTmToStr(back);

	return newCommand;
}

std::string UIShow::generateShowMonthForBack(tm startDate){
	time_t now;
	struct tm nextMonth;

	time(&now);
	nextMonth = *localtime(&now);
	nextMonth = startDate;
	nextMonth.tm_mon --;
	std::mktime(&nextMonth);

	//exception 1 <= month day <=31
	//exception 1 <= month <= 12
	//exception year

	std::string nextMonthString = intToMonth(nextMonth.tm_mon);
	std::string yearString = intToString(nextMonth.tm_year + 1900);

	std::string newCommand = COMMAND_SHOW + " " + nextMonthString + " " + yearString;
		
	return newCommand;
}

std::string UIShow::generateDateString(std::string date){
	int index=0;
	int i=0;
	
	std::string dateDay = "";
	for (;std::isdigit(date[index]);index++){
		dateDay += date[index];
	}

	int dateDayInt = stringToInt(dateDay);
	
	index++;

	std::string dateMonth = "";
	for (;std::isdigit(date[index]);index++){
		dateMonth += date[index];
	}

	int dateMonthInt = stringToInt(dateMonth);
	
	std::string dateMonthString = intToMonth(dateMonthInt-1);

	index++;

	std::string dateYear = "";
	for (;std::isdigit(date[index]);index++){
		dateYear += date[index];
	}

	int dateYearInt = stringToInt(dateYear);

	//exception 1 <= month day <=31
	//exception 1 <= month <= 12
	//exception year
	
	std::string dateString =  dateDay + dateMonthString + " " + dateYear;
	return dateString;
}

std::string UIShow::convertFromTmToStr(tm date){
	//exception 1 <= month day <=31
	//exception 1 <= month <= 12
	//exception year

	std::string dateString = "";

	dateString += intToString(date.tm_mday);
	dateString += intToMonth(date.tm_mon);
	dateString += " ";
	dateString += intToString(date.tm_year + 1900);

	return dateString;
}

int UIShow::countNumDays(tm startDay, tm endDay){
	initializeTime(startDay);
	initializeTime(endDay);
	std::time_t start = std::mktime(&startDay);
	std::time_t end = std::mktime(&endDay);

	// if 70<=tm_year<=1100
	// throw exception

	int dayDifference = std::difftime(end,start)/(60*60*24);

	return dayDifference;
}

void UIShow::initializeTime(tm date){
	date.tm_hour = 0;
	date.tm_min = 0;
	date.tm_sec = 0;
}

bool UIShow::checkIsSingleDate(std::vector<tm> mainDisplayDate){
	assert(mainDisplayDate.size() == 2);

	bool isSingleDate = false;

	if(mainDisplayDate[0].tm_mday == mainDisplayDate[1].tm_mday && mainDisplayDate[0].tm_mon == mainDisplayDate[1].tm_mon && mainDisplayDate[0].tm_year == mainDisplayDate[1].tm_year){
			isSingleDate = true;
		}
	return isSingleDate;
}

std::string UIShow::intToString (int num){
	assert(num>=0);

	std::string outString;
	std::ostringstream oss;
	oss << num;
	return oss.str();
}

int UIShow::stringToInt (std::string str){
	assert(!str.empty());

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







