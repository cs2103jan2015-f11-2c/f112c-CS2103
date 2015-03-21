#include "Conversion.h"



const int Conversion::base = 10;

Conversion::Conversion(void)
{
}


Conversion::~Conversion(void)
{
}


std::string Conversion::boolToString(bool isFloatingBool){
	if (isFloatingBool){
		return "1";
	} else{
		return "0";
		}
}

bool Conversion::stringToBool (std::string checkBool){
	if (checkBool == "1"){
		return true;
	} else{
		return false;
	    }
}

string Conversion::tmToString(Event convertEvent){
	std::ostringstream oss;

	oss << convertEvent.getStartDate().tm_year << std::endl << convertEvent.getStartDate().tm_mon << std::endl << convertEvent.getStartDate().tm_mday
		<< std::endl << convertEvent.getStartDate().tm_hour << std::endl << convertEvent.getStartDate().tm_min << std::endl;
	
	oss << convertEvent.getEndDate().tm_year << std::endl << convertEvent.getEndDate().tm_mon << std::endl << convertEvent.getEndDate().tm_mday
		<< std::endl << convertEvent.getEndDate().tm_hour << std::endl << convertEvent.getEndDate().tm_min;

	return oss.str();
}


std::string Conversion::eventToString(Event eventToDisplay){
					
	std::string eventName = eventToDisplay.getName();

	int tempStartDate = eventToDisplay.getStartDate().tm_mday;
    std::string startDate = intToString (tempStartDate);

	int tempStartMonth = eventToDisplay.getStartDate().tm_mon;
	std::string startMonth = intToMonth (tempStartMonth);

	int tempStartWDay = eventToDisplay.getStartDate().tm_wday;
	std::string startWDay = intToDayOfWeek (tempStartWDay);

	int tempStartHr  = eventToDisplay.getStartDate().tm_hour;
	int tempStartMin = eventToDisplay.getStartDate().tm_min;
	int tempStartTime = tempStartHr*100 + tempStartMin;
	std::string startTime = intToTime(tempStartTime);

	int tempEndDate = eventToDisplay.getEndDate().tm_mday;
	std::string endDate = intToString(tempEndDate);

	int tempEndMonth = eventToDisplay.getEndDate().tm_mon;
	std::string endMonth = intToString(tempEndMonth);

	int tempEndWDay = eventToDisplay.getEndDate().tm_wday;
	std::string endWDay = intToDayOfWeek (tempEndWDay);

	int tempEndHr  = eventToDisplay.getEndDate().tm_hour;
	int tempEndMin = eventToDisplay.getEndDate().tm_min;
	int tempEndTime = tempEndHr*100 + tempEndMin;
	std::string endTime = intToTime(tempEndTime);

	std::string description = eventToDisplay.getDescription();

	std::string tags = "";
	vector<std::string> tempTags = eventToDisplay.getTags(); 
					
	for (int i=0; i<tempTags.size(); i++){
		std::string temp = tempTags[i] + " ";
		tags+= temp;
	}

	std::string eventInString = "";
	eventInString += startDate + " ";
	eventInString += startMonth;
	eventInString += "(" + startWDay + ")" + "   ";
	eventInString += startTime;
	eventInString += " - ";
	eventInString += endDate + " ";
	eventInString += endMonth;
	eventInString += "(" + endWDay + ")" + "   ";
	eventInString += endTime;
	eventInString += "		";
	eventInString += eventName;
	eventInString += "		";
	eventInString += tags;
	
	if (description != ""){
	eventInString += "\n";
	eventInString += "*" + description;
	}
	
	eventInString += "\n\n";

	return eventInString;

}

Event Conversion::stringToEvent(std::string){
	Event a;

	return a;
}



int Conversion::monthToInt (std::string month){
	if(month == "jan"){
		return 0;
	} else if(month == "feb"){
		return 1;
	} else if(month == "mar"){
		return 2;
	} else if(month == "apr"){
		return 3;
	} else if(month == "may"){
		return 4;
	} else if(month == "jun"){
		return 5;
	} else if(month == "jul"){
		return 6;
	} else if(month == "aug"){
		return 7;
	} else if(month == "sep"){
		return 8;
	} else if(month == "oct"){
		return 9;
	} else if(month == "nov"){
		return 10;
	} else if(month == "dec"){
		return 11;
	} else {
		return -1;
	}
}

std::string Conversion::intToMonth (int monthInNum){
	if(monthInNum == 0){
		return "Jan";
	} else if(monthInNum  == 1){
		return "Feb";
	} else if(monthInNum  == 2){
		return "Mar";
	} else if(monthInNum  == 3){
		return "Apr";
	} else if(monthInNum  == 4){
		return "May";
	} else if(monthInNum  == 5){
		return "Jun";
	} else if(monthInNum  == 6){
		return "Jul";
	} else if(monthInNum  == 7){
		return "Aug";
	} else if(monthInNum  == 8){
		return "Sep";
	} else if(monthInNum  == 9){
		return "Oct";
	} else if(monthInNum  == 10){
		return "Nov";
	} else if(monthInNum  == 11){
		return "Dec";
	} else {
		return "Invalid month";
	}
}



std::string Conversion::intToDayOfWeek (int dayInNum){
	if(dayInNum == 0){
		return "Sun";
	} else if (dayInNum == 1){
		return "Mon";
	} else if (dayInNum == 2){
		return "Tues";
	} else if (dayInNum == 3){
		return "Wed";
	} else if (dayInNum == 4){
		return "Thurs";
	} else if (dayInNum == 5){
		return "Fri";
	} else if (dayInNum == 6){
		return "Sat";
	} else{
		return "Invalid day";
	}
}

int Conversion::dayOfWeekToInt (std::string day){
	if(day == "sun"){
		return 0;
	} else if (day == "mon"){
		return 1;
	} else if (day == "tues"){
		return 2;
	} else if (day == "wed"){
		return 3;
	} else if (day == "thurs"){
		return 4;
	} else if (day == "fri"){
		return 5;
	} else if (day == "sat"){
		return 6;
	} else{
		return -1;
	}
}

std::string Conversion::intToTime (int timeInInt){
	int hours;
	int minutes;
	bool afterTwelve = false;
	std::ostringstream oss;
	hours = timeInInt/100;
	minutes = timeInInt%100;

	if(hours > 12){
		hours = hours - 12;
		afterTwelve = true;
	}
	
	if(afterTwelve){
		oss << hours << "." << minutes << "pm";
	} else {
		oss << hours << "." << minutes << "am";
	}
	
	return oss.str();
}

int Conversion::timeToInt (std::string time){
	std::string::size_type strDotIndex;
	std::string strHour;
	std::string strMinute;
	int hours;
	int minutes;
	int combinedHoursMinutes;
	bool afterTwelve = false;

	if(time.find("am") != std::string::npos){
		afterTwelve = false;
	} else if(time.find("pm") != std::string::npos){
		afterTwelve = true;
	}

	strDotIndex = time.find_first_of(".");
	if(strDotIndex != std::string::npos){
		strHour = time.substr(0,strDotIndex);
		strMinute = time.substr(strDotIndex+1);
	} else {
		strHour = time.substr(0,strDotIndex);
	}

	if(afterTwelve){
		hours = std::stoi(strHour) + 12;
	} else {
		hours = std::stoi(strHour);
	}

	if(strDotIndex != std::string::npos){
		minutes = std::stoi(strMinute);
	} else {
		minutes = 0;
	}

	combinedHoursMinutes = hours*100 + minutes;
	return combinedHoursMinutes;
}

std::string Conversion::intToString (int num){
	std::string outString;
	std::ostringstream oss;
	oss << num;
	return oss.str();
}
int Conversion::stringToInt (std::string str){
	int outNum;
	std::istringstream in(str);
	in >> outNum;
	return outNum;
}

std::string Conversion::toLowerCase(std::string word){
	for (int i=0;i<word.size();i++){
		 word[i] = tolower(word[i]);
	 }
	return word;
 }

int Conversion::determineLastDayOfMth(int month, int year){
	if (month == 0 || month == 2 || month == 4 || month == 6 || month == 7 || month == 9 || month == 11){
		return 31;
	} else if (month == 3 || month == 5 || month == 8 || month == 10){
		return 30;
	} else if (isLeapYear(year)){
		return 29;
	} else {
		return 28;
	}
}

bool Conversion::isLeapYear(int year){
	if (year % 4 != 0) return false;
	if (year % 400 == 0) return true;
	if (year % 100 == 0) return false;
	return true;
}