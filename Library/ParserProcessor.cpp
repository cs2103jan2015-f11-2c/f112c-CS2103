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
}

Event ParserProcessor::processAddEvent(std::vector<std::string> fragmentedWords){
	Conversion convertor;
	Event tempEventStore;
	std::string strMonth;
	int tempInt;
	int day = 0, month = 0, year = 0, hour = 0, minute = 0;
	bool matchFound = false;
	bool startDayFound = false;
	bool endDayFound = false;
	bool startTimeFound = false;
	bool endTimeFound = false;
	bool afterTwelve = false;
	bool nameFound = false;
	
	int tempi = 0;
	unsigned int i;
	//finding all the names of event
	for(i = 0; i < fragmentedWords.size() && !nameFound; i++){
		if(fragmentedWords[i].find(";") != std::string::npos){
			tempEventStore.setName(fragmentedWords[i].substr(0,fragmentedWords[i].find_last_of(";")));
			tempi++;
			nameFound = true;
		}
	}

	int j;
	for(i = tempi; i < fragmentedWords.size(); i++){
		//finding date
		for (j = 0; j < NUMBER_OF_KEYWORDS_MONTHS && !matchFound; j++){
			if(fragmentedWords[i].find(keywordMonths[j]) != std::string::npos){
				matchFound = true;
				tempi = i;
				strMonth = keywordMonths[j];
			}
		}
		
		if(matchFound){
			try {
				auto tempStoi = std::stoi(fragmentedWords[tempi]);
				fragmentedWords[tempi] = LOCKUP_USED_INFORMATION;
				tempInt = tempStoi;
			} catch (const std::invalid_argument& e){
				tempi--;
				auto tempStoi = std::stoi(fragmentedWords[tempi]);
				fragmentedWords[tempi] = LOCKUP_USED_INFORMATION;
				tempInt = tempStoi;
			} 
			day = tempInt;
			month = convertor.monthToInt(strMonth);
			year = 2015-1900;
			if(!startDayFound){
				startDayFound = true;
				tempEventStore.setStartDate(day,month,year);
			} else {
				endDayFound = true;
				tempEventStore.setEndDate(day,month,year);
			}
		}
		matchFound = false;

		//finding time
		for (j = 0; j < NUMBER_OF_KEYWORDS_TIME && !matchFound; j++){
			if(fragmentedWords[i].find(keywordTime[j]) != std::string::npos){
				matchFound = true;
				tempi = i;
				if(keywordTime[j] == "pm"){
					afterTwelve = true;
				}
			}
		}

		if(matchFound){
			try {
				auto tempStoi = std::stoi(fragmentedWords[tempi]);
				fragmentedWords[tempi] = LOCKUP_USED_INFORMATION;
				tempInt = tempStoi;
			} catch (const std::invalid_argument& e){
				tempi--;
				auto tempStoi = std::stoi(fragmentedWords[tempi]);
				fragmentedWords[tempi] = LOCKUP_USED_INFORMATION;
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
				tempi--;
				try {
					hour = std::stoi(fragmentedWords[tempi]);
					fragmentedWords[tempi] = LOCKUP_USED_INFORMATION;
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
		matchFound = false;
	}

	if(!startDayFound && !startTimeFound){
		tempEventStore.setIsFloating(true);
	}
	if(startDayFound && !startTimeFound){
		tempEventStore.setStartTime(0,0);
		tempEventStore.setEndTime(23,59);
	}
	if(!startDayFound && startTimeFound){
		time_t t = time(0);
		struct tm* now = localtime(&t);
		day = now->tm_mday;
		month = now->tm_mon;
		year = now->tm_year;
		tempEventStore.setStartDate(day,month,year);
		tempEventStore.setEndDate(day,month,year);
	}
	if(!endDayFound){
		tempEventStore.setEndDate(day,month,year);
	}
	if(!endTimeFound){
		tempEventStore.setEndTime(hour+1,minute);
	}
	if(endDayFound && !endTimeFound){
		tempEventStore.setEndTime(23,59);
	}

	struct tm* temptmPtr;
	temptmPtr = &tempEventStore.getStartDate();
	mktime(temptmPtr);
	tempEventStore.setStartDate(temptmPtr->tm_mday,temptmPtr->tm_mon,temptmPtr->tm_year);
	tempEventStore.setStartTime(temptmPtr->tm_hour,temptmPtr->tm_min);
	temptmPtr = &tempEventStore.getEndDate();
	mktime(temptmPtr);
	tempEventStore.setEndDate(temptmPtr->tm_mday,temptmPtr->tm_mon,temptmPtr->tm_year);
	tempEventStore.setEndTime(temptmPtr->tm_hour,temptmPtr->tm_min);

	return tempEventStore;
}

Event ParserProcessor::processEditEvent(std::vector<std::string> fragmentedWords){
	Conversion convertor;
	Event tempEventStore;
	std::string strMonth;
	int tempInt;
	int day = 0, month = 0, year = 0, hour = 0, minute = 0;
	bool matchFound = false;
	bool startDayFound = false;
	bool endDayFound = false;
	bool startTimeFound = false;
	bool endTimeFound = false;
	bool afterTwelve = false;
	bool nameFound = false;
	
	fragmentedWords.insert(fragmentedWords.begin(),LOCKUP_USED_INFORMATION);

	int tempi = 0;
	unsigned int i;
	//finding all the names of event
	for(i = 0; i < fragmentedWords.size() && !nameFound; i++){
		if(fragmentedWords[i].find(";") != std::string::npos){
			tempEventStore.setName(fragmentedWords[i].substr(0,fragmentedWords[i].find_last_of(";")));
			tempi++;
			nameFound = true;
		}
	}

	int j;
	for(i = tempi; i < fragmentedWords.size(); i++){
		//finding date
		for (j = 0; j < NUMBER_OF_KEYWORDS_MONTHS && !matchFound; j++){
			if(fragmentedWords[i].find(keywordMonths[j]) != std::string::npos){
				matchFound = true;
				tempi = i;
				strMonth = keywordMonths[j];
			}
		}
		
		if(matchFound){
			try {
				auto tempStoi = std::stoi(fragmentedWords[tempi]);
				fragmentedWords[tempi] = LOCKUP_USED_INFORMATION;
				tempInt = tempStoi;
			} catch (const std::invalid_argument& e){
				tempi--;
				auto tempStoi = std::stoi(fragmentedWords[tempi]);
				fragmentedWords[tempi] = LOCKUP_USED_INFORMATION;
				tempInt = tempStoi;
			} 
			day = tempInt;
			month = convertor.monthToInt(strMonth);
			year = 2015-1900;
			if(!startDayFound){
				startDayFound = true;
				tempEventStore.setStartDate(day,month,year);
			} else {
				endDayFound = true;
				tempEventStore.setEndDate(day,month,year);
			}
		}
		matchFound = false;

		//finding time
		for (j = 0; j < NUMBER_OF_KEYWORDS_TIME && !matchFound; j++){
			if(fragmentedWords[i].find(keywordTime[j]) != std::string::npos){
				matchFound = true;
				tempi = i;
				if(keywordTime[j] == "pm"){
					afterTwelve = true;
				}
			}
		}

		if(matchFound){
			try {
				auto tempStoi = std::stoi(fragmentedWords[tempi]);
				fragmentedWords[tempi] = LOCKUP_USED_INFORMATION;
				tempInt = tempStoi;
			} catch (const std::invalid_argument& e){
				tempi--;
				auto tempStoi = std::stoi(fragmentedWords[tempi]);
				fragmentedWords[tempi] = LOCKUP_USED_INFORMATION;
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
				tempi--;
				try {
					hour = std::stoi(fragmentedWords[tempi]);
					fragmentedWords[tempi] = LOCKUP_USED_INFORMATION;
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
		matchFound = false;
	}
	if(!startDayFound && !startTimeFound){
		tempEventStore.setIsFloating(true);
	}
	if(startDayFound && !endDayFound){
		tempEventStore.setEndDate(day,month,year);
	}
	if(startTimeFound && !endTimeFound){
		tempEventStore.setEndTime(hour+1,minute);
	}
	if(!nameFound){
		tempEventStore.setName("");
	}
	struct tm* temptmPtr;
	temptmPtr = &tempEventStore.getStartDate();
	mktime(temptmPtr);
	tempEventStore.setStartDate(temptmPtr->tm_mday,temptmPtr->tm_mon,temptmPtr->tm_year);
	tempEventStore.setStartTime(temptmPtr->tm_hour,temptmPtr->tm_min);
	temptmPtr = &tempEventStore.getEndDate();
	mktime(temptmPtr);
	tempEventStore.setEndDate(temptmPtr->tm_mday,temptmPtr->tm_mon,temptmPtr->tm_year);
	tempEventStore.setEndTime(temptmPtr->tm_hour,temptmPtr->tm_min);

	if(!startDayFound){
		tempEventStore.setStartDate(100,100,100);
		tempEventStore.setEndDate(100,100,100);
	}
	if(!startTimeFound){
		tempEventStore.setStartTime(100,100);
		tempEventStore.setEndTime(100,100);
	}
	
	if(endDayFound && !endTimeFound){
		tempEventStore.setEndTime(100,100);
	}

	return tempEventStore;
}