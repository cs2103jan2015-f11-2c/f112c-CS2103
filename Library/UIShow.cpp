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

std::string UIShow::displayNext(std::string currentMainDisplayLabel){
	if (currentMainDisplayLabel == "Commands"){
		return "Commands";
	}

	if (currentMainDisplayLabel == "Help Introduction"){
		return "help";
	}
	/*
	//function to check whether it is single or multiple day

	bool isSingleDate = checkIsSingleDate(currentMainDisplayLabel);
	if ( isSingleDate ){

		// Forward by 1 day
	} else {
		// Count number of days 
		// Forward by this no. of days
	}
	*/
	
}



std::string UIShow::displayBack(std::string currentMainDisplayLabel){
	if (currentMainDisplayLabel == "Commands"){
		return "Commands";
	}

	if (currentMainDisplayLabel == "Help Introduction"){
		return "help";
	}
	/*
	//function to check whether it is single or multiple day

	bool isSingleDate = checkIsSingleDate(currentMainDisplayLabel);
	if ( isSingleDate ){

		// backward by 1 day
	} else {
		// Count number of days 
		// backward by this no. of days
	}
	
}

tm UIShow::shiftDate(tm date, int numDaysToShift){
	time_t t = time(0);
	struct tm* temp = localtime(&t);
	*/

}


bool UIShow::checkIsSingleDate(std::string currentMainDisplayLabel){
	bool isSingleDate = false;

	for (int i=0; i<currentMainDisplayLabel.size() && !isSingleDate; i++){
		if(currentMainDisplayLabel[i] == '-'){
			isSingleDate = true;
		}
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

/*
time_t t = time(0);
	struct tm* temp = localtime(&t);
	temp->tm_mday = wantedEventDates[i].tm_mday;
			temp->tm_mon = wantedEventDates[i].tm_mon;
			temp->tm_year = wantedEventDates[i].tm_year;
			mktime(temp);
			*/