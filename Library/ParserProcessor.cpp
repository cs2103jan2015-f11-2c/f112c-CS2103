#include "ParserProcessor.h"

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
	keywordDetails[0] = "name";
	keywordDetails[1] = "date";
	keywordDetails[2] = "time";
	keywordDetails[3] = "description";
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

	tempEventStore.setName(fragmentedWords[0]);
	
	unsigned int i = 1;
	int j = 0;
	int tempi = 0;
	for(i = 1; i < fragmentedWords.size(); i++){
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
				fragmentedWords[tempi] = "USED";
				tempInt = tempStoi;
			} catch (const std::invalid_argument& e){
				tempi--;
				auto tempStoi = std::stoi(fragmentedWords[tempi]);
				fragmentedWords[tempi] = "USED";
				tempInt = tempStoi;
			} 
			day = tempInt;
			month = convertor.monthToInt(strMonth);
			year = 2015;
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
				fragmentedWords[tempi] = "USED";
				tempInt = tempStoi;
			} catch (const std::invalid_argument& e){
				tempi--;
				auto tempStoi = std::stoi(fragmentedWords[tempi]);
				fragmentedWords[tempi] = "USED";
				tempInt = tempStoi;
			} 
			if(tempInt >= 100){
				minute = tempInt%100;
				if(afterTwelve){
					hour = tempInt/100 + 12;
				} else {
					hour = tempInt/100;
				}
				if(!startTimeFound){
					tempEventStore.setStartTime(hour,minute);
					startTimeFound = true;
				} 
				else {
					tempEventStore.setEndTime(hour,minute);
					endTimeFound = true;
				}
			} else if(tempInt < 100){
				tempi--;
				try {
					hour = std::stoi(fragmentedWords[tempi]);
					fragmentedWords[tempi] = "USED";
					minute = tempInt;
				} catch (const std::invalid_argument& e){
					hour = tempInt;
					minute = 0;
				} 
				if(afterTwelve){
					hour = hour + 12;
				} 
				if(!startTimeFound){
					startTimeFound = true;
					tempEventStore.setStartTime(hour,minute);
				} 
				else {
					endTimeFound = true;
					tempEventStore.setEndTime(hour,minute);
				}
			}
		}
		matchFound = false;
	}

	if(!startDayFound){
		tempEventStore.setStartDate(day,month,year);
	}	
	if(!startTimeFound){
		tempEventStore.setStartTime(hour,minute);
	} 
	if(!startDayFound && !startTimeFound){
		tempEventStore.setIsFloating(true);
	}
	if(!endDayFound){
		tempEventStore.setEndDate(day,month,year);
	}
	if(!endTimeFound){
		tempEventStore.setEndTime(hour+1,minute);
	}

	return tempEventStore;
}

Event ParserProcessor::processEditEvent(std::vector<std::string> fragmentedWords){
	Event tempEventStore;
	return tempEventStore;
}