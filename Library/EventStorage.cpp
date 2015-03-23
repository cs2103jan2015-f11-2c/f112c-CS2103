#include "EventStorage.h"

//These are messages to give the user feedback on what the program is doing.

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
			<< conversion.boolToString(currentContent[i].getIsFloating()) << std::endl 
			<< currentContent[i].getName() << std::endl 
			<< conversion.tmToString(currentContent[i]) << std::endl
			<< currentContent[i].getDescription() << std::endl
			<< currentContent[i].getFeedback() << std::endl
			<< currentContent[i].getID() << std::endl;
	}	
	for(auto i=0;i<currentFloatingContent.size();i++){
		writeFile 
			<< conversion.boolToString(currentFloatingContent[i].getIsFloating()) << std::endl 
			<< currentFloatingContent[i].getName() << std::endl 
			<< '\n' << '\n' << '\n' << '\n' << '\n' << '\n' << '\n' << '\n' << '\n' << std::endl
			<< currentFloatingContent[i].getDescription() << std::endl
			<< currentFloatingContent[i].getFeedback() << std::endl
			<< currentFloatingContent[i].getID() << std::endl;	
	}
	writeFile.close();
}

//add method
vector<Event> EventStorage::addEvent(Event newEvent){  //return eventvector with all events on that day
	logger.logStoragePosition("addEvent");
	vector<Event> returnToLogicVector;

	if(newEvent.getIsFloating()){
		logger.logStorageStringData("addFloat",newEvent.getName());
		currentFloatingContent.push_back(newEvent);
		returnToLogicVector = currentFloatingContent;
	} else{
		logger.logStorageStringData("addNormal",newEvent.getName());
		currentContent.push_back(newEvent);
		returnToLogicVector = showDates(newEvent);
	}
	writeToCurrentFile();

	return returnToLogicVector; 
}

//delete method
vector<Event> EventStorage::checkMultipleResults(string eventName){
	logger.logStoragePosition("checkMultipleResults");
	
	vector<Event> eventVector, floatingEventVector;
	Search search;
	
	eventVector = search.searchForEventWithEventName(eventName, currentContent);
	floatingEventVector = search.searchForEventWithEventName(eventName, currentFloatingContent);
	eventVector.insert( eventVector.end(), floatingEventVector.begin(), floatingEventVector.end() );
	
	return eventVector;
}
vector<Event> EventStorage::deleteEvent(int eventID, Event eventToBeDeleted){
	logger.logStoragePosition("deleteEvent");
	
	int indexOfEventID = INVALID; 
	vector<Event> returnToLogicVector;

	if(eventID == INVALID){ //event is not a user display Index
		eventID = eventToBeDeleted.getID(); //set relevant eventID 
		logger.logStorageIntData("eventID to delete: ",eventID);
	}
	//assert(eventID != INVALID);
	//Normal Case
	logger.logStoragePosition("entering search");
	indexOfEventID = search.searchForIndexWithEventID(eventID,currentContent);
	logger.logStorageIntData("getting index from currentContent",indexOfEventID);
	if(indexOfEventID > INVALID){ 
		eventToBeDeleted = currentContent[indexOfEventID];
		logger.logStorageStringData("deleteNormal",eventToBeDeleted.getName());
		currentContent.erase(currentContent.begin() + indexOfEventID);
		returnToLogicVector = showDates(eventToBeDeleted);	
	} else{ //Floating Case
		indexOfEventID = search.searchForIndexWithEventID(eventID,currentFloatingContent);
		if(indexOfEventID > INVALID){
			logger.logStorageStringData("deleteFloat",eventToBeDeleted.getName());
			eventToBeDeleted = currentFloatingContent[indexOfEventID];
			currentFloatingContent.erase(currentFloatingContent.begin() + indexOfEventID);
			returnToLogicVector = eventOrganiser.showAllFloatingEvent(currentFloatingContent);
		}
	}
	
	writeToCurrentFile();
	logger.logStoragePosition("Leaving deleteEvent");
	return returnToLogicVector;

	//saving in archive for Undo
	//archiveObject.setCommandType("delete");
	//archiveObject.setArchiveEvent(eventToBeDeleted);
	//archiveContent.push_back(archiveObject);
}

//edit method
vector<Event> EventStorage::editEvent(int eventID, Event eventToBeEdited, Event editedEvent){
	logger.logStoragePosition("editEvent");
	
	int indexOfEventID = INVALID; 
	vector<Event> returnToLogicVector;
	
	if(eventID == INVALID){ //event is not a user display Index)		
		eventID = eventToBeEdited.getID();  //set relevant eventID
	}
	assert(eventID != INVALID);
	//Normal Case
	indexOfEventID = search.searchForIndexWithEventID(eventID,currentContent); //how to change to floating?
	if(indexOfEventID > INVALID){ 
		logger.logStorageStringData("editNormal",eventToBeEdited.getName());
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
		returnToLogicVector = showDates(editedEvent);
	}
	else{ //Floating Case
		logger.logStorageStringData("editFloating",eventToBeEdited.getName());
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
				returnToLogicVector = eventOrganiser.showAllFloatingEvent(currentFloatingContent);
			}
		}
	}
	
	writeToCurrentFile();
	logger.logStoragePosition("Leaving editEvent");
	return returnToLogicVector;

	//store in event archive
}

vector<Event> EventStorage::showDates(Event eventWithStartEndTimes){
	logger.logStoragePosition("showDates");
	return eventOrganiser.showDateRange(eventWithStartEndTimes,currentContent);
}


//getters
vector<Event> EventStorage::getAllNormalEvents(){
	return eventOrganiser.showAllNormalEvent(currentContent);
}
vector<Event> EventStorage::getAllFloatingEvents(){
	return eventOrganiser.showAllFloatingEvent(currentFloatingContent);
}
vector<Event> EventStorage::searchAllComponents(string infoToSearch, vector<Event> contentToSearch){
	return search.searchAllComponentsOfEvent(infoToSearch,contentToSearch);
}
