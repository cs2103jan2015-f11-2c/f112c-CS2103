#include "EventStorage.h"

//These are messages to give the user feedback on what the program is doing.
const string EventStorage::ADDED_FLOATING_EVENT = "Congratulation!! You have added a Floating Event to MapleSyrup :)";
const string EventStorage::ADDED_NORMAL_EVENT = "Well Done!! You have added an Event to MapleSyrup :)";

const int EventStorage::INVALID = -1 ;
	
const std::string EventStorage::currentFile = "mytext.txt";

//CONSTRUCTOR, DESTRUCTOR
//read all from text file first to have past memory

EventStorage::EventStorage(void)
{
	readToCurrentContent();
}

EventStorage::~EventStorage(void)
{
}
	//METHODS
void EventStorage::readToCurrentContent(){
	
	std::ifstream readFile(currentFile);
	std::string textLine, name, description, feedback, tags, startDateYear, startDateMonth, startDateDay, startDateHour, startDateMin, endDateYear, endDateMonth, endDateDay, endDateHour, endDateMin, id;

	getline(readFile, textLine);
	while(!readFile.eof()){

		Event* tempEvent = new Event;

		if(textLine == "0"){					//Normal case
			//getinfo from textfile;
			getline(readFile, name);
			//cin event times
			getline(readFile, startDateYear);
			getline(readFile, startDateMonth);
			getline(readFile, startDateDay);
			getline(readFile, startDateHour);
			getline(readFile, startDateMin);
			getline(readFile, endDateYear);
			getline(readFile, endDateMonth);
			getline(readFile, endDateDay);
			getline(readFile, endDateHour);
			getline(readFile, endDateMin);
		
			getline(readFile, description);
			getline(readFile, feedback);
			getline(readFile, id);
			//getline(readFile, tags);
			//createFile
			tempEvent->setIsFloating(false); //stringToBool
			tempEvent->setName(name);
			tempEvent->setDescription(description);
			tempEvent->setFeedback(feedback);
			tempEvent->setID(atoi(id.c_str()));
			tempEvent->setStartTime(atoi(startDateHour.c_str()),atoi(startDateMin.c_str()));
			tempEvent->setStartDate(atoi(startDateDay.c_str()),atoi(startDateMonth.c_str()),atoi(startDateYear.c_str()));
			tempEvent->setEndTime(atoi(endDateHour.c_str()),atoi(endDateMin.c_str()));
			tempEvent->setEndDate(atoi(endDateDay.c_str()),atoi(endDateMonth.c_str()),atoi(endDateYear.c_str()));
			//split tags
			//tempEvent->setTags();
			currentContent.push_back(*tempEvent);
		} else if(textLine == "1"){				//floatingEvent
			//getinfo from textfile
			getline(readFile, name);
			getline(readFile, startDateYear);
			getline(readFile, startDateMonth);
			getline(readFile, startDateDay);
			getline(readFile, startDateHour);
			getline(readFile, startDateMin);
			getline(readFile, endDateYear);
			getline(readFile, endDateMonth);
			getline(readFile, endDateDay);
			getline(readFile, endDateHour);
			getline(readFile, endDateMin);
			getline(readFile, description);
			getline(readFile, feedback);
			getline(readFile, id);
			//getline(readFile, tags);
			//createFile
			tempEvent->setIsFloating(true);
			tempEvent->setName(name);
			tempEvent->setDescription(description);
			tempEvent->setFeedback(feedback);
			tempEvent->setID(atoi(id.c_str()));
			//split tags
			//tempEvent->setTags();
			currentFloatingContent.push_back(*tempEvent);
		}
		delete tempEvent;
		getline(readFile, textLine);			//takes in 0/1 for isFloating check
	}
	readFile.close();
}

void EventStorage::writeToCurrentFile(){
	std::ofstream writeFile(currentFile);
	
	for(auto i=0;i<currentContent.size();i++){
		writeFile 
			<< boolToString(currentContent[i].getIsFloating()) << std::endl 
			<< currentContent[i].getName() << std::endl 
			<< tmToString(currentContent[i]) << std::endl
			<< currentContent[i].getDescription() << std::endl
			<< currentContent[i].getFeedback() << std::endl
			<< currentContent[i].getID() << std::endl;
		
		//for(auto iter = (currentContent[i].getTags()).begin(); iter != (currentContent[i].getTags()).end(); iter++)
		//	writeFile << " " << *iter << std::endl;
	}	
	for(auto i=0;i<currentFloatingContent.size();i++){
		writeFile 
			<< boolToString(currentFloatingContent[i].getIsFloating()) << std::endl 
			<< currentFloatingContent[i].getName() << std::endl 
			<< '\n' << '\n' << '\n' << '\n' << '\n' << '\n' << '\n' << '\n' << '\n' << std::endl
			<< currentFloatingContent[i].getDescription() << std::endl
			<< currentFloatingContent[i].getFeedback() << std::endl
			<< currentFloatingContent[i].getID() << std::endl;
		
		//for(auto iter = (currentContent[i].getTags()).begin(); iter != (currentContent[i].getTags()).end(); iter++)
		//	writeFile << " " << *iter << std::endl;
	}


	writeFile.close();
}

string EventStorage::boolToString(bool isFloatingBool){
	if(isFloatingBool){
		return "1";
	} else{
		return "0";
	}
}

string EventStorage::tmToString(Event convertEvent){
	std::ostringstream oss;

	oss << convertEvent.getStartDate().tm_year << std::endl << convertEvent.getStartDate().tm_mon << std::endl << convertEvent.getStartDate().tm_mday
		<< std::endl << convertEvent.getStartDate().tm_hour << std::endl << convertEvent.getStartDate().tm_min << std::endl;
	
	oss << convertEvent.getEndDate().tm_year << std::endl << convertEvent.getEndDate().tm_mon << std::endl << convertEvent.getEndDate().tm_mday
		<< std::endl << convertEvent.getEndDate().tm_hour << std::endl << convertEvent.getEndDate().tm_min;

	return oss.str();
}

vector<Event> EventStorage::addEvent(Event newEvent){  //return eventvector with all events on that day
	vector<Event> returnToLogicVector;

	if(newEvent.getIsFloating()){
		newEvent.setFeedback(ADDED_FLOATING_EVENT); 
		currentFloatingContent.push_back(newEvent);
		returnToLogicVector = currentFloatingContent;
	} else{
		newEvent.setFeedback(ADDED_NORMAL_EVENT); 
		currentContent.push_back(newEvent);
		returnToLogicVector = showDay(newEvent.getStartDate().tm_mday,newEvent.getStartDate().tm_mon,newEvent.getStartDate().tm_year);
	}
	writeToCurrentFile();

	return returnToLogicVector; 
}

vector<Event> EventStorage::showAllNormalEvent(){
	vector<Event> sortResults;
	sortResults = sortEventVectorByDate(currentContent);
	return sortResults; 
}
vector<Event> EventStorage::showAllFloatingEvent(){
	return currentFloatingContent;
}

vector<Event> EventStorage::sortEventVectorByDate(vector<Event> eventVectorToSort){

	Event tempEvent;
	if(eventVectorToSort.size()<=1){
		return eventVectorToSort;
	} else{
		for(auto i=0;i<(eventVectorToSort.size()-1);i++){
			for(auto j=i+1;j<eventVectorToSort.size();j++){
				if(isLatterTimeSmaller(eventVectorToSort[i],eventVectorToSort[j])){
					tempEvent = eventVectorToSort[j];
					eventVectorToSort[j] = eventVectorToSort[i];
					eventVectorToSort[i] = tempEvent;
				}
			}
		}
	}
	return eventVectorToSort;
}
	
bool EventStorage::isLatterTimeSmaller(Event eventTime1,Event eventTime2) //returns true is latter time is smaller
{	
	bool isEarlier = false;

	if(eventTime1.getStartDate().tm_year != eventTime2.getStartDate().tm_year){
		return isLatterYearSmaller(eventTime1,eventTime2);
	} else if(eventTime1.getStartDate().tm_mon != eventTime2.getStartDate().tm_mon){
		return isLatterMonthSmaller(eventTime1,eventTime2);
	} else if(eventTime1.getStartDate().tm_mday != eventTime2.getStartDate().tm_mday){
		return isLatterDaySmaller(eventTime1,eventTime2);
	} else if(eventTime1.getStartDate().tm_hour != eventTime2.getStartDate().tm_hour){
		return isLatterHourSmaller(eventTime1,eventTime2);
	} else if(eventTime1.getStartDate().tm_min != eventTime2.getStartDate().tm_min){
		return isLatterMinSmaller(eventTime1,eventTime2);
	} else		//Start time is equal
		return isEarlier;
}
bool EventStorage::isLatterHourSmaller(Event eventTime1, Event eventTime2) //returns true is eT2 is earlier
{
	int startHour, endHour;
	bool isHourBigger = false;

	startHour = eventTime1.getStartDate().tm_hour;
	endHour = eventTime2.getStartDate().tm_hour;
	if(startHour > endHour)
		isHourBigger = true;

	return isHourBigger;
}

bool EventStorage::isLatterYearSmaller(Event eventTime1, Event eventTime2) //returns true is eT2 is earlier
{
	int startYear, endYear;
	bool isYearBigger = false;

	startYear = eventTime1.getStartDate().tm_year;
	endYear = eventTime2.getStartDate().tm_year;
	if(startYear > endYear){
		isYearBigger = true;
	}
	return isYearBigger;
}

bool EventStorage::isLatterMonthSmaller(Event eventTime1, Event eventTime2)  //returns true is eT2 is earlier
{
	int startMonth, endMonth;
	bool isMonthBigger = false;

	startMonth = eventTime1.getStartDate().tm_mon;
	endMonth = eventTime2.getStartDate().tm_mon;
	if(startMonth > endMonth)
		isMonthBigger = true;

	return isMonthBigger;
}

bool EventStorage::isLatterDaySmaller(Event eventTime1, Event eventTime2)  //returns true is eT2 is earlier
{
	int startDay, endDay;
	bool isDayBigger = false;

	startDay = eventTime1.getStartDate().tm_mday;
	endDay = eventTime2.getStartDate().tm_mday;
	if(startDay > endDay)
		isDayBigger = true;

	return isDayBigger;
}

bool EventStorage::isLatterMinSmaller(Event eventTime1, Event eventTime2) //returns true is eT2 is earlier
{
	int startMin, endMin;
	bool isMinBigger = false;

	startMin = eventTime1.getStartDate().tm_min;
	endMin = eventTime2.getStartDate().tm_min;
	if(startMin > endMin)
		isMinBigger = true;

	return isMinBigger;
}

vector<Event> EventStorage::showDay(int dayToShow, int monthToShow, int yearToShow){
	
	bool isFound=false;
	vector<Event> showDayResults;
	vector<Event> sortResults;

	sortResults = sortEventVectorByDate(currentContent);

	for(auto i=0;i<sortResults.size();i++){
		if((sortResults[i].getStartDate().tm_year == yearToShow) && (sortResults[i].getStartDate().tm_mon == monthToShow) && (sortResults[i].getStartDate().tm_mday == dayToShow)){
			isFound = true;
			showDayResults.push_back(sortResults[i]);
			isFound = false;
		}
	}
	return showDayResults;
}

//delete method
vector<Event> EventStorage::checkMultipleResults(string eventName){
	
	vector<Event> eventVector, floatingEventVector;
	Search search;

	eventVector = search.searchForEventWithEventName(eventName, currentContent);
	floatingEventVector = search.searchForEventWithEventName(eventName, currentFloatingContent);
	eventVector.insert( eventVector.end(), floatingEventVector.begin(), floatingEventVector.end() );

	return eventVector;
}
vector<Event> EventStorage::deleteEvent(int eventID, Event eventToBeDeleted){
	
	int indexOfEventID = INVALID; 
	Search search;
	vector<Event> returnToLogicVector;

	if(eventID == INVALID){ //event is not a user display Index
		eventID = eventToBeDeleted.getID(); //set relevant eventID 
	}
	//Normal Case
	indexOfEventID = search.searchForIndexWithEventID(eventID,currentContent);
	if(indexOfEventID > INVALID){ 
		eventToBeDeleted = currentContent[indexOfEventID];
		currentContent.erase(currentContent.begin() + indexOfEventID);
		returnToLogicVector = showDay(eventToBeDeleted.getStartDate().tm_mday,eventToBeDeleted.getStartDate().tm_mon,eventToBeDeleted.getStartDate().tm_year);
	}else{ //Floating Case
		indexOfEventID = search.searchForIndexWithEventID(eventID,currentFloatingContent);
		if(indexOfEventID > INVALID){
			eventToBeDeleted = currentFloatingContent[indexOfEventID];
			currentFloatingContent.erase(currentFloatingContent.begin() + indexOfEventID);
			returnToLogicVector = currentFloatingContent;
		}
	}
	
	writeToCurrentFile();
	return returnToLogicVector;

	//saving in archive for Undo
	//archiveObject.setCommandType("delete");
	//archiveObject.setArchiveEvent(eventToBeDeleted);
	//archiveContent.push_back(archiveObject);
}

vector<Event> EventStorage::editEvent(int eventID, Event eventToBeEdited, Event editedEvent){
	
	Search search;
	int indexOfEventID = INVALID; 
	vector<Event> returnToLogicVector;
	
	if(eventID == INVALID){ //event is not a user display Index)		
		eventID = eventToBeEdited.getID();  //set relevant eventID
	}
	//Normal Case
	indexOfEventID = search.searchForIndexWithEventID(eventID,currentContent); //how to change to floating?
	if(indexOfEventID > INVALID){ 
		if(editedEvent.getName() != ""){
			(currentContent[indexOfEventID]).setName(editedEvent.getName());
		}
		if(editedEvent.getStartDate().tm_mday != 100){ //change magic number
			(currentContent[indexOfEventID]).setStartDate(editedEvent.getStartDate().tm_mday,editedEvent.getStartDate().tm_mon,editedEvent.getStartDate().tm_year);
		}
		if(editedEvent.getEndDate().tm_mday != 100){
			(currentContent[indexOfEventID]).setEndDate(editedEvent.getEndDate().tm_mday,editedEvent.getEndDate().tm_mon,editedEvent.getStartDate().tm_year);
		}
		if(editedEvent.getStartDate().tm_hour != 100){
			(currentContent[indexOfEventID]).setStartTime(editedEvent.getStartDate().tm_hour,editedEvent.getStartDate().tm_min);
		}
		if(editedEvent.getEndDate().tm_min != 100){
			(currentContent[indexOfEventID]).setEndTime(editedEvent.getEndDate().tm_hour,editedEvent.getEndDate().tm_min);
		}
		if(editedEvent.getDescription() != ""){
			(currentContent[indexOfEventID]).setDescription(editedEvent.getDescription());
		}
		returnToLogicVector = showDay(eventToBeEdited.getStartDate().tm_mday,eventToBeEdited.getStartDate().tm_mon,eventToBeEdited.getStartDate().tm_year);
	}
	else{ //Floating Case
		indexOfEventID = search.searchForIndexWithEventID(eventID,currentFloatingContent);
		if(indexOfEventID > INVALID){
			if(editedEvent.getName() != ""){
				(currentFloatingContent[indexOfEventID]).setName(editedEvent.getName());		
			}			
			if(editedEvent.getEndDate().tm_mday != 100){
				(currentFloatingContent[indexOfEventID]).setEndDate(editedEvent.getEndDate().tm_mday,editedEvent.getEndDate().tm_mon,editedEvent.getStartDate().tm_year);
			}
			if(editedEvent.getStartDate().tm_hour != 100){
				(currentFloatingContent[indexOfEventID]).setStartTime(editedEvent.getStartDate().tm_hour,editedEvent.getStartDate().tm_min);
				(currentFloatingContent[indexOfEventID]).setIsFloating(false);			//set time only?
			}
			if(editedEvent.getEndDate().tm_min != 100){
				(currentFloatingContent[indexOfEventID]).setEndTime(editedEvent.getEndDate().tm_hour,editedEvent.getEndDate().tm_min);
			}
			if(editedEvent.getDescription() != ""){
				(currentFloatingContent[indexOfEventID]).setDescription(editedEvent.getDescription());
			}
			if(editedEvent.getStartDate().tm_mday != 100){
				(currentFloatingContent[indexOfEventID]).setStartDate(editedEvent.getStartDate().tm_mday,editedEvent.getStartDate().tm_mon,editedEvent.getStartDate().tm_year);
				(currentFloatingContent[indexOfEventID]).setIsFloating(false);
				returnToLogicVector = addEvent(currentFloatingContent[indexOfEventID]);  //add to currentcontent
				currentFloatingContent.erase(currentFloatingContent.begin() + indexOfEventID); //delete from currentfloatingcontent
			} else{
				returnToLogicVector = currentFloatingContent;
			}
		}
	}
	
	writeToCurrentFile();
	return returnToLogicVector;

	//store in event archive
}
/*
//search all vector and all component of events save into events of vector results
vector<Event> EventStorage::searchAllComponentsOfEvent(string informationToSearch){
	bool isFound=false;
	vector<Event> searchResults;

	for(int i=0;i<currentContent.size();i++){
		if(currentContent[i].getDescription().find(informationToSearch) != std::string::npos)
			isFound = true;
		if(currentContent[i].getName().find(informationToSearch) != std::string::npos)
			isFound = true;
		//search for tags not yet included			
		if(currentContent[i].getStartDate().tm_year == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getStartDate().tm_mon == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getStartDate().tm_mday == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getStartDate().tm_hour == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getStartDate().tm_min == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getEndDate().tm_year == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getEndDate().tm_mon == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getEndDate().tm_mday == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getEndDate().tm_hour == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getEndDate().tm_min == atoi(informationToSearch.c_str()))
			isFound = true;

	if(isFound){
		searchResults.push_back(currentContent[i]);
	}
	isFound=false;
	}
	return searchResults;
}
*/