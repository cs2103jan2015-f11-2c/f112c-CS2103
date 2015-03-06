
#include "Parser.h"
/*
<<<<<<< HEAD
=======

	//CONSTRUCTOR, DESTRUCTOR
>>>>>>> origin/master
*/
Parser::Parser(std::string input)
{
	original = input;
	this->retrieveCategories();
	this->tokenizeOriginalString();
}

Parser::~Parser(void)
{
}

	//GETTERS
Parser::commandType Parser::getCommandType(){
	return typeOfCommand;
}

std::string Parser::getCommand(){
	return command;
}

std::string Parser::getDetails(){
	return details;
}

std::string Parser::getOriginal(){
	return original;
}

Event Parser::getEvent(){
	return tempEventStore;
}

int Parser::getIndex(){
	return index;
}


	//MAIN METHODS
void Parser::tokenizeOriginalString(){
	std::string::size_type strCutIndex = original.find_first_of(" ");
	command = original.substr(0,strCutIndex);
	details = original.substr(strCutIndex+1);

	if(command == "add"){
		this->identifyAddCommand();
	}
	else if(command == "delete"){
		this->setDeleteCommand();
	}
	else if(command == "edit"){
		this->setEditCommand();
		this->identifyDetailToEdit();
	}
	else if(command == "show"){
		this->identifyShowCommand();
	}

	return;
}

void Parser::retrieveCategories(){
	std::string category;
	std::ifstream readCategories;
	readCategories.open("categories.txt");
	while(std::getline(readCategories,category)){
		categories.push_back(category);
	}
	readCategories.close();

	return;
}


	//ADD
//Possible add commands:
// -add [name] (ADDFLOAT) X
// -add [name] @[date] (ADDFULLDAY) X
// -add [name] @[date] [starttime]-[endtime] (ADD) X
// -add [name] @[date] [starttime] (ADDSTART) X
// -add [name] @[startdate]-[enddate] (ADDMULFULLDAYS) X
// -add [name] @[startdate]-[enddate] [starttime-endtime] (ADDMULDAYS) X
// @10feb-11feb 

void Parser::identifyAddCommand(){
	//whenever an information is extracted and there is no preceding information left to extract, it will exit the if.. statements with commandType identified
	if(this->extractEventName()){
		if(this->extractEventDate()){
			if(this->extractEventTime()){
				typeOfCommand = ERROR_;
			}
		}
	}
}


bool Parser::extractEventName(){
	std::string tempName;
	std::string::size_type strCutIndex;
	
	//extract out name of event from details string (any input before @ is taken as part of the event name)
	strCutIndex = details.find_first_of("@");
	tempName = details.substr(0,strCutIndex);
	details = details.substr(strCutIndex+1);
	
	//remove unwanted spaces from name of event before the @ sign
	tempEventStore.setName(tempName.substr(0,tempName.find_last_not_of(" ")+1));
	
	//name information added*

	//return false for ADDFLOAT command to exit if.. statements
	if(strCutIndex == std::string::npos){
		typeOfCommand = ADDFLOAT;
		tempEventStore.setIsFloating(true);
		return false;
	} 

	return true;
}
	
bool Parser::extractEventDate(){	
	std::string tempDate;
	std::string tempStartDate;
	std::string tempEndDate;
	int startday;
	int startmth;
	int startyr;
	int endday;
	int endmth;
	int endyr;
	std::string::size_type strCutIndex;
	std::string::size_type strDateDashIndex;
	
	//extract out date of event (assume no spaces within the entire date input)
	strCutIndex = details.find_first_of(" ");
	tempDate = details.substr(0,strCutIndex);
	details = details.substr(strCutIndex+1);

	//split date into startDate and endDate if it exists
	strDateDashIndex = tempDate.find_first_of("-");
	if(strDateDashIndex != std::string::npos){
		tempStartDate = tempDate.substr(0,strDateDashIndex);
		startday = std::stoi(tempStartDate);
		startmth = mthToInt(tempStartDate.substr(tempStartDate.size()-3));
		startyr = 2015;
		tempEventStore.setStartDate(startday,startmth,startyr);
		tempEndDate = tempDate.substr(strDateDashIndex+1,tempDate.find_last_of(" ")); //remove the dash and spacing at the end if it exists
		endday = std::stoi(tempEndDate);
		endmth = mthToInt(tempEndDate.substr(tempEndDate.size()-3));
		endyr = 2015;
		tempEventStore.setEndDate(endday,endmth,endyr);
	} 
	else {
		tempStartDate = tempDate.substr(0,tempDate.find_last_of(" ")); //remove spacing at the end if it exists
		startday = std::stoi(tempStartDate);
		startmth = mthToInt(tempStartDate.substr(tempStartDate.size()-3));
		startyr = 2015;
		tempEventStore.setStartDate(startday,startmth,startyr);
		tempEventStore.setEndDate(startday,startmth,startyr);
	}

	//startDate and endDate information added*

	//return false for ADDFULLDAY or ADDMULFULLDAYS command to exit if.. statements
	if(strCutIndex == std::string::npos){
		if(strDateDashIndex == std::string::npos){
			typeOfCommand = ADDFULLDAY;
			return false;
		}
		else {
			typeOfCommand = ADDMULFULLDAYS;
			return false;
		}
	}

	return true;
}
	
int Parser::mthToInt(std::string month){
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
		return 0;
	}
}


bool Parser::extractEventTime(){
	std::string tempTime;
	std::string tempStartTime;
	std::string tempEndTime;
	int hour;
	int minute;
	std::string::size_type strCutIndex;
	std::string::size_type strTimeDashIndex;
	
	strCutIndex = details.find_first_of(" ");
	tempTime = details;

	//split time into startTime and endTime if it exists
	strTimeDashIndex = tempTime.find_first_of("-");
	if(strTimeDashIndex != std::string::npos){
		tempStartTime = tempTime.substr(0,strTimeDashIndex);
		timeToInt(hour,minute,tempStartTime);
		tempEventStore.setStartTime(hour,minute);
		tempEndTime = tempTime.substr(strTimeDashIndex+1,tempTime.find_last_of(" ")); //remove the dash and spacing at the end if it exists
		timeToInt(hour,minute,tempEndTime);
		tempEventStore.setEndTime(hour,minute);
	} 
	else {
		tempStartTime = tempTime.substr(0,tempTime.find_last_of(" ")); //remove spacing at the end if it exists
		timeToInt(hour,minute,tempStartTime);
		tempEventStore.setStartTime(hour,minute);
		tempEventStore.setEndTime(hour+1,minute); //DOES NOT TAKE INTO ACCOUNT +1 to NEXT DAY
	}

	//startTime and endTime information added*

	//exit for ADD or ADDSTART or ADDMULDAYS
	if(strCutIndex == std::string::npos){
		if((tempEventStore.getEndDate()).tm_mday == (tempEventStore.getStartDate()).tm_mday){
			if(strTimeDashIndex == std::string::npos){
				typeOfCommand = ADDSTART;
				return false;
			}
			else {
				typeOfCommand = ADD;
				return false;
			}
		}
		else {
			typeOfCommand = ADDMULDAYS;
			return false;
		}
	}

	return true;
}

	//DELETE
//Possible delete commands:
// -delete 1
void Parser::setDeleteCommand(){
	if(index = std::stoi(details)){
		typeOfCommand = DELETE_;
	}
	else {
		typeOfCommand = ERROR_;
	}
	return;
}

void Parser::timeToInt(int& hours, int& minutes, std::string tempTime){
	std::string::size_type strDotIndex;
	std::string strHour;
	std::string strMinute;
	bool afterTwelve = false;

	if(tempTime.find("am") != std::string::npos){
		afterTwelve = false;
	} else if(tempTime.find("pm") != std::string::npos){
		afterTwelve = true;
	}

	strDotIndex = tempTime.find_first_of(".");
	if(strDotIndex != std::string::npos){
		strHour = tempTime.substr(0,strDotIndex);
		strMinute = tempTime.substr(strDotIndex+1);
	} else {
		strHour = tempTime.substr(0,strDotIndex);
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

}

	//EDIT
//Possible edit commands:
// -edit 1 time 1pm-10pm
// -edit 1 date 20 Mar
//?? -edit 1 date time 20 Mar 1pm-10pm
void Parser::setEditCommand(){
	std::string::size_type strCutIndex;
	index = std::stoi(details,&strCutIndex);
	details = details.substr(strCutIndex+1);
	typeOfCommand = EDIT;
	return;
}

void Parser::identifyDetailToEdit(){
/* INCOMPLETE
	std::string detailToEdit;
	detailToEdit = details.substr(0,details.find_first_of(" "));
	details = details.substr(details.find_first_of(" ")+1);

	if(detailToEdit == "name"){
		eventInfo.name = details;
	}
	else if(detailToEdit == "date"){
		eventInfo.date = details;
	}
	else if(detailToEdit == "time"){
		// INCOMPLETE starttime endtime
		eventInfo.time = details;
	}
	else if(detailToEdit == "tag"){
		eventInfo.tags.push_back(details);
	}
	else if(detailToEdit == "description"){
		eventInfo.description = details;
	}
	else {
		typeOfCommand = ERROR;
	}
*/
	return;
}


	//SHOW
//Possible show commands:
// -show Day
// -show School
void Parser::identifyShowCommand(){
	if(details == "day"){  //system categories
		typeOfCommand = SHOWDAY;
	}
	else if(details == "month"){
		typeOfCommand = SHOWMTH;
	}
	else if(details == "year"){
		typeOfCommand = SHOWYR;
	}
	else {  //check if category exists for user categories
		bool userCategoryFound = false;
		for(int i = 0; i < categories.size() && !userCategoryFound; i++){
			if(details == categories[i]){
				userCategoryFound = true;
			}
		}
		if(userCategoryFound){
			typeOfCommand = SHOWUSER;
		} 
		else {
			typeOfCommand = ERROR_;
		}
	}
	return;
//<<<<<<< HEAD
}


//<<<<<<< HEAD



//
//>>>>>>> origin/master


/*
=======
}
>>>>>>> origin/master
*/
