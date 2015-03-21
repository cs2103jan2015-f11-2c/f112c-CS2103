#include "ParserProcessor.h"

const std::string ParserProcessor::LOCKUP_USED_INFORMATION = "USED";

const std::string ParserProcessor::PROCESS_ADD_EVENT = "processAddEvent";
const std::string ParserProcessor::PROCESS_EDIT_EVENT = "processEditEvent";
const std::string ParserProcessor::IDENTIFY_EVENT_NAME = "identifyEventName";
const std::string ParserProcessor::IDENTIFY_DATE = "identifyDate";
const std::string ParserProcessor::IDENTIFY_DAY = "identifyDay";
const std::string ParserProcessor::IDENTIFY_TIME = "identifyTime";
const std::string ParserProcessor::ADD_EVENT_CORRECTOR = "addEventCorrector";
const std::string ParserProcessor::EDIT_EVENT_CORRECTOR = "editEventCorrector";
const std::string ParserProcessor::EVENT_MK_TIME_CORRECTOR = "eventMkTimeCorrector";
const std::string ParserProcessor::PROCESS_SHOW_EVENT = "processShowEvent";

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

	keywordDay[0] = "today";
	keywordDay[1] = "tomorrow";
	keywordDay[2] = "mon";
	keywordDay[3] = "tues";
	keywordDay[4] = "wed";
	keywordDay[5] = "thurs";
	keywordDay[6] = "fri";
	keywordDay[7] = "sat";
	keywordDay[8] = "sun";
	keywordDay[9] = "next";

	keywordSpecial[0] = "due";
	keywordSpecial[1] = "to";
	keywordSpecial[2] = "every";

	matchFound = false;
	startDayFound = false;
	endDayFound = false;
	startTimeFound = false;
	endTimeFound = false;
	afterTwelve = false;
	nameFound = false;
	toFound = false;

	oneMatchFound = false;
	twoMatchFound = false;
	systemShowDay = false;
	systemShowWeek = false;
	systemShowMonth = false;
	systemShowFloat = false;
	userShowDay = false;
	userShowRangeOfDays = false;
	userShowMonth = false;
	userShowRangeOfMonths = false;

	time_t t = time(0);
	now = localtime(&t);
}

Event ParserProcessor::processAddEvent(std::vector<std::string> fragmentedWords_){
	logger.logParserEnterFunc(PROCESS_ADD_EVENT);

	fragmentedWords = fragmentedWords_;
	
	try {
		unsigned int i = 0;
		identifyEventName(i);
		if(!nameFound){
			logger.logParserError(ParserExceptions::ERROR_NO_NAME);
			throw ParserExceptions(ParserExceptions::ERROR_NO_NAME);
		}

		for(i = 1; i < fragmentedWords.size(); i++){
			matchFound = identifyDay(i);
			matchFound = identifyDate(i);
			matchFound = identifyTime(i);
			matchFound = false;
		}

		for(i = 0; i < fragmentedWords.size(); i++){
			try {
				auto tempInt = std::stoi(fragmentedWords[i]);
				logger.logParserError(ParserExceptions::ERROR_UNUSED_INTEGERS);
				throw ParserExceptions(ParserExceptions::ERROR_UNUSED_INTEGERS);
			} catch (std::invalid_argument& e){
			}
		}
	} catch(ParserExceptions& e){
		throw e;
	}

	addEventCorrector();
	eventMktimeCorrector();
			
	return tempEventStore;
}

bool ParserProcessor::identifyEventName(int index){
	logger.logParserEnterFunc(IDENTIFY_EVENT_NAME);

	if(fragmentedWords[index].find(";") != std::string::npos){
		tempEventStore.setName(fragmentedWords[index].substr(0,fragmentedWords[index].find_last_of(";")));
		nameFound = true;
	}
	return nameFound;
}

bool ParserProcessor::identifyDay(int index){
	logger.logParserEnterFunc(IDENTIFY_DAY);

	Conversion convertor;
	int tempIndex = 0, tempInt = 0;
	int nowday = 0, nowweekday = 0, numWdaysApart = 0;
	int day = 0, month = 0, year = 0, weekday = 0;
	std::string strDay;

	for (int j = 0; j < NUMBER_OF_KEYWORDS_DAYS-1 && !matchFound; j++){   // NUMBER_OF_KEYWORDS_DAYS-1 because keyword "next" is not going to be searched first
		if(fragmentedWords[index].find(keywordDay[j]) != std::string::npos){
			tempIndex = index;
			strDay = keywordDay[j];
			matchFound = true;
		
			if(strDay == "today"){
				tempEventStore.setStartDate(now->tm_mday,now->tm_mon,now->tm_year);
				tempEventStore.setEndDate(now->tm_mday,now->tm_mon,now->tm_year);
				startDayFound = true;
				endDayFound = true;
			} else if(strDay == "tomorrow"){
				tempEventStore.setStartDate(now->tm_mday+1,now->tm_mon,now->tm_year);
				tempEventStore.setEndDate(now->tm_mday+1,now->tm_mon,now->tm_year);
				startDayFound = true;
				endDayFound = true;
			} else {
				nowweekday = now->tm_wday;
				weekday = convertor.dayOfWeekToInt(strDay);
				if(weekday > nowweekday){
					numWdaysApart = weekday - nowweekday;
				} else if(weekday <= nowweekday){
					numWdaysApart = weekday -(nowweekday - NUMBER_OF_DAYSINAWEEK);
				}
				tempIndex--;
				if(fragmentedWords[tempIndex] == "next"){
					if(weekday < nowweekday){
						numWdaysApart = numWdaysApart + 7;
					}
				}
				if(!startDayFound){
					startDayFound = true;
					tempEventStore.setStartDate(now->tm_mday+numWdaysApart,now->tm_mon,now->tm_year);
				} else if (!endDayFound){
					endDayFound = true;
					tempEventStore.setEndDate(now->tm_mday+numWdaysApart,now->tm_mon,now->tm_year);
				} else {
					throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_DATES);
				}
			}
		}
	}
	return matchFound;
}

bool ParserProcessor::identifyDate(int index){
	logger.logParserEnterFunc(IDENTIFY_DATE);

	Conversion convertor;
	int tempIndex = 0, tempInt = 0;
	int day = 0, month = 0, year = 0;
	std::string strMonth;
	
	for (int j = 0; j < NUMBER_OF_KEYWORDS_MONTHS && !matchFound; j++){
		if(fragmentedWords[index].find(keywordMonths[j]) != std::string::npos){
			tempIndex = index;
			strMonth = keywordMonths[j];
			matchFound = true;
			
			//Extracting day integer
			try {
				auto tempStoi = std::stoi(fragmentedWords[tempIndex]);
				fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
				tempInt = tempStoi;
			} catch (const std::invalid_argument& e){
				tempIndex--;
				if(tempIndex >= 0){
					try {
						auto tempStoi = std::stoi(fragmentedWords[tempIndex]);
						fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
						tempInt = tempStoi;
					} catch (std::invalid_argument& e){
						logger.logParserError(ParserExceptions::ERROR_MISSING_DAY);
						throw ParserExceptions(ParserExceptions::ERROR_MISSING_DAY);
					}
				}
			} 
			
			//Registering day, month, year
			year = now->tm_year;
			month = convertor.monthToInt(strMonth);
			if((tempInt > convertor.determineLastDayOfMth(month,year)) || (tempInt < 1)){
				logger.logParserError(ParserExceptions::ERROR_UNKNOWN_DATE);
				throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_DATE);
			}
			day = tempInt;
			
			//Check for 'to'
			tempIndex--;
			if(tempIndex >= 0){
				if(fragmentedWords[tempIndex] == "to"){
					tempIndex--;
					if(tempIndex >= 0){
						try {
							auto tempStoi = std::stoi(fragmentedWords[tempIndex]);
							fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
							tempInt = tempStoi;
							toFound = true;
						} catch (std::invalid_argument& e){
						}
					}
				}
			}
			
			//Creating start and end date in Event
			if(toFound){
				startDayFound = true;
				tempEventStore.setStartDate(tempInt,month,year);
				endDayFound = true;
				tempEventStore.setEndDate(day,month,year);
			} else if(!startDayFound){
				startDayFound = true;
				tempEventStore.setStartDate(day,month,year);
			} else if(!endDayFound){
				endDayFound = true;
				tempEventStore.setEndDate(day,month,year);
			} else {
				logger.logParserError(ParserExceptions::ERROR_TOO_MANY_DATES);
				throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_DATES);
			}
		}
	}
	return matchFound;
}

bool ParserProcessor::identifyTime(int index){
	logger.logParserEnterFunc(IDENTIFY_TIME);

	int tempIndex = 0, tempInt = 0;
	int hour = 0, minute = 0;
	int toHour = 0, toMinute = 0;
	
	for (int j = 0; j < NUMBER_OF_KEYWORDS_TIME && !matchFound; j++){
		if(fragmentedWords[index].find(keywordTime[j]) != std::string::npos){
			tempIndex = index;
			if(keywordTime[j] == "pm"){
				afterTwelve = true;
			}
			matchFound = true;
			
			//Extracting hour and minute integers
			try {
				auto tempStoi = std::stoi(fragmentedWords[tempIndex]);
				fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
				tempInt = tempStoi;
			} catch (const std::invalid_argument& e){
				tempIndex--;
				if(tempIndex >= 0){
					try {
						auto tempStoi = std::stoi(fragmentedWords[tempIndex]);
						fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
						tempInt = tempStoi;
					} catch (std::invalid_argument& e){
						logger.logParserError(ParserExceptions::ERROR_MISSING_HOUR_MIN);
						throw ParserExceptions(ParserExceptions::ERROR_MISSING_HOUR_MIN);
					}
				}
			} 
			
			//Registering hour and minute
			if(tempInt >= 100){
				minute = tempInt%100;
				if(minute > 60){
					logger.logParserError(ParserExceptions::ERROR_UNKNOWN_MINUTE);
					throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_MINUTE);
				}
				hour = tempInt/100;
				if(hour > 12){
					logger.logParserError(ParserExceptions::ERROR_UNKNOWN_HOUR);
					throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_HOUR);
				}
				if(afterTwelve){
					if (hour < 12){
						hour = hour + 12;
					}
				} else {
					if (hour == 12){
						hour = 0;
					}
				}
			} else if(tempInt < 100){
				tempIndex--;
				if(tempIndex >= 0){
					try {
						hour = std::stoi(fragmentedWords[tempIndex]);
						fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
						minute = tempInt;
						tempIndex--;
					} catch (const std::invalid_argument& e){
						hour = tempInt;
						minute = 0;
					}
					if(minute > 60){
						logger.logParserError(ParserExceptions::ERROR_UNKNOWN_MINUTE);
						throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_MINUTE);
					}
					if(hour > 12){
						logger.logParserError(ParserExceptions::ERROR_UNKNOWN_HOUR);
						throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_HOUR);
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
				}
			}
			
			//Check for 'to'
			if(tempIndex >= 0){
				if(fragmentedWords[tempIndex] == "to"){
					tempIndex--;
					if(tempIndex >= 0){
						try {
							auto tempStoi = std::stoi(fragmentedWords[tempIndex]);
							fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
							tempInt = tempStoi;
							toFound = true;

							if(tempInt >= 100){
								toMinute = tempInt%100;
								if(toMinute > 60){
									logger.logParserError(ParserExceptions::ERROR_UNKNOWN_MINUTE);
									throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_MINUTE);
								}
								toHour = tempInt/100;
								if(toHour > 12){
									logger.logParserError(ParserExceptions::ERROR_UNKNOWN_HOUR);
									throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_HOUR);
								}
								if(afterTwelve){
									if (toHour < 12){
										toHour = toHour + 12;
									}
								} else {
									if (toHour == 12){
										toHour = 0;
									}
								}
							} else if(tempInt < 100){
								tempIndex--;
								if(tempIndex >= 0){
									try {
										toHour = std::stoi(fragmentedWords[tempIndex]);
										fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
										toMinute = tempInt;
									} catch (const std::invalid_argument& e){
										toHour = tempInt;
										toMinute = 0;
									}
									if(toMinute > 60){
										logger.logParserError(ParserExceptions::ERROR_UNKNOWN_MINUTE);
										throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_MINUTE);
									}
									if(toHour > 12){
										logger.logParserError(ParserExceptions::ERROR_UNKNOWN_HOUR);
										throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_HOUR);
									}
									if(afterTwelve){
										if(toHour < 12){
											toHour = toHour + 12;
										}
									} else {
										if(toHour == 12){
											toHour = 0;
										}
									}
								}
							}
						} catch (std::invalid_argument& e){
						}
					}
				}
			}
			
			//Creating start time and end time
			if(toFound){
				startTimeFound = true;
				tempEventStore.setStartTime(toHour,toMinute);
				endTimeFound = true;
				tempEventStore.setEndTime(hour,minute);
			} else if(!startTimeFound){
				startTimeFound = true;
				tempEventStore.setStartTime(hour,minute);
			} else if(!endTimeFound){				
				endTimeFound = true;
				tempEventStore.setEndTime(hour,minute);
			} else {
				logger.logParserError(ParserExceptions::ERROR_TOO_MANY_TIMES);
				throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_TIMES);
			}
		}
	}
	return matchFound;
}

void ParserProcessor::addEventCorrector(){
	logger.logParserEnterFunc(ADD_EVENT_CORRECTOR);

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
	logger.logParserEnterFunc(EVENT_MK_TIME_CORRECTOR);

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
	logger.logParserEnterFunc(PROCESS_EDIT_EVENT);

	fragmentedWords = fragmentedWords_;
	
	fragmentedWords.insert(fragmentedWords.begin(),LOCKUP_USED_INFORMATION);

	try {
		unsigned int i;
		for(i = 0; i < fragmentedWords.size(); i++){
			if(!nameFound){
				matchFound = identifyEventName(i);
			}
			matchFound = identifyDate(i);
			matchFound = identifyTime(i);
			matchFound = false;
		}

		for(i = 0; i < fragmentedWords.size(); i++){
			try {
				auto tempInt = std::stoi(fragmentedWords[i]);
				logger.logParserError(ParserExceptions::ERROR_UNUSED_INTEGERS);
				throw ParserExceptions(ParserExceptions::ERROR_UNUSED_INTEGERS);
			} catch (std::invalid_argument& e){
			}
		}
	} catch (ParserExceptions& e){
		throw e;
	}

	editEventCorrector();

	return tempEventStore;
}

void ParserProcessor::editEventCorrector(){
	logger.logParserEnterFunc(EDIT_EVENT_CORRECTOR);

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
	logger.logParserEnterFunc(PROCESS_SHOW_EVENT);

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
		tempEventStore.setEndDate(convertor.determineLastDayOfMth(month,year),month,year);
		systemShowMonth = true;
	} else if(firstWord == "floating"){
		tempEventStore.setIsFloating(true);
		systemShowFloat = true;
	}

	//check if it is user based Show (e.g. 14 apr, april, month/ april, week/ 14apr, 17 apr to 18 apr, apr to may)
	unsigned int i = 0;
	int tempi = 0; 
	int j = 0;
	if(systemShowDay || systemShowWeek || systemShowMonth || systemShowFloat){
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
				} else if(!twoMatchFound){
					twoMatchFound = true;
				} else {
					logger.logParserError(ParserExceptions::ERROR_TOO_MANY_DATES);
					throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_DATES);
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
					try {
						auto tempStoi = std::stoi(fragmentedWords[tempi]);
						fragmentedWords[tempi] = LOCKUP_USED_INFORMATION;
						tempInt = tempStoi;
						if (!twoMatchFound){
							userShowDay = true;
						} else {
							userShowRangeOfDays = true;
							userShowDay = false;
						}
					} catch(std::invalid_argument& e){
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

			month = convertor.monthToInt(strMonth);
			if(userShowDay || userShowRangeOfDays){
				if((tempInt > convertor.determineLastDayOfMth(month,year)) || (tempInt < 1)){
					logger.logParserError(ParserExceptions::ERROR_UNKNOWN_DATE);
					throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_DATE);
				}
			}
			day = tempInt;

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
					tempEventStore.setEndDate(convertor.determineLastDayOfMth(month,year),month,year);
				} else {
					tempEventStore.setStartDate(1,month,year);
					tempEventStore.setEndDate(convertor.determineLastDayOfMth(month,year),month,year);
				}
			}
			if(userShowRangeOfMonths){
				tempEventStore.setEndDate(convertor.determineLastDayOfMth(month,year),month,year);
			}

		}
		matchFound = false;
	}

	for(i = 0; i < fragmentedWords.size(); i++){
		try {
			auto tempInt = std::stoi(fragmentedWords[i]);
			logger.logParserError(ParserExceptions::ERROR_UNUSED_INTEGERS);
			throw ParserExceptions(ParserExceptions::ERROR_UNUSED_INTEGERS);
		} catch (std::invalid_argument& e){
		}
	}

	//correcting dates 
	tempEventStore.setStartTime(0,0);
	tempEventStore.setEndTime(0,0);
	eventMktimeCorrector();

	return tempEventStore;
}
