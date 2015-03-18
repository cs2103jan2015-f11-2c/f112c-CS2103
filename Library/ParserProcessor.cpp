#include "ParserProcessor.h"

const std::string ParserProcessor::LOCKUP_USED_INFORMATION = "USED";

ParserProcessor::ParserProcessor(){
	keywordMonths[0] = "jan";
	keywordMonths[1] = "feb";
	keywordMonths[2] = "mar";
	keywordMonths[3] = "apr";
	keywordMonths[4] = "may";
	keywordMonths[5] = "jun";
	keywordMonths[6] = "jul";
	keywordMonths[7] = "aug";
	keywordMonths[8] = "sep";
	keywordMonths[9] = "oct";
	keywordMonths[10] = "nov";
	keywordMonths[11] = "dec";
	
	keywordTime[0] = "am";
	keywordTime[1] = "pm";

	matchFound = false;
	startDayFound = false;
	endDayFound = false;
	startTimeFound = false;
	endTimeFound = false;
	afterTwelve = false;
	nameFound = false;

	oneMatchFound = false;
	twoMatchFound = false;
	systemShowDay = false;
	systemShowWeek = false;
	systemShowMonth = false;
	userShowDay = false;
	userShowRangeOfDays = false;
	userShowMonth = false;
	userShowRangeOfMonths = false;

	time_t t = time(0);
	now = localtime(&t);
}

Event ParserProcessor::processAddEvent(std::vector<std::string> fragmentedWords_){
	fragmentedWords = fragmentedWords_;

	for(unsigned int i = 0; i < fragmentedWords.size(); i++){
		if(!nameFound){
			matchFound = identifyEventName(i);
		}
		matchFound = identifyDate(i);
		matchFound = identifyTime(i);
		matchFound = false;
	}

	addEventCorrector();
	eventMktimeCorrector();

	return tempEventStore;
}

bool ParserProcessor::identifyEventName(int index){
	if(fragmentedWords[index].find(";") != std::string::npos){
		tempEventStore.setName(fragmentedWords[index].substr(0,fragmentedWords[index].find_last_of(";")));
		nameFound = true;
		matchFound = true;
	}
	return matchFound;
}

bool ParserProcessor::identifyDate(int index){
	Conversion convertor;
	int tempIndex = 0, tempInt = 0;
	int day = 0, month = 0, year = 0;
	std::string strMonth;
	
	for (int j = 0; j < NUMBER_OF_KEYWORDS_MONTHS && !matchFound; j++){
		if(fragmentedWords[index].find(keywordMonths[j]) != std::string::npos){
			tempIndex = index;
			strMonth = keywordMonths[j];
			matchFound = true;
			
			try {
				auto tempStoi = std::stoi(fragmentedWords[tempIndex]);
				fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
				tempInt = tempStoi;
			} catch (const std::invalid_argument& e){
				tempIndex--;
				auto tempStoi = std::stoi(fragmentedWords[tempIndex]);
				fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
				tempInt = tempStoi;
			} 
			
			day = tempInt;
			month = convertor.monthToInt(strMonth);
			year = now->tm_year;
			
			if(!startDayFound){
				startDayFound = true;
				tempEventStore.setStartDate(day,month,year);
			} else {
				endDayFound = true;
				tempEventStore.setEndDate(day,month,year);
			}
		}
	}
	return matchFound;
}

bool ParserProcessor::identifyTime(int index){
	int tempIndex = 0, tempInt = 0;
	int hour = 0, minute = 0;
	
	for (int j = 0; j < NUMBER_OF_KEYWORDS_TIME && !matchFound; j++){
		if(fragmentedWords[index].find(keywordTime[j]) != std::string::npos){
			tempIndex = index;
			if(keywordTime[j] == "pm"){
				afterTwelve = true;
			}
			matchFound = true;
	
			try {
				auto tempStoi = std::stoi(fragmentedWords[tempIndex]);
				fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
				tempInt = tempStoi;
			} catch (const std::invalid_argument& e){
				tempIndex--;
				auto tempStoi = std::stoi(fragmentedWords[tempIndex]);
				fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
				tempInt = tempStoi;
			} 
			
			if(tempInt >= 100){
				minute = tempInt%100;
				hour = tempInt/100;
				if(afterTwelve){
					if (hour < 12){
						hour = hour + 12;
					}
				} else {
					if (hour == 12){
						hour = 0;
					}
				}
				if(!startTimeFound){
					tempEventStore.setStartTime(hour,minute);
					startTimeFound = true;
				} else {
					tempEventStore.setEndTime(hour,minute);
					endTimeFound = true;
				}
			} else if(tempInt < 100){
				tempIndex--;
				try {
					hour = std::stoi(fragmentedWords[tempIndex]);
					fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
					minute = tempInt;
				} catch (const std::invalid_argument& e){
					hour = tempInt;
					minute = 0;
				} 
				if(afterTwelve){
					if(hour < 12){
						hour = hour + 12;
					}
				} else {
					if(hour == 12){
						hour = 0;
					}
				}
				if(!startTimeFound){
					startTimeFound = true;
					tempEventStore.setStartTime(hour,minute);
				} else {
					endTimeFound = true;
					tempEventStore.setEndTime(hour,minute);
				}
			}
		}
	}
	return matchFound;
}

void ParserProcessor::addEventCorrector(){
	int day = 0, month = 0, year = 0;
	int hour = 0, minute = 0;

	if(!startDayFound && !startTimeFound){
		tempEventStore.setIsFloating(true);
	}
	if(startDayFound && !startTimeFound){
		tempEventStore.setStartTime(0,0);
		tempEventStore.setEndTime(23,59);
	}
	if(!startDayFound && startTimeFound){
		day = now->tm_mday;
		month = now->tm_mon;
		year = now->tm_year;
		tempEventStore.setStartDate(day,month,year);
		tempEventStore.setEndDate(day,month,year);
	}
	if(!endDayFound){
		struct tm tempTime = tempEventStore.getStartDate();
		tempEventStore.setEndDate(tempTime.tm_mday,tempTime.tm_mon,tempTime.tm_year);
	}
	if(startTimeFound && !endTimeFound){
		struct tm tempTime = tempEventStore.getStartDate();
		tempEventStore.setEndTime((tempTime.tm_hour)+1,tempTime.tm_min);
	}
	if(endDayFound && !endTimeFound){
		tempEventStore.setEndTime(23,59);
	}
}

void ParserProcessor::eventMktimeCorrector(){
	struct tm* temptmPtr;
	temptmPtr = &tempEventStore.getStartDate();
	mktime(temptmPtr);
	tempEventStore.setStartDate(temptmPtr->tm_mday,temptmPtr->tm_mon,temptmPtr->tm_year);
	tempEventStore.setStartTime(temptmPtr->tm_hour,temptmPtr->tm_min);
	temptmPtr = &tempEventStore.getEndDate();
	mktime(temptmPtr);
	tempEventStore.setEndDate(temptmPtr->tm_mday,temptmPtr->tm_mon,temptmPtr->tm_year);
	tempEventStore.setEndTime(temptmPtr->tm_hour,temptmPtr->tm_min);
}

Event ParserProcessor::processEditEvent(std::vector<std::string> fragmentedWords_){
	fragmentedWords = fragmentedWords_;
	
	fragmentedWords.insert(fragmentedWords.begin(),LOCKUP_USED_INFORMATION);

	for(unsigned int i = 0; i < fragmentedWords.size(); i++){
		if(!nameFound){
			matchFound = identifyEventName(i);
		}
		matchFound = identifyDate(i);
		matchFound = identifyTime(i);
		matchFound = false;
	}

	editEventCorrector();

	return tempEventStore;
}

void ParserProcessor::editEventCorrector(){
	int day = 0, month = 0, year = 0;
	int hour = 0, minute = 0;

	if(startDayFound && !endDayFound){
		struct tm tempTime = tempEventStore.getStartDate();
		tempEventStore.setEndDate(tempTime.tm_mday,tempTime.tm_mon,tempTime.tm_year);
	}
	if(startTimeFound && !endTimeFound){
		struct tm tempTime = tempEventStore.getStartDate();
		tempEventStore.setEndTime((tempTime.tm_hour)+1,tempTime.tm_min);
	}

	eventMktimeCorrector();

	if(!nameFound){
		tempEventStore.setName("");
	}
	if(!startDayFound){
		tempEventStore.setStartDate(100,100,100);
		tempEventStore.setEndDate(100,100,100);
	}
	if(!startTimeFound){
		tempEventStore.setStartTime(100,100);
		tempEventStore.setEndTime(100,100);
	}
}

Event ParserProcessor::processShowEvent(std::vector<std::string> fragmentedWords_){
	fragmentedWords = fragmentedWords_;
	Conversion convertor;
	std::string strMonth;
	int tempInt = 0;
	int day = 0, month = 0, year = 0, weekday = 0;

	//check for system based Show (e.g. Today, Week, Month)
	int daysToEndWeek = 0;
	day = now->tm_mday;
	month = now->tm_mon;
	year = now->tm_year;
	
	std::string firstWord = fragmentedWords[0];
	if (firstWord == "today"){
		tempEventStore.setStartDate(day,month,year);
		tempEventStore.setEndDate(day,month,year);
		systemShowDay = true;
	} else if (firstWord == "week"){
		weekday = now->tm_wday;
		daysToEndWeek = 6 - weekday;
		tempEventStore.setStartDate(day,month,year);
		tempEventStore.setEndDate(day+daysToEndWeek,month,year);
		systemShowWeek = true;
	} else if(firstWord == "month"){
		tempEventStore.setStartDate(day,month,year);
		tempEventStore.setEndDate(determineLastDayOfMth(month,year),month,year);
		systemShowMonth = true;
	}

	//check if it is user based Show (e.g. 14 apr, april, month/ april, week/ 14apr, 17 apr to 18 apr, apr to may)
	int i = 0, tempi = 0, j = 0;
	if(systemShowDay || systemShowWeek || systemShowMonth){
		tempi++;
	}
	for(i = tempi; i < fragmentedWords.size(); i++){
		//finding any string of a month within the fragmentedWords vector
		//record number of matches found, if two matches are found, a range of days/range of months is requested to be shown
		for (j = 0; j < NUMBER_OF_KEYWORDS_MONTHS && !matchFound; j++){
			if(fragmentedWords[i].find(keywordMonths[j]) != std::string::npos){
				matchFound = true;
				if(!oneMatchFound){
					oneMatchFound = true;
				} else {
					twoMatchFound = true;
				}
				tempi = i;
				strMonth = keywordMonths[j];
			}
		}
		
		if(matchFound){
			try {
				//check if current string contains integer value as day
				auto tempStoi = std::stoi(fragmentedWords[tempi]);
				fragmentedWords[tempi] = LOCKUP_USED_INFORMATION;
				tempInt = tempStoi;
				if (!twoMatchFound){
					userShowDay = true;
				} else {
					userShowRangeOfDays = true;
					userShowDay = false;
				}
			} catch (const std::invalid_argument& e){
				//no integer found, check if there are any possibility of the day input before the month
				//if no possibility, implies showMonth. if theres a day, implies showDay or showWeek depending
				//whether systemShowDay or systemShowWeek is true
				tempi--;
				if(tempi >= 0){
					if (isdigit((fragmentedWords[tempi])[0])){
						auto tempStoi = std::stoi(fragmentedWords[tempi]);
						fragmentedWords[tempi] = LOCKUP_USED_INFORMATION;
						tempInt = tempStoi;
						if (!twoMatchFound){
							userShowDay = true;
						} else {
							userShowRangeOfDays = true;
							userShowDay = false;
						}
					} else {
						if (!twoMatchFound){
							userShowMonth = true;
						} else {
							userShowRangeOfMonths = true;
							userShowMonth = false;
						}
					}
				} else {
					if (!twoMatchFound){
						userShowMonth = true;
					} else {
						userShowRangeOfMonths = true;
						userShowMonth = false;
					}
				}
			}

			day = tempInt;
			month = convertor.monthToInt(strMonth);

			//create startDate and endDate based on what Show is found
			if(!systemShowWeek){
				if(userShowDay){
					tempEventStore.setStartDate(day,month,year);
					tempEventStore.setEndDate(day,month,year);
				} 
				if(userShowRangeOfDays){
					tempEventStore.setEndDate(day,month,year);
				}
			} else {
				time_t t = time(0);
				struct tm* dateWithinWeek = localtime(&t);
				dateWithinWeek->tm_mday = day;
				dateWithinWeek->tm_mon = month;
				dateWithinWeek->tm_year = year;
				mktime(dateWithinWeek);
				weekday = dateWithinWeek->tm_wday;
				daysToEndWeek = 6 - weekday;
				if(userShowDay){
					tempEventStore.setStartDate(day-weekday,month,year);
					tempEventStore.setEndDate(day+daysToEndWeek,month,year);
				} 
				if(userShowRangeOfDays){
					tempEventStore.setEndDate(day+daysToEndWeek,month,year);
				}
			}

			if(userShowMonth){
				if(month == now->tm_mon){
					tempEventStore.setStartDate(now->tm_mday,month,year);
					tempEventStore.setEndDate(determineLastDayOfMth(month,year),month,year);
				} else {
					tempEventStore.setStartDate(1,month,year);
					tempEventStore.setEndDate(determineLastDayOfMth(month,year),month,year);
				}
			}
			if(userShowRangeOfMonths){
				tempEventStore.setEndDate(determineLastDayOfMth(month,year),month,year);
			}

		}
		matchFound = false;
	}

	//correcting dates 
	tempEventStore.setStartTime(0,0);
	tempEventStore.setEndTime(0,0);
	eventMktimeCorrector();

	return tempEventStore;
}


int ParserProcessor::determineLastDayOfMth(int month, int year){
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

bool ParserProcessor::isLeapYear(int year){
	if (year % 4 != 0) return false;
	if (year % 400 == 0) return true;
	if (year % 100 == 0) return false;
	return true;
}
