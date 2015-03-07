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
	}

	else{
		return "0";
		}
}

bool Conversion::stringToBool (std::string checkBool){
	if (checkBool == "1"){
		return true;
	}
	else{
		return false;
	    }
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
	std::string startHr = intToString (tempStartHr);

	int tempStartMin = eventToDisplay.getStartDate().tm_min;
	std::string startMin = intToString (tempStartMin);

	int tempEndDate = eventToDisplay.getEndDate().tm_mday;
	std::string endDate = intToString(tempEndDate);

	int tempEndMonth = eventToDisplay.getEndDate().tm_mon;
	std::string endMonth = intToString(tempEndMonth);

	int tempEndWDay = eventToDisplay.getEndDate().tm_wday;
	std::string endWDay = intToDayOfWeek (tempEndWDay);

	int tempEndHr  = eventToDisplay.getEndDate().tm_hour;
	std::string  endHr = intToString (tempEndHr);

	int tempEndMin = eventToDisplay.getEndDate().tm_min;
	std::string endMin = intToString (tempEndMin);

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
	eventInString += "(" + startWDay + ")";
	eventInString += startDate + " ";


	startMonth + startDay + " " + startHr + startMin + " - " + endMonth + endDay + " " + endHr + endMin + "      " + eventName + "      " + tags + "\n" + description;   



}

Event Conversion::stringToEvent(std::string){
}



int Conversion::monthToInt (std::string month){
	if(month == "jan"){
		return 1;
	} else if(month == "feb"){
		return 2;
	} else if(month == "mar"){
		return 3;
	} else if(month == "apr"){
		return 4;
	} else if(month == "may"){
		return 5;
	} else if(month == "jun"){
		return 6;
	} else if(month == "jul"){
		return 7;
	} else if(month == "aug"){
		return 8;
	} else if(month == "sep"){
		return 9;
	} else if(month == "oct"){
		return 10;
	} else if(month == "nov"){
		return 11;
	} else if(month == "dec"){
		return 12;
	} else {
		return -1;
	}
}

std::string Conversion::intToMonth (int monthInNum){
	if(monthInNum == 1){
		return "jan";
	} else if(monthInNum  == 2){
		return "feb";
	} else if(monthInNum  == 3){
		return "mar";
	} else if(monthInNum  == 4){
		return "apr";
	} else if(monthInNum  == 5){
		return "may";
	} else if(monthInNum  == 6){
		return "jun";
	} else if(monthInNum  == 7){
		return "jul";
	} else if(monthInNum  == 8){
		return "aug";
	} else if(monthInNum  == 9){
		return "sep";
	} else if(monthInNum  == 10){
		return "oct";
	} else if(monthInNum  == 11){
		return "nov";
	} else if(monthInNum  == 12){
		return "dec";
	} else {
		return "Invalid month";
	}
}



std::string Conversion::intToDayOfWeek (int dayInNum){
	if(dayInNum == 0){
		return "sun";
	} else if (dayInNum == 1){
		return "mon";
	} else if (dayInNum == 2){
		return "tues";
	} else if (dayInNum == 3){
		return "wed";
	} else if (dayInNum == 4){
		return "thurs";
	} else if (dayInNum == 5){
		return "fri";
	} else if (dayInNum == 6){
		return "sat";
	} else{
		return "Invalid day";
	}
}

int dayOfWeekToInt (std::string day){
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

}

int Conversion::timeToInt (std::string time){
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