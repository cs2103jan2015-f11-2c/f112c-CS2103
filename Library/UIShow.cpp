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

	//Generate new command
}

std::string UIShow::displayBack(std::string currentMainDisplayLabel){
	if (currentMainDisplayLabel == "Commands"){
		return "Commands";
	}

	if (currentMainDisplayLabel == "Help Introduction"){
		return "help";
	}

	//Generate new command
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


