//@author A0111379H 

#include "ParserProcessor.h"

const std::string ParserProcessor::LOCKUP_USED_INFORMATION = "USED";

const std::string ParserProcessor::PROCESS_ADD_EVENT = "processAddEvent";
const std::string ParserProcessor::PROCESS_EDIT_EVENT = "processEditEvent";
const std::string ParserProcessor::ADD_EVENT_CORRECTOR = "addEventCorrector";
const std::string ParserProcessor::EDIT_EVENT_CORRECTOR = "editEventCorrector";
const std::string ParserProcessor::EVENT_MK_TIME_CORRECTOR = "eventMkTimeCorrector";
const std::string ParserProcessor::PROCESS_SHOW_EVENT = "processShowEvent";
const std::string ParserProcessor::IDENTIFY_EVENT_NAME = "Event name identified";
const std::string ParserProcessor::IDENTIFY_DATE = "Date identified";
const std::string ParserProcessor::IDENTIFY_DAY = "Day identified";
const std::string ParserProcessor::IDENTIFY_TIME = "Time identified";
const std::string ParserProcessor::IDENTIFY_DEADLINE = "Deadline identified";
const std::string ParserProcessor::IDENTIFY_IMPORTANCE = "Importance identified";
const std::string ParserProcessor::SYSTEM_SHOW = "System show identified";
const std::string ParserProcessor::SHOW_YEAR = "Show by year identified";

const std::string ParserProcessor::CONVERT_NORMAL_TO_FLOAT = "to>>>float";

ParserProcessor::ParserProcessor() {
	keywordMonths[0] = "jan";
	keywordMonths[1] = "january";
	keywordMonths[2] = "feb";
	keywordMonths[3] = "february";
	keywordMonths[4] = "mar";
	keywordMonths[5] = "march";
	keywordMonths[6] = "apr";
	keywordMonths[7] = "april";
	keywordMonths[8] = "may";
	keywordMonths[9] = "jun";
	keywordMonths[10] = "june";
	keywordMonths[11] = "jul";
	keywordMonths[12] = "july";
	keywordMonths[13] = "aug";
	keywordMonths[14] = "august";
	keywordMonths[15] = "sep";
	keywordMonths[16] = "september";
	keywordMonths[17] = "oct";
	keywordMonths[18] = "october";
	keywordMonths[19] = "nov";
	keywordMonths[20] = "november";
	keywordMonths[21] = "dec";
	keywordMonths[22] = "december";
	
	keywordTime[0] = "am";
	keywordTime[1] = "pm";

	keywordDay[0] = "today";
	keywordDay[1] = "tdy";
	keywordDay[2] = "tomorrow";
	keywordDay[3] = "tmr";
	keywordDay[4] = "mon";
	keywordDay[5] = "monday";
	keywordDay[6] = "tues";
	keywordDay[7] = "tuesday";
	keywordDay[8] = "wed";
	keywordDay[9] = "wednesday";
	keywordDay[10] = "thurs";
	keywordDay[11] = "thursday";
	keywordDay[12] = "fri";
	keywordDay[13] = "friday";
	keywordDay[14] = "sat";
	keywordDay[15] = "saturday";
	keywordDay[16] = "sun";
	keywordDay[17] = "sunday";

	matchFound = false;
	startDayFound = false;
	endDayFound = false;
	startTimeFound = false;
	endTimeFound = false;
	afterTwelve = false;
	nameFound = false;
	firstTriggerKeyword = false;
	nameIndex = INVALID_NUMBER;
	semiColonIndex = INVALID_NUMBER;
	toFound = false;
	deadlineFound = false;
	importanceFound = false;
	normalToFloat = false;

	oneMatchFound = false;
	twoMatchFound = false;
	systemShowWeek = false;
	systemShowMonth = false;
	systemShowYear = false;
	systemShowOthers = false;
	userShowDay = false;
	userShowRangeOfDays = false;
	userShowMonth = false;
	userShowRangeOfMonths = false;

	time_t t = time(0);
	now = localtime(&t);
}

//Process the fragmented vector of strings that contains all the information of the Event by calling further functions to identify the event name, day/date,
//time, deadline and importance of the Event. It then checks what information has been found, and throws exceptions if the basic requirements are not met.
//Lastly, it calls two correctors to correct the details and finalise the contents in the Event.
//Returns the final completed Event that has extracted and stored all the information that was initially passed in as a vector.
Event ParserProcessor::processAddEvent(std::vector<std::string> fragmentedWords_) {
	logger.logParserEnterFunc(PROCESS_ADD_EVENT);

	fragmentedWords = fragmentedWords_;
	int shiftedIndex = 0;

	for(unsigned int j = 0; j < fragmentedWords.size(); j++){
		if(fragmentedWords[j].find(";") != std::string::npos){
			semiColonIndex = j;
		}
	}

	try {
		//Check within the vector of strings for keywords to identify day/date, time, deadline, importance
		unsigned int i = 0;
		for (i = semiColonIndex+1; i < fragmentedWords.size(); i++) {
			shiftedIndex = identifyDeadline(i);
			identifyEventName(shiftedIndex);
			shiftedIndex = identifyImportance(i);
			identifyEventName(shiftedIndex);
			shiftedIndex = identifyDay(i);
			identifyEventName(shiftedIndex);
			shiftedIndex = identifyDate(i);
			identifyEventName(shiftedIndex);
			shiftedIndex = identifyTime(i);
			identifyEventName(shiftedIndex);
			matchFound = false;
		}

		tempEventStore.setName(setEventName(nameIndex));
		if(!startDayFound && !startTimeFound && !deadlineFound && !importanceFound && !nameFound && !firstTriggerKeyword){
			nameFound = true;
			logger.logParserIdentified(IDENTIFY_EVENT_NAME);
			nameIndex = fragmentedWords.size()-1;
			tempEventStore.setName(setEventName(nameIndex));
		}

		//Check Exception Cases:
		//Case 1: no event name
		if(tempEventStore.getName() == ""){
			logger.logParserError(ParserExceptions::ERROR_NO_NAME);
			throw ParserExceptions(ParserExceptions::ERROR_NO_NAME);
		}
		//Case 2: name is found. additional input detected after event name but not read in at all
		if (nameFound && !startDayFound && !startTimeFound && !importanceFound) {
			if (fragmentedWords.size() > nameIndex+1) {
				logger.logParserError(ParserExceptions::ERROR_UNUSED_INFORMATION);
				throw ParserExceptions(ParserExceptions::ERROR_UNUSED_INFORMATION);	
			}
		}
		//Case 3: due/deadline keyword found but no date or time input
		if (deadlineFound) {
			if (!endDayFound && !endTimeFound) {
				logger.logParserError(ParserExceptions::ERROR_INSUFFICIENT_INFO);
				throw ParserExceptions(ParserExceptions::ERROR_INSUFFICIENT_INFO);
			}
		}
		//Case 4: some data are unused, means there might be wrong formatting or too many information entered
		for (unsigned int i = nameIndex+1; i < fragmentedWords.size(); i++) {
			try {
				auto tempInt = std::stoi(fragmentedWords[i]);
				logger.logParserError(ParserExceptions::ERROR_UNUSED_INFORMATION);
				throw ParserExceptions(ParserExceptions::ERROR_UNUSED_INFORMATION);
			} catch (...) {
			}
		}
	} catch(ParserExceptions& e) {
		throw e;
	}

	//System-based correction to the input data to complete and confirm the event before returning it
	addEventCorrector();
	eventMktimeCorrector();
	try {
		checkStartBeforeEnd();
	} catch (ParserExceptions& e) {
		throw e;
	}
			
	return tempEventStore;
}

//Process the fragmented vector of strings that contains all the information to be editted by calling further functions to identify any event name, day/date,
//time, deadline and importance of the Event that is to be editted. It then checks what information has been found, and throws exceptions if the basic requirements are not met.
//Lastly, it calls a corrector to correct and confirm the details to be editted in the Event.
//Returns the final completed Event that has extracted and stored all the information to be editted that was initially passed in as a vector.
Event ParserProcessor::processEditEvent(std::vector<std::string> fragmentedWords_) {
	logger.logParserEnterFunc(PROCESS_EDIT_EVENT);

	fragmentedWords = fragmentedWords_;
	int shiftedIndex = 0;

	try {
		//Check if it if changing from normal to floating
		unsigned int i = 0;
		if(identifyNormaltoFloat(i)) {
			i++;
		}

		//Check within the vector of strings for keywords to identify day/date, time, importance
		for (; i < fragmentedWords.size(); i++) {
			shiftedIndex = identifyDeadline(i);
			identifyEventName(shiftedIndex);
			shiftedIndex = identifyImportance(i);
			identifyEventName(shiftedIndex);
			shiftedIndex = identifyDay(i);
			identifyEventName(shiftedIndex);
			shiftedIndex = identifyDate(i);
			identifyEventName(shiftedIndex);
			shiftedIndex = identifyTime(i);
			identifyEventName(shiftedIndex);
			matchFound = false;
		}

		tempEventStore.setName(setEventName(nameIndex));
		if(!startDayFound && !startTimeFound && !deadlineFound && !importanceFound && !firstTriggerKeyword && !normalToFloat){
			nameFound = true;
			logger.logParserIdentified(IDENTIFY_EVENT_NAME);
			nameIndex = fragmentedWords.size()-1;
			tempEventStore.setName(setEventName(nameIndex));
		}

		//Check Exception Cases:
		//Case 1: no name, no day, no time input at all
		if (!nameFound && !startDayFound && !startTimeFound && !importanceFound && !normalToFloat) {
			logger.logParserError(ParserExceptions::ERROR_UNUSED_INFORMATION);
			throw ParserExceptions(ParserExceptions::ERROR_UNUSED_INFORMATION);
		}
		//Case 2: some data are unused, means there might be wrong formatting or too many information entered
		for (unsigned int i = nameIndex+1; i < fragmentedWords.size(); i++) {
			try {
				auto tempInt = std::stoi(fragmentedWords[i]);
				logger.logParserError(ParserExceptions::ERROR_UNUSED_INFORMATION);
				throw ParserExceptions(ParserExceptions::ERROR_UNUSED_INFORMATION);
			} catch (...) {
			}
		}
		//Case 3: cannot convert to deadline events from non deadline
		if (deadlineFound){
			logger.logParserError(ParserExceptions::ERROR_NO_EDIT_TO_DEADLINE);
			throw ParserExceptions(ParserExceptions::ERROR_NO_EDIT_TO_DEADLINE); 
		}

	} catch (ParserExceptions& e) {
		throw e;
	}
	//System-based correction to the input data to confirm the details to be editted in the Event before returning it
	try {
		editEventCorrector();
	} catch (ParserExceptions& e) {
		throw e;
	}

	return tempEventStore;
}

bool ParserProcessor::identifyNormaltoFloat(int index){
	if(fragmentedWords[index] == CONVERT_NORMAL_TO_FLOAT){
		normalToFloat = true;
		tempEventStore.setIsFloating(true);
	}
	return normalToFloat;
}


void ParserProcessor::identifyEventName(int shiftedIndex){
	if(matchFound && !nameFound && !firstTriggerKeyword){
		logger.logParserIdentified(IDENTIFY_EVENT_NAME);
		nameFound = true;
		firstTriggerKeyword = true;
		nameIndex = shiftedIndex;
	}
}

//Sets the name of event to that name if found, removing the ';' at the end. Returns nameFound as true if found.
std::string ParserProcessor::setEventName(int index) {
	if(nameIndex == INVALID_NUMBER){
		return "";
	}
	std::string tempName = "";
	for(int i = 0; i <= index; i++){
		if(i == index){
			if(i == semiColonIndex){
				tempName = tempName + fragmentedWords[i].substr(0,fragmentedWords[i].find_last_not_of(" ;")+1);
			} else {
				tempName = tempName + fragmentedWords[i].substr(0,fragmentedWords[i].find_last_not_of(" ")+1);
			}
		} else {
			tempName = tempName + fragmentedWords[i];
		}
	}
	return tempName;
}


//Checks the string at the current index of the fragmented string vector for the presence of keywords of weekdays/today/tomorrow.
//If found, further operations are done to determine the date set of (day, month and year) based off these keywords.
//The Event's start date and end date will be assigned based on the date set found. Returns matchFound as true if found.
int ParserProcessor::identifyDay(int index) {
	Conversion convertor;
	int tempIndex = index;
	int currentDay = 0, currentWeekDay = 0, inputWeekDay = 0, numWdaysApart = 0;
	std::string strDay;
	std::string lowerCaseString;

	//Find the presence of keywords based on weekdays (tdy,tmr,mon,tues....)
	for (int j = 0; j < NUMBER_OF_KEYWORDS_DAYS && !matchFound; j++) {
		lowerCaseString = fragmentedWords[index];
		for(unsigned int i = 0; i < lowerCaseString.size(); i++){
			lowerCaseString[i] = std::tolower(lowerCaseString[i]);
		}
		if(findExactWord(lowerCaseString,keywordDay[j])){
			strDay = keywordDay[j];
			matchFound = true;
			logger.logParserIdentified(IDENTIFY_DAY);
			tempIndex--;
			
			//assigning start and end date according to what keyword was found
			if (strDay == "today" || strDay == "tdy") {
				if (!startDayFound) {
					tempEventStore.setStartDate(now->tm_mday,now->tm_mon,now->tm_year);
					startDayFound = true;
				} else if (!endDayFound) {
					tempEventStore.setEndDate(now->tm_mday,now->tm_mon,now->tm_year);
					endDayFound = true;
				} else {
					logger.logParserError(ParserExceptions::ERROR_TOO_MANY_DATES);
					throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_DATES);
				}
			} else if (strDay == "tomorrow" || strDay == "tmr") {
				if (!startDayFound) {
					tempEventStore.setStartDate(now->tm_mday+1,now->tm_mon,now->tm_year);
					startDayFound = true;
				} else if (!endDayFound) {
					tempEventStore.setEndDate(now->tm_mday+1,now->tm_mon,now->tm_year);
					endDayFound = true;
				} else {
					logger.logParserError(ParserExceptions::ERROR_TOO_MANY_DATES);
					throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_DATES);
				}
			} else {
				currentWeekDay = now->tm_wday;
				inputWeekDay = convertor.dayOfWeekToInt(strDay);
				//finding number of days from current day to the input week day
				if (inputWeekDay > currentWeekDay) {
					numWdaysApart = inputWeekDay - currentWeekDay;
				} else if (inputWeekDay <= currentWeekDay) {
					numWdaysApart = inputWeekDay - (currentWeekDay - NUMBER_OF_DAYSINAWEEK);
				}
				//checking for next which will add one extra week
				if (tempIndex >= 0) {
					lowerCaseString = fragmentedWords[tempIndex];
					for(unsigned int i = 0; i < lowerCaseString.size(); i++){
						lowerCaseString[i] = std::tolower(lowerCaseString[i]);
					}
					if ((findExactWord(lowerCaseString,"next")) || (findExactWord(lowerCaseString,"nxt"))) {
						numWdaysApart = numWdaysApart + NUMBER_OF_DAYSINAWEEK;
						tempIndex--;
					}
				}
				if (!startDayFound) {
					startDayFound = true;
					tempEventStore.setStartDate(now->tm_mday+numWdaysApart,now->tm_mon,now->tm_year);
				} else if (!endDayFound) {
					endDayFound = true;
					tempEventStore.setEndDate(now->tm_mday+numWdaysApart,now->tm_mon,now->tm_year);
				} else {
					logger.logParserError(ParserExceptions::ERROR_TOO_MANY_DATES);
					throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_DATES);
				}
			}
		}
	}
	if(tempIndex < 0){
		tempIndex = INVALID_NUMBER;
	}
	return tempIndex;
}

//Checks the string at the current index of the fragmented string vector for the presence of any keywords of months. 
//If found, further operations are performed to extract the day, month and year from the surrounding strings in the vector to complete a date set.
//A date set will consist of (day, month, year). The Event's start date and end date will be assigned based on the date set found.
//Returns matchFound is true if a date is found.
int ParserProcessor::identifyDate(int index) {
	Conversion convertor;
	int indexShift = 0, tempIndex = index;
	int tempInt = 0, day = 0, month = 0, year = 0, dayTo = 0;
	std::string strMonth;
	std::string lowerCaseString;
	
	//finding the keywords of months within the current string in the fragmented string vector 
	for (int j = 0; j < NUMBER_OF_KEYWORDS_MONTHS && !matchFound; j++) {
		lowerCaseString = fragmentedWords[index];
		for(unsigned int i = 0; i < lowerCaseString.size(); i++){
			lowerCaseString[i] = std::tolower(lowerCaseString[i]);
		}
		if (findExactWord(lowerCaseString,keywordMonths[j])){
			strMonth = keywordMonths[j];
			matchFound = true;
			logger.logParserIdentified(IDENTIFY_DATE);
			
			//Retrieving one set of (day, month, year) from input data
			year = checkYear(tempIndex,&indexShift);
			tempIndex += indexShift;
			day = checkDay(tempIndex,&indexShift);
			tempIndex += indexShift;
			month = convertor.monthToInt(strMonth);

			//Confirming first set of (day, month, year)
			if ((day > convertor.determineLastDayOfMth(month,year)) || (day == 0)) {
				logger.logParserError(ParserExceptions::ERROR_UNKNOWN_DATE);
				throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_DATE);
			}
			
			//Retrieve second set of (day, month, year) if 'to' is found, using previous month and year
			dayTo = checkDayTo(tempIndex,&indexShift);
			tempIndex += indexShift;

			//Confirming second set of (day, month, year)
			if ((day > convertor.determineLastDayOfMth(month,year)) || (day == 0)) {
				logger.logParserError(ParserExceptions::ERROR_UNKNOWN_DATE);
				throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_DATE);
			}

			//Assigning the values retrieved into start day or end day of event
			assignDate(day,month,year,dayTo);
		}
	}
	if(tempIndex < 0){
		tempIndex = INVALID_NUMBER;
	}
	return tempIndex;
}

//Checking for and extracting year integer. If not found, current year is used instead.
//Returns the value of year in int form in the format used in tm struct.
int ParserProcessor::checkYear(int tempIndex, int* indexShift) {			
	int year = now->tm_year;
	*indexShift = tempIndex;
	int tempInt = 0;

	if (tempIndex + 1 < fragmentedWords.size()) {
		try {
			auto tempStoi = std::stoi(fragmentedWords[tempIndex+1]);
			tempInt = tempStoi;
			if(tempInt > 1300){
				if (tempInt > LOWER_RANGE_YEAR && tempInt < HIGHER_RANGE_YEAR) {
					year = tempInt - TM_YEAR_ADJUSTMENT;
					fragmentedWords[tempIndex+1] = LOCKUP_USED_INFORMATION;
				} else {
					throw ParserExceptions(ParserExceptions::ERROR_INVALID_YEAR);
				}
			}
		} catch (...) {
		}
	}
	*indexShift = tempIndex - *indexShift;
	return year;
}

//Extracting the day integer, either in the same string as the keyword or in the string before the keyword.
//Return the day as an int if found. Throws exception if no day is found.
int ParserProcessor::checkDay(int tempIndex, int* indexShift) {
	Conversion convertor;
	int tempInt = 0;
	*indexShift = tempIndex;
	
	tempIndex--;
	if (tempIndex >= 0) {
		try {
			auto tempStoi = std::stoi(fragmentedWords[tempIndex]);
			fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
			tempInt = tempStoi;
		} catch (...) {
			tempInt = INVALID_NUMBER;
		}
	}
	*indexShift = tempIndex - *indexShift;
	return tempInt;
}

//Checks for 'to' word before a date set. 'to' indicates that the day input before 'to' uses the same month value as the day input after the 'to'.
//Function sets toFound to true if a day before the word 'to' is found. It returns the day if found, or returns 0 if not found. 
int ParserProcessor::checkDayTo(int tempIndex, int* indexShift) {
	int tempInt = 0;
	*indexShift = tempIndex; 

	tempIndex--;
	if (tempIndex >= 0) {
		if (fragmentedWords[tempIndex] == "to") {
			tempIndex--;
			if (tempIndex >= 0) {
				try {
					auto tempStoi = std::stoi(fragmentedWords[tempIndex]);
					fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
					tempInt = tempStoi;
					toFound = true;
					logger.logParserIdentified(IDENTIFY_DATE);
					tempIndex--;
				} catch (...) {
					tempInt = INVALID_NUMBER;
				}
			}
		}
	}
	*indexShift = tempIndex - *indexShift;
	return tempInt;
}

//Inserts the Start day and End day into the temporary Event based on the day, month and year that was found.
//Takes into account whether start day and end day have already been found, and assign accordingly. Throws exception if there are too many dates.
void ParserProcessor::assignDate(int day, int month, int year, int dayTo) {
	if (toFound && dayTo != INVALID_NUMBER) {
		if (!startDayFound && !endDayFound) {
			startDayFound = true;
			tempEventStore.setStartDate(dayTo,month,year);
			endDayFound = true;
			tempEventStore.setEndDate(day,month,year);
			toFound = false;
		} else if (tempEventStore.getIsDeadline()) {
			logger.logParserError(ParserExceptions::ERROR_DUE_TOO_MANY_DATES);
			throw ParserExceptions(ParserExceptions::ERROR_DUE_TOO_MANY_DATES);
		} else {
			logger.logParserError(ParserExceptions::ERROR_TOO_MANY_DATES);
			throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_DATES);
		}
	} else if (day != INVALID_NUMBER){
		if (!startDayFound) {
			startDayFound = true;
			tempEventStore.setStartDate(day,month,year);
		} else if (!endDayFound) {
			endDayFound = true;
			tempEventStore.setEndDate(day,month,year);
		} else if (tempEventStore.getIsDeadline()) {
			logger.logParserError(ParserExceptions::ERROR_DUE_TOO_MANY_DATES);
			throw ParserExceptions(ParserExceptions::ERROR_DUE_TOO_MANY_DATES);
		} else {
			logger.logParserError(ParserExceptions::ERROR_TOO_MANY_DATES);
			throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_DATES);
		}
	} else {
		matchFound = false;
	}
}

//Checks the string at the current index of the fragmented string vector for the presence of any keywords of time. 
//If found, further operations are performed to extract the hour and minutes from the surrounding strings in the vector to complete a time set.
//A time set will consist of (hour, minute). The Event's start time and end time will be assigned based on the time set found.
//Returns matchFound is true if a time is found.
int ParserProcessor::identifyTime(int index) {

	int tempIndex = index, firstTimeInteger = 0, indexShift = 0;
	timeSet hourMin;
	timeSet toHourMin;
	hourMin.hour = 0; hourMin.minute = 0;
	toHourMin.hour = 0; toHourMin.minute = 0;
	std::string lowerCaseString;
	
	//finding the keywords of time within the current string in the fragmented string vector
	for (int j = 0; j < NUMBER_OF_KEYWORDS_TIME && !matchFound; j++) {
		lowerCaseString = fragmentedWords[index];
		for(unsigned int i = 0; i < lowerCaseString.size(); i++){
			lowerCaseString[i] = std::tolower(lowerCaseString[i]);
		}
		if (findExactWord(lowerCaseString,keywordTime[j])){
			if (keywordTime[j] == "pm") {
				afterTwelve = true;
			}
			matchFound = true;
			logger.logParserIdentified(IDENTIFY_TIME);

			//Retrieving one time set of (hour, minute) from the input data
			firstTimeInteger = extractFirstTimeInteger(tempIndex,&indexShift);
			tempIndex += indexShift;
			hourMin = extractHourMin(tempIndex,firstTimeInteger,&indexShift);
			tempIndex += indexShift;

			//Retrieve second time set of (hour, minute) if 'to' is found, using previous am/pm
			toHourMin = extractHourMinTo(tempIndex,&indexShift);
			tempIndex += indexShift;
			
			//Assigning the values retrieved into start time or end time of event
			assignTime(hourMin,toHourMin);
			
			afterTwelve = false;
		}
	}
	if(tempIndex < 0){
		tempIndex = INVALID_NUMBER;
	}
	return tempIndex;
}

//Extracting first integer found either in the same string as the keyword or a string before the keyword
//Returns the value of the first integer found. Throws exception if no integer is found.
int ParserProcessor::extractFirstTimeInteger(int tempIndex, int* indexShift) {
	int firstTimeInteger = 0;
	*indexShift = tempIndex; 

	tempIndex--;
	if (tempIndex >= 0) {
		std::string tempTimeString = fragmentedWords[tempIndex];
		if(tempTimeString.find(".") != std::string::npos){
			tempTimeString = tempTimeString.substr(0,tempTimeString.find(".")) + tempTimeString.substr(tempTimeString.find(".")+1);
		}
		try {
			auto tempStoi = std::stoi(tempTimeString);
			fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
			firstTimeInteger = tempStoi;
		} catch (...) {
			firstTimeInteger = INVALID_NUMBER;
		}
	} 
	*indexShift = tempIndex - *indexShift;
	return firstTimeInteger;
}
			
//Extracting and registering a time set of (hour, minute) based on the first integer found. 
//Throws exception if the hour or minutes are invalid and unknown. Returns a time set in struct timeSet form containing hour & minute.
ParserProcessor::timeSet ParserProcessor::extractHourMin(int tempIndex, int firstTimeInteger, int* indexShift) {
	ParserProcessor::timeSet hourMin;
	int hour = 0, minute = 0;
	*indexShift = tempIndex; 

	if (firstTimeInteger >= 100) {  //For time input in the form of combined hour & minute. E.g. 930 1045 1230
		tempIndex--;
		minute = firstTimeInteger%100;
		if (minute > 60) {
			logger.logParserError(ParserExceptions::ERROR_UNKNOWN_MINUTE);
			throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_MINUTE);
		}
		hour = firstTimeInteger/100;
		if (hour > 12) {
			logger.logParserError(ParserExceptions::ERROR_UNKNOWN_HOUR);
			throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_HOUR);
		}
		if (afterTwelve) {
			if (hour < 12) {
				hour = hour + 12;
			}
		} else {
			if (hour == 12) {
				hour = 0;
			}
		}
	} else if (firstTimeInteger < 100) {  //For time input with hour only
		tempIndex--;
		hour = firstTimeInteger;
		minute = 0;
		if (minute > 60) {
			logger.logParserError(ParserExceptions::ERROR_UNKNOWN_MINUTE);
			throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_MINUTE);
		}
		if (hour > 12) {
			logger.logParserError(ParserExceptions::ERROR_UNKNOWN_HOUR);
			throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_HOUR);
		}
		if (afterTwelve) {
			if (hour < 12) {
				hour = hour + 12;
			}
		} else {
			if (hour == 12) {
				hour = 0;
			}
		}
	}
	hourMin.hour = hour;
	hourMin.minute = minute;
	*indexShift = tempIndex - *indexShift;
	return hourMin;
}
			
//Checks for 'to' word before a time set. 'to' indicates that the hour and minute input before 'to' uses the same am/pm value as the hour and minute input after the 'to'.
//Function sets toFound to true if a time set before the word 'to' is found. Throws exceptions if the hour and minute input are invalid or unknown.
//It returns the time set if found, or returns a zero-ed time set if not found. 
ParserProcessor::timeSet ParserProcessor::extractHourMinTo(int tempIndex, int* indexShift) {
	ParserProcessor::timeSet toHourMin;
	int tempInt = 0;
	int toHour = 0, toMinute = 0;
	*indexShift = tempIndex;

	if (tempIndex >= 0) {
		if (fragmentedWords[tempIndex] == "to") {
			tempIndex--;
			if (tempIndex >= 0) {
				std::string tempTimeString = fragmentedWords[tempIndex];
				if(tempTimeString.find(".") != std::string::npos){
					tempTimeString = tempTimeString.substr(0,tempTimeString.find(".")) + tempTimeString.substr(tempTimeString.find(".")+1);
				}
				try {
					auto tempStoi = std::stoi(tempTimeString);
					fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
					tempInt = tempStoi;
					toFound = true;
					logger.logParserIdentified(IDENTIFY_TIME);

					if (tempInt >= 100) {   //For time input in the form of combined hour & minute. E.g. 930 1045 1230
						toMinute = tempInt%100;
						if (toMinute > 60) {
							logger.logParserError(ParserExceptions::ERROR_UNKNOWN_MINUTE);
							throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_MINUTE);
						}
						toHour = tempInt/100;
						if (toHour > 12) {
							logger.logParserError(ParserExceptions::ERROR_UNKNOWN_HOUR);
							throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_HOUR);
						}
						if (afterTwelve) {
							if (toHour < 12) {
								toHour = toHour + 12;
							}
						} else {
							if (toHour == 12) {
								toHour = 0;
							}
						}
					} else if (tempInt < 100) {   //For time input with hour only
						toHour = tempInt;
						toMinute = 0;
						if (toMinute > 60) {
							logger.logParserError(ParserExceptions::ERROR_UNKNOWN_MINUTE);
							throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_MINUTE);
						}
						if (toHour > 12) {
							logger.logParserError(ParserExceptions::ERROR_UNKNOWN_HOUR);
							throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_HOUR);
						}
						if (afterTwelve) {
							if (toHour < 12) {
								toHour = toHour + 12;
							}
						} else {
							if (toHour == 12) {
								toHour = 0;
							}
						}
					}
					tempIndex--;
				} catch (...) {
					toHour = INVALID_NUMBER;
					toMinute = INVALID_NUMBER;
				}
			}
		}
	}
	toHourMin.hour = toHour;
	toHourMin.minute = toMinute;
	*indexShift = tempIndex - *indexShift;
	return toHourMin;
}

//Inserts the Start time and End time into the temporary Event based on the timeSet retrieved from the data.
//Takes into account whether start time and end time have already been found, and assign accordingly. Throws exception if there are too many times.
void ParserProcessor::assignTime(ParserProcessor::timeSet hourMin, ParserProcessor::timeSet toHourMin) {
	if (toFound && toHourMin.hour != INVALID_NUMBER && toHourMin.minute != INVALID_NUMBER) {
		if (!startTimeFound && !endTimeFound) {
			startTimeFound = true;
			tempEventStore.setStartTime(toHourMin.hour,toHourMin.minute);
			endTimeFound = true;
			tempEventStore.setEndTime(hourMin.hour,hourMin.minute);
			toFound = false;
		} else if (tempEventStore.getIsDeadline()) {
			logger.logParserError(ParserExceptions::ERROR_DUE_TOO_MANY_TIMES);
			throw ParserExceptions(ParserExceptions::ERROR_DUE_TOO_MANY_TIMES);
		} else {
			logger.logParserError(ParserExceptions::ERROR_TOO_MANY_TIMES);
			throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_TIMES);
		}
	} else if(hourMin.hour != INVALID_NUMBER && hourMin.minute != INVALID_NUMBER){
		if (endDayFound && !deadlineFound){
			if (!startTimeFound && endTimeFound){
				struct tm tempTime = tempEventStore.getEndDate();
				tempEventStore.setStartTime(tempTime.tm_hour,tempTime.tm_min);
				startTimeFound = true;
				tempEventStore.setEndTime(hourMin.hour,hourMin.minute);
			} else if(!startTimeFound){
				tempEventStore.setEndTime(hourMin.hour,hourMin.minute);
				endTimeFound = true;
			} else if(startTimeFound && !endTimeFound){
				endTimeFound = true;
				tempEventStore.setEndTime(hourMin.hour,hourMin.minute);
			} else if(startTimeFound && endTimeFound){
				logger.logParserError(ParserExceptions::ERROR_TOO_MANY_TIMES);
				throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_TIMES);
			}
		} else {
			if (!startTimeFound) {
				startTimeFound = true;
				tempEventStore.setStartTime(hourMin.hour,hourMin.minute);
			} else if (!endTimeFound) {				
				endTimeFound = true;
				tempEventStore.setEndTime(hourMin.hour,hourMin.minute);
			} else if (tempEventStore.getIsDeadline()) {
				logger.logParserError(ParserExceptions::ERROR_DUE_TOO_MANY_TIMES);
				throw ParserExceptions(ParserExceptions::ERROR_DUE_TOO_MANY_TIMES);
			} else {
				logger.logParserError(ParserExceptions::ERROR_TOO_MANY_TIMES);
				throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_TIMES);
			}
		}
	} else {
		matchFound = false;
	}
}

//Checks the string at the current index of the fragmented string vector for the keyword "due", indicating a deadline event.
//Sets the temporary Event isDeadline to true, and toggles the startDayFound and startTimeFound to true to prevent more than 2 day & time input. 
//Returns matchFound as true if found. 
int ParserProcessor::identifyDeadline(int index) {
	int tempIndex = index;
	std::string lowerCaseString;
	lowerCaseString = fragmentedWords[index];
	for(unsigned int i = 0; i < lowerCaseString.size() && !deadlineFound; i++){
		lowerCaseString[i] = std::tolower(lowerCaseString[i]);
	}
	if (findExactWord(lowerCaseString,"due") || findExactWord(lowerCaseString,"by")) {
		tempEventStore.setIsDeadline(true);
		deadlineFound = true;
		logger.logParserIdentified(IDENTIFY_DEADLINE);
		if (!endDayFound) {
			endDayFound = true;
		} else {
			throw ParserExceptions(ParserExceptions::ERROR_DUE_TOO_MANY_DATES);
		}
		if (!endTimeFound) {
			endTimeFound = true;
		} else {
			throw ParserExceptions(ParserExceptions::ERROR_DUE_TOO_MANY_TIMES);
		}
		matchFound = true;
		tempIndex--;
	}
	if(tempIndex < 0){
		tempIndex = INVALID_NUMBER;
	}
	return tempIndex;
}

//Checks the string at the current index of the fragmented string vector for the presence of a '!' to indicate importance.
//Determine the level of importance and sets the temporary Event importance level. Throws exception if importance is of wrong format.
//Returns matchFound as true if found.
int ParserProcessor::identifyImportance(int index) {
	int tempIndex = index;
	std::string tempStr = fragmentedWords[index];
	int levelImportance = 0;
	if(!tempStr.empty()){
		if (tempStr.at(0) == '!') {
			matchFound = true;
			for (unsigned int i = 0; i < tempStr.size(); i++) {
				if (tempStr.at(i) == '!') {
					levelImportance++;
				} else if(i != tempStr.size()-1){
					matchFound = false;
				}
			}
			if(matchFound){
				tempIndex--;
				importanceFound = true;
				logger.logParserIdentified(IDENTIFY_IMPORTANCE);
				tempEventStore.setImportanceLevel(levelImportance);
			}
		}
	}
	if(tempIndex < 0){
		tempIndex = INVALID_NUMBER;
	}
	return tempIndex;
}

//Function corrects missing/wrong start day, end day, start time and end time in the temporary Event based on 
//what type of Event it has been identified as.
void ParserProcessor::addEventCorrector() {
	logger.logParserEnterFunc(ADD_EVENT_CORRECTOR);

	//Deadline events, set Start date and Start time to be equal to the End date and End time read from input
	if (tempEventStore.getIsDeadline()) {
		struct tm tempTime = tempEventStore.getStartDate();
		if (startDayFound && startTimeFound) {
			tempEventStore.setEndDate(tempTime.tm_mday,tempTime.tm_mon,tempTime.tm_year);
			tempEventStore.setEndTime(tempTime.tm_hour,tempTime.tm_min);
		}
		if (startDayFound && !startTimeFound) {
			tempEventStore.setStartTime(23,59);
			tempEventStore.setEndTime(23,59);
			tempEventStore.setEndDate(tempTime.tm_mday,tempTime.tm_mon,tempTime.tm_year);
			startTimeFound = true;
		}
		if (!startDayFound && startTimeFound) {
			tempEventStore.setStartDate(now->tm_mday,now->tm_mon,now->tm_year);
			tempEventStore.setEndDate(now->tm_mday,now->tm_mon,now->tm_year);
			tempEventStore.setEndTime(tempTime.tm_hour,tempTime.tm_min);
			startDayFound = true;
		}
	} else {
		//Floating events, set temporary Event isFloating to true
		if (!startDayFound && !startTimeFound) {
			tempEventStore.setIsFloating(true);
		}
		//Full day events, set Start time to 0am and End time to 11.59pm
		if (startDayFound && !startTimeFound && !endTimeFound) {
			tempEventStore.setStartTime(0,0);
			tempEventStore.setEndTime(23,59);
		}
		//Today event, set Start day and End day to the current system day
		if (!startDayFound && startTimeFound) {
			int day = now->tm_mday; 
			int month = now->tm_mon; 
			int year = now->tm_year;
			tempEventStore.setStartDate(day,month,year);
			tempEventStore.setEndDate(day,month,year);
		}
		//Single day event, set End day to be equal to the Start day
		if (!endDayFound) {
			struct tm tempTime = tempEventStore.getStartDate();
			tempEventStore.setEndDate(tempTime.tm_mday,tempTime.tm_mon,tempTime.tm_year);
		}
		//Event with Start time only, sets End time to an hour after Start time by default
		if (!endDayFound && startTimeFound && !endTimeFound) {
			struct tm tempTime = tempEventStore.getStartDate();
			if ((tempTime.tm_hour)+1 == 24 && tempTime.tm_min == 0) {   //Corrects any 12am timing to 11.59pm to prevent spilling over to next day
				tempEventStore.setEndTime(23,59);					  //Because day ends at 11.59pm and new day starts at 12am
			} else {
				tempEventStore.setEndTime((tempTime.tm_hour)+1,tempTime.tm_min);
			}
			endTimeFound = true;
		}
		//Multiple day events with End time only, sets Start time to 12am of the first day
		if (endDayFound && startTimeFound && !endTimeFound){
			tempEventStore.setEndTime(23,59);
			endTimeFound = true;
		}
		//Multiple day events with End time only, sets Start time to 12am of the first day
		if (endDayFound && endTimeFound && !startTimeFound) {
			tempEventStore.setStartTime(0,0);
			startTimeFound = true;
		}
		//Corrects any 12am timing to 11.59pm to prevent spilling over to next day, because day ends at 11.59pm and new day starts at 12am
		if (startTimeFound && endTimeFound) {
			struct tm tempTime = tempEventStore.getEndDate();
			if (tempTime.tm_hour == 0 && tempTime.tm_min == 0) {
				tempEventStore.setEndTime(23,59);
			}
		}
		//Corrects any spill over timing mistake of the user input to update the End day to the next day. E.g. tdy 10pm-3am -> tdy to tmr 10pm-3am
		struct tm tempEventStartDate = tempEventStore.getStartDate();
		struct tm tempEventEndDate = tempEventStore.getEndDate();
		if (tempEventStartDate.tm_mday == tempEventEndDate.tm_mday &&
			tempEventStartDate.tm_mon == tempEventEndDate.tm_mon &&
			tempEventStartDate.tm_year == tempEventEndDate.tm_year) {
				if (tempEventEndDate.tm_hour < tempEventStartDate.tm_hour) {
					tempEventStore.setEndDate(tempEventStartDate.tm_mday+1,tempEventStartDate.tm_mon,tempEventStartDate.tm_year);
				} else if (tempEventEndDate.tm_hour == tempEventStartDate.tm_hour && tempEventEndDate.tm_min < tempEventStartDate.tm_min) {
					tempEventStore.setEndDate(tempEventStartDate.tm_mday+1,tempEventStartDate.tm_mon,tempEventStartDate.tm_year);
				}
		}
	}
}

void ParserProcessor::checkStartBeforeEnd() {
	struct tm tempEventStartDate = tempEventStore.getStartDate();
	struct tm tempEventEndDate = tempEventStore.getEndDate();
	
	//Exception case 1: Start day is later than End day
	if (tempEventStartDate.tm_year > tempEventEndDate.tm_year) {
		throw ParserExceptions(ParserExceptions::ERROR_START_AFTER_END);
	} 
	if (tempEventStartDate.tm_year == tempEventEndDate.tm_year) {
		if (tempEventStartDate.tm_mon > tempEventEndDate.tm_mon) {
			throw ParserExceptions(ParserExceptions::ERROR_START_AFTER_END);
		}
	}
	if (tempEventStartDate.tm_year == tempEventEndDate.tm_year) {
		if (tempEventStartDate.tm_mon == tempEventEndDate.tm_mon) {
			if (tempEventStartDate.tm_mday > tempEventEndDate.tm_mday) {
				throw ParserExceptions(ParserExceptions::ERROR_START_AFTER_END);
			}
		}
	}

	//Exception case 2: Start time is later than End time if day is the same
	if (tempEventStartDate.tm_year == tempEventEndDate.tm_year &&
		tempEventStartDate.tm_mon == tempEventEndDate.tm_mon &&
		tempEventStartDate.tm_mday == tempEventEndDate.tm_mday) {
			if (tempEventStartDate.tm_hour > tempEventEndDate.tm_hour) {
				throw ParserExceptions(ParserExceptions::ERROR_START_AFTER_END);
			} 
			if (tempEventStartDate.tm_hour == tempEventEndDate.tm_hour) {
				if (tempEventStartDate.tm_min > tempEventEndDate.tm_min) {
					throw ParserExceptions(ParserExceptions::ERROR_START_AFTER_END);
				}
			}
	}
}

//Function ensures only the details entered in the input will be editted while the other data will be left untouched by creating dummy values 
//to signal which detail should not be touched. Performs correction to the details that are to be editted, by completing and correcting their values.
void ParserProcessor::editEventCorrector() {
	logger.logParserEnterFunc(EDIT_EVENT_CORRECTOR);

	//Single day event, set End day to be equal to Start day
	if (startDayFound && !endDayFound) {
		struct tm tempTime = tempEventStore.getStartDate();
		tempEventStore.setEndDate(tempTime.tm_mday,tempTime.tm_mon,tempTime.tm_year);
	}
	//Event with Start time only, sets End time to an hour after Start time by default
	if (startTimeFound && !endDayFound && !endTimeFound) {
		struct tm tempTime = tempEventStore.getStartDate();
		if (tempTime.tm_hour+1 == 24 && tempTime.tm_min == 0) {
			tempEventStore.setEndTime(23,59);
		} else {
			tempEventStore.setEndTime((tempTime.tm_hour)+1,tempTime.tm_min);
		}
	}
	//Multiple day events with End time only, sets Start time to 12am of the first day
	if (endDayFound && startTimeFound && !endTimeFound){
		tempEventStore.setEndTime(23,59);
		endTimeFound = true;
	}
	//Multiple day events with End time only, sets Start time to 12am of the first day
	if (endDayFound && endTimeFound && !startTimeFound) {
		tempEventStore.setStartTime(0,0);
		startTimeFound = true;
	}
	//Corrects any spill over timing mistake of the user input to update the End day to the next day. E.g. 10pm-3am -> tdy to tmr 10pm-3am
	struct tm tempEventStartDate = tempEventStore.getStartDate();
	struct tm tempEventEndDate = tempEventStore.getEndDate();
	if (tempEventStartDate.tm_mday == tempEventEndDate.tm_mday &&
		tempEventStartDate.tm_mon == tempEventEndDate.tm_mon &&
		tempEventStartDate.tm_year == tempEventEndDate.tm_year) {
			if (tempEventEndDate.tm_hour < tempEventStartDate.tm_hour) {
				tempEventStore.setEndDate(tempEventStartDate.tm_mday+1,tempEventStartDate.tm_mon,tempEventStartDate.tm_year);
			} else if (tempEventEndDate.tm_hour == tempEventStartDate.tm_hour && tempEventEndDate.tm_min < tempEventStartDate.tm_min) {
				tempEventStore.setEndDate(tempEventStartDate.tm_mday+1,tempEventStartDate.tm_mon,tempEventStartDate.tm_year);
			}
	}
	
	//Only calls correctors after Start day/Start time/End day/End time has been completed
	if (startDayFound || startTimeFound) {
		try {
			checkStartBeforeEnd();
		} catch (ParserExceptions& e) {
			throw e;
		}
	}
	eventMktimeCorrector();

	//Set dummy values to details that should not be touched
	if (!nameFound) {
		tempEventStore.setName("");
	}
	if (!startDayFound) {
		tempEventStore.setStartDate(100,100,100);
		tempEventStore.setEndDate(100,100,100);
	}
	if (!startTimeFound) {
		tempEventStore.setStartTime(100,100);
		tempEventStore.setEndTime(100,100);
	}
	if (!importanceFound) {
		tempEventStore.setImportanceLevel(-1);
	}
}

//Performs mktime on both the Start date as well as the End date of the temporary Event to ensure a correct (day, month, year) and also
//to generate the weekday value for the Start date.
void ParserProcessor::eventMktimeCorrector() {
	logger.logParserEnterFunc(EVENT_MK_TIME_CORRECTOR);

	struct tm* temptmPtr;
	temptmPtr = &tempEventStore.getStartDate();
	mktime(temptmPtr);
	tempEventStore.setStartDate(temptmPtr->tm_mday,temptmPtr->tm_mon,temptmPtr->tm_year);
	tempEventStore.setStartTime(temptmPtr->tm_hour,temptmPtr->tm_min);
	tempEventStore.setStartWeekday(temptmPtr->tm_wday);

	temptmPtr = &tempEventStore.getEndDate();
	mktime(temptmPtr);
	tempEventStore.setEndDate(temptmPtr->tm_mday,temptmPtr->tm_mon,temptmPtr->tm_year);
	tempEventStore.setEndTime(temptmPtr->tm_hour,temptmPtr->tm_min);
	tempEventStore.setEndWeekday(temptmPtr->tm_wday);
}

//Process the fragmented vector of strings that contains to be shown by calling further functions to identify day/date. It then checks what information has been found, and throws 
//exceptions if the basic requirements are not met. Lastly, it calls a corrector to correct the date set to a valid date.
//Returns an Event that contains the range of days to be shown from its Start day to its End day.
Event ParserProcessor::processShowEvent(std::vector<std::string> fragmentedWords_) {
	logger.logParserEnterFunc(PROCESS_SHOW_EVENT);

	std::string tempString;
	fragmentedWords = fragmentedWords_;
	int tempInt = 0;
	int daysToEndWeek = 0, weekday = 0;
	int day = now->tm_mday;
	int month = now->tm_mon;
	int year = now->tm_year;

	unsigned int i = 0; 
	//Check for show by year. E.g. show year/yr   show 2015   show 2015-2016
	if (i < fragmentedWords.size()) {
		if (checkShowByYear(i)) {
			i++;
		}
	}

	//Check for system based Show. E.g. week/wk, month/mth, float, due, importance, all)
	if (i < fragmentedWords.size()) {
		if (checkSystemBasedShow(i)) {
			i++;
		}
	}

	//Check for user based Show (e.g. 14 apr, april, month/ april, week/ 14apr, 17 apr to 18 apr, apr to may)
	for (; i < fragmentedWords.size(); i++) {
		identifyShowDay(i);
		identifyShowDate(i);
		matchFound = false;
	}

	//Exception Cases:
	//Case 1: no show is found
	if (!systemShowOthers && !systemShowYear && !userShowDay && !userShowMonth && !userShowRangeOfDays && !userShowRangeOfMonths && !systemShowWeek && !systemShowMonth) {
		logger.logParserError(ParserExceptions::ERROR_NO_SHOW);
		throw ParserExceptions(ParserExceptions::ERROR_NO_SHOW);
	}

	//Case 2: some data are unused, means there might be wrong formatting or too many information entered
	for (unsigned int i = 0; i < fragmentedWords.size(); i++) {
		try {
			auto tempInt = std::stoi(fragmentedWords[i]);
			logger.logParserError(ParserExceptions::ERROR_UNUSED_INFORMATION);
			throw ParserExceptions(ParserExceptions::ERROR_UNUSED_INFORMATION);
		} catch (...) {
		}
	}

	//Correcting dates
	showEventCorrector();
	if (!systemShowOthers) {
		try {
			checkStartBeforeEnd();
		} catch (ParserExceptions& e) {
			throw e;
		}
	}
	eventMktimeCorrector();

	return tempEventStore;
}

//Verifies if the first word is a show by year and assigns Start and End date accordingly.  
//Returns true if the a show by year is identified.
bool ParserProcessor::checkShowByYear(int tempIndex) {
	int tempInt = 0;
	int day = now->tm_mday;
	int month = now->tm_mon;
	int year = now->tm_year;
	bool nextFound = false;
	std::string firstWord = fragmentedWords[tempIndex];

	try {      //Check if first word is a year integer. E.g. 2015
		auto tempStoi = std::stoi(firstWord);
		tempInt = tempStoi;
		if(tempInt > 1300){
			if (tempInt > LOWER_RANGE_YEAR && tempInt < HIGHER_RANGE_YEAR) {
				if (year == tempInt - TM_YEAR_ADJUSTMENT) {
					tempEventStore.setStartDate(day,month,year);
					tempEventStore.setEndDate(31,11,year);
				} else {
					year = tempInt - TM_YEAR_ADJUSTMENT;
					tempEventStore.setStartDate(1,0,year);
					tempEventStore.setEndDate(31,11,year);
				}
				systemShowYear = true;
				fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
				tempIndex++;
				if (fragmentedWords.size() > tempIndex) {      
					if (fragmentedWords[tempIndex] == "to") {    //Check if it is a range between 2 year inputs. E.g. 2015-2016  2015 to 2016
						try {
							tempIndex++;
							if (fragmentedWords.size() > tempIndex) {
								auto tempStoi = std::stoi(fragmentedWords[tempIndex]);
								tempInt = tempStoi;
								fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
								if (tempInt > LOWER_RANGE_YEAR && tempInt < HIGHER_RANGE_YEAR) {
									tempEventStore.setEndDate(31,11,tempInt-TM_YEAR_ADJUSTMENT);
								} 
							}
						} catch (...) {
						}
					}
				}
			} else {
				throw ParserExceptions(ParserExceptions::ERROR_INVALID_YEAR);
			}
		}
	} catch (...) {  //Check if it is system show year, which shows current year
		if (firstWord == "next" || firstWord == "nxt") {
			tempIndex++;
			nextFound = true;
			firstWord = fragmentedWords[tempIndex];
		}
		if (firstWord == "year" || firstWord == "yr") {
			if (nextFound) {
				tempEventStore.setStartDate(1,0,year+1);
				tempEventStore.setEndDate(31,11,year+1);
			} else {
				tempEventStore.setStartDate(day,month,year);
				tempEventStore.setEndDate(31,11,year);
			}
			systemShowYear = true;
		}
	}
	if(systemShowYear){
		logger.logParserIdentified(SHOW_YEAR);
	}
	return systemShowYear;
}

//Verifies if the first word is any of the system show type and assigns Start and End date, or float/importance/deadline according to what was identified. 
//Returns true if the a system based show is identified. 
bool ParserProcessor::checkSystemBasedShow(int tempIndex) {
	Conversion convertor;

	int daysToEndWeek = 0, weekday = 0;
	int day = now->tm_mday;
	int month = now->tm_mon;
	int year = now->tm_year;
	bool nextFound = false;
	std::string firstWord = fragmentedWords[tempIndex];
	
	//Check all system show commands and assign Start and End date accordingly if required
	if (firstWord == "next" || firstWord == "nxt") {
		tempIndex++;
		nextFound = true;
		firstWord = fragmentedWords[tempIndex];
	}
	if (firstWord == "week" || firstWord == "wk") {
		fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
		tempEventStore.setName("week");
		weekday = now->tm_wday;
		daysToEndWeek = 6 - weekday;
		if (nextFound) {
			tempEventStore.setStartDate(day + daysToEndWeek + 1,month,year);
			tempEventStore.setEndDate(day + daysToEndWeek + 1 + NUMBER_OF_DAYSINAWEEK,month,year);
		} else {
			tempEventStore.setStartDate(day,month,year);
			tempEventStore.setEndDate(day + daysToEndWeek,month,year);
		}
		systemShowWeek = true;
	} else if (firstWord == "month" || firstWord == "mth") {
		tempEventStore.setName("month");
		fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
		if (nextFound) {
			tempEventStore.setStartDate(1,month+1,year);
			tempEventStore.setEndDate(convertor.determineLastDayOfMth(month,year),month+1,year);
		} else {
			tempEventStore.setStartDate(day,month,year);
			tempEventStore.setEndDate(convertor.determineLastDayOfMth(month,year),month,year);
		}
		systemShowMonth = true;
	} else if (firstWord == "floating" || firstWord == "float" || firstWord == "all" || firstWord == "due" || 
				firstWord == "important" || firstWord == "impt" || firstWord == "done" || firstWord == "completed" || firstWord == "complete") {
		tempEventStore.setName(firstWord);
		fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
		systemShowOthers = true;
	} else if (firstWord[0] == '!') {
		int levelImportance = 0;
		for (unsigned int i = 0; i < firstWord.size(); i++) {
			if (firstWord[i] == '!') {
				levelImportance++;
			} else {
				logger.logParserError(ParserExceptions::ERROR_UNUSED_INFORMATION);
				throw ParserExceptions(ParserExceptions::ERROR_UNUSED_INFORMATION);
			}
		}
		tempEventStore.setImportanceLevel(levelImportance);
		tempEventStore.setName("specificimportance");
		fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
		systemShowOthers = true;
	}
	if(systemShowOthers || systemShowWeek || systemShowMonth){
		logger.logParserIdentified(SYSTEM_SHOW);
	}
	return (systemShowOthers || systemShowWeek || systemShowMonth);
}
	
//Checks the string at the current index of the fragmented string vector for the presence of any keywords of days. If found, further operations are 
//performed to determine the day, month and year to complete a date set. A date set will consist of (day, month, year). 
//The number of matches found is recorded, if two matches are found, a range of days is requested to be shown. 
//Throws exception if there are too many dates. Returns matchFound is true if a keyword day is found
bool ParserProcessor::identifyShowDay(int index) {
	Conversion convertor;
	int tempIndex = 0, weekday = 0, currentWeekDay = 0, inputWeekDay = 0, numWdaysApart = 0;
	int day = now->tm_mday;
	int month = now->tm_mon;
	int year = now->tm_year;
	std::string strDay;
	std::string lowerCaseString;

	//Find the presence of keywords based on weekdays (tdy,tmr,mon,tues....)
	for (int j = 0; j < NUMBER_OF_KEYWORDS_DAYS && !matchFound; j++) {
		lowerCaseString = fragmentedWords[index];
		for(unsigned int i = 0; i < lowerCaseString.size(); i++){
			lowerCaseString[i] = std::tolower(lowerCaseString[i]);
		}
		if(findExactWord(lowerCaseString,keywordDay[j])){
			tempIndex = index;
			strDay = keywordDay[j];
			matchFound = true;
			logger.logParserIdentified(IDENTIFY_DAY);
			
			//assigning start and end date according to what keyword was found
			if (strDay == "today" || strDay == "tdy") {
				if (!oneMatchFound) {
					tempEventStore.setStartDate(now->tm_mday,now->tm_mon,now->tm_year);
					oneMatchFound = true;
					userShowDay = true;
				} else if (!twoMatchFound) {
					tempEventStore.setEndDate(now->tm_mday,now->tm_mon,now->tm_year);
					twoMatchFound = true;
					userShowRangeOfDays = true;
					userShowDay = false;
				} else {
					logger.logParserError(ParserExceptions::ERROR_TOO_MANY_DATES);
					throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_DATES);
				}
			} else if (strDay == "tomorrow" || strDay == "tmr") {
				if (!oneMatchFound) {
					tempEventStore.setStartDate(now->tm_mday+1,now->tm_mon,now->tm_year);
					oneMatchFound = true;
					userShowDay = true;
				} else if (!twoMatchFound) {
					tempEventStore.setEndDate(now->tm_mday+1,now->tm_mon,now->tm_year);
					twoMatchFound = true;
					userShowRangeOfDays = true;
					userShowDay = false;
				} else {
					logger.logParserError(ParserExceptions::ERROR_TOO_MANY_DATES);
					throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_DATES);
				}
			} else {
				currentWeekDay = now->tm_wday;
				inputWeekDay = convertor.dayOfWeekToInt(strDay);
				//finding number of days from current day to the input week day
				if (inputWeekDay > currentWeekDay) {
					numWdaysApart = inputWeekDay - currentWeekDay;
				} else if (inputWeekDay <= currentWeekDay) {
					numWdaysApart = inputWeekDay -(currentWeekDay - NUMBER_OF_DAYSINAWEEK);
				}
				tempIndex--;
				//checking for next which will add one extra week
				if (tempIndex >= 0) {
					lowerCaseString = fragmentedWords[tempIndex];
					for(unsigned int i = 0; i < lowerCaseString.size(); i++){
						lowerCaseString[i] = std::tolower(lowerCaseString[i]);
					}
					if ((findExactWord(lowerCaseString,"next")) || (findExactWord(lowerCaseString,"nxt"))) {
						numWdaysApart = numWdaysApart + NUMBER_OF_DAYSINAWEEK;
						tempIndex--;
					}
				}
				if (!oneMatchFound) {
					tempEventStore.setStartDate(now->tm_mday+numWdaysApart,now->tm_mon,now->tm_year);
					oneMatchFound = true;
					userShowDay = true;
				} else if (!twoMatchFound) {
					tempEventStore.setEndDate(now->tm_mday+numWdaysApart,now->tm_mon,now->tm_year);
					twoMatchFound = true;
					userShowRangeOfDays = true;
					userShowDay = false;
				} else {
					logger.logParserError(ParserExceptions::ERROR_TOO_MANY_DATES);
					throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_DATES);
				}
			}
		}
	}
	return matchFound;
}

//Checks the string at the current index of the fragmented string vector for the presence of any keywords of months. If found, further operations are 
//performed to extract the day, month and year from the surrounding strings in the vector to complete a date set. A date set will consist of (day, month, year). 
//The number of matches found is recorded, if two matches are found, a range of days/range of months is requested to be shown. 
//Throws exception if there are too many dates, or if there are unknown or invalid dates. Returns matchFound is true if a date is found.
bool ParserProcessor::identifyShowDate(int index) {
	Conversion convertor;
	std::string strMonth;
	std::string lowerCaseString;
	int tempIndex = 0, indexShift = 0, weekday = 0, dayTo = 0;
	int day = now->tm_mday;
	int month = now->tm_mon;
	int year = now->tm_year;
	
	//Checks current string for any keywords of months
	for (unsigned int j = 0; j < NUMBER_OF_KEYWORDS_MONTHS && !matchFound; j++) {
		lowerCaseString = fragmentedWords[index];
		for(unsigned int i = 0; i < lowerCaseString.size(); i++){
			lowerCaseString[i] = std::tolower(lowerCaseString[i]);
		}
		if(findExactWord(lowerCaseString,keywordMonths[j])){
			matchFound = true;
			logger.logParserIdentified(IDENTIFY_DATE);
			if (!oneMatchFound) {
				oneMatchFound = true;
			} else if (!twoMatchFound) {
				twoMatchFound = true;
			} else {
				logger.logParserError(ParserExceptions::ERROR_TOO_MANY_DATES);
				throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_DATES);
			}
			tempIndex = index;
			strMonth = keywordMonths[j];
			
			//Retrieving one date set of (day, month, year) from the data
			year = checkYear(tempIndex,&indexShift);
			tempIndex += indexShift;
			day = checkShowDay(tempIndex,&indexShift);
			tempIndex += indexShift;
			month = convertor.monthToInt(strMonth);

			//Confirming the first set of (day, month, year)
			if (userShowDay || userShowRangeOfDays) {
				if ((day > convertor.determineLastDayOfMth(month,year)) || (day < 1)) {
					logger.logParserError(ParserExceptions::ERROR_UNKNOWN_DATE);
					throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_DATE);
				}
			}

			//Retrieving the second date set of (day, month, year) if 'to' is foun, using previous month and year
			dayTo = checkShowDayTo(tempIndex,&indexShift);
			tempIndex += indexShift;

			//Confirming the second set of (day, month, year)
			if (userShowRangeOfDays) {
				if ((day > convertor.determineLastDayOfMth(month,year)) || (day < 1)) {
					logger.logParserError(ParserExceptions::ERROR_UNKNOWN_DATE);
					throw ParserExceptions(ParserExceptions::ERROR_UNKNOWN_DATE);
				}
			}

			//Assigning the values retrieved into start day or end day of event
			assignShowDate(day,month,year,dayTo);
		}
	}
	return matchFound;
}

//Extracting the day integer, either in the same string as the keyword or in the string before the keyword.
//Return the day as an int if found. 
int ParserProcessor::checkShowDay(int tempIndex, int* indexShift) {
	Conversion convertor;
	int tempInt = 0;
	*indexShift = tempIndex;

	try {
		auto tempStoi = std::stoi(fragmentedWords[tempIndex]);
		fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
		tempInt = tempStoi;
		if (!twoMatchFound) {
			userShowDay = true;
		} else {
			userShowRangeOfDays = true;
			userShowDay = false;
		}
	} catch (...) {
		//no integer found, check if there are any possibility of the day input before the month
		//if no possibility, implies showMonth. if theres a day, implies showDay or showWeek depending
		//whether systemShowDay or systemShowWeek is true
		tempIndex--;
		if (tempIndex >= 0) {
			try {
				auto tempStoi = std::stoi(fragmentedWords[tempIndex]);
				fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
				tempInt = tempStoi;
				if (!twoMatchFound) {
					userShowDay = true;
				} else {
					userShowRangeOfDays = true;
					userShowDay = false;
				}
			} catch(...) {
				if (!twoMatchFound) {
					userShowMonth = true;
				} else {
					userShowRangeOfMonths = true;
					userShowMonth = false;
				}
			}
		} else {
			if (!twoMatchFound) {
				userShowMonth = true;
			} else {
				userShowRangeOfMonths = true;
				userShowMonth = false;
			}
		}
	}
	*indexShift = tempIndex - *indexShift;
	return tempInt;
}

//Checks for 'to' word before a date set. 'to' indicates that the day input before 'to' uses the same month value as the day input after the 'to'.
//Function sets toFound to true if a day before the word 'to' is found. It returns the day if found, or returns 0 if not found. 
int ParserProcessor::checkShowDayTo(int tempIndex, int* indexShift) {
	int tempInt = 0;
	*indexShift = tempIndex; 

	tempIndex--;
	if (tempIndex >= 0) {
		if (fragmentedWords[tempIndex] == "to") {
			tempIndex--;
			if (tempIndex >= 0) {
				try {
					auto tempStoi = std::stoi(fragmentedWords[tempIndex]);
					fragmentedWords[tempIndex] = LOCKUP_USED_INFORMATION;
					tempInt = tempStoi;
					toFound = true;
					logger.logParserIdentified(IDENTIFY_DATE);
					twoMatchFound = true;
					userShowRangeOfDays = true;
					userShowDay = false;
				} catch (...) {
				}
			}
		}
	}
	*indexShift = tempIndex - *indexShift;
	return tempInt;
}

//Inserts values into startDate and endDate based on what Show is found
void ParserProcessor::assignShowDate(int day, int month, int year, int dayTo) {
	Conversion convertor;
	int weekday = 0, daysToEndWeek = 0;
	
	//For handling showing of a day, or a range of days
	if (toFound) {
		tempEventStore.setStartDate(dayTo,month,year);
		tempEventStore.setEndDate(day,month,year);
	} else if (!systemShowWeek) {
		if (userShowDay) {
			tempEventStore.setStartDate(day,month,year);
			tempEventStore.setEndDate(day,month,year);
		} 
		if (userShowRangeOfDays) {
			tempEventStore.setEndDate(day,month,year);
		}
	} else {     //For handling system showing of the week based on a day. E.g. show week 14apr
		time_t t = time(0);
		struct tm* dateWithinWeek = localtime(&t);
		dateWithinWeek->tm_mday = day;
		dateWithinWeek->tm_mon = month;
		dateWithinWeek->tm_year = year;
		mktime(dateWithinWeek);
		weekday = dateWithinWeek->tm_wday;
		daysToEndWeek = 6 - weekday;
		if (userShowDay) {
			tempEventStore.setStartDate(day-weekday,month,year);
			tempEventStore.setEndDate(day+daysToEndWeek,month,year);
		} 
	}

	//For handling system show month. E.g. month   mar   apr
	if (userShowMonth) {
		tempEventStore.setName("month");
		if (month == now->tm_mon) {
			tempEventStore.setStartDate(now->tm_mday,month,year);
			tempEventStore.setEndDate(convertor.determineLastDayOfMth(month,year),month,year);
		} else {
			tempEventStore.setStartDate(1,month,year);
			tempEventStore.setEndDate(convertor.determineLastDayOfMth(month,year),month,year);
		}
	}
	//For handling system show range of months. E.g. mar-apr   
	if (userShowRangeOfMonths) {
		tempEventStore.setEndDate(convertor.determineLastDayOfMth(month,year),month,year);
	}
}

void ParserProcessor::showEventCorrector() {
	if (oneMatchFound && !twoMatchFound) { 
		if (userShowDay && !systemShowWeek) {
			struct tm tempDate = tempEventStore.getStartDate();
			tempEventStore.setEndDate(tempDate.tm_mday,tempDate.tm_mon,tempDate.tm_year);
		}
	}
	tempEventStore.setStartTime(0,0);
	tempEventStore.setEndTime(0,0);
}

bool ParserProcessor::findExactWord(std::string input, std::string keyWord){
	bool isExact = true;
	unsigned int i;
	for(i = 0; i < input.size() && i < keyWord.size(); i++){
		if(input[i] != keyWord[i]){
			isExact = false;
		}
	}
	if(isExact){
		if(i != keyWord.size() || i != input.size()){
			isExact= false;
			if(input[i] == ' ' && i == input.size()-1){
				isExact = true;
			}
		}
	}
	return isExact;
}
