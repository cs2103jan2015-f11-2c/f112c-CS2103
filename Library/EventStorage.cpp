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
	vector<Event> returnToLogicVector;

	if(newEvent.getIsFloating()){
		newEvent.setFeedback(ADDED_FLOATING_EVENT); 
		currentFloatingContent.push_back(newEvent);
		returnToLogicVector = currentFloatingContent;
	} else{
		newEvent.setFeedback(ADDED_NORMAL_EVENT); 
		currentContent.push_back(newEvent);
		returnToLogicVector = eventOrganiser.showDay(newEvent.getStartDate().tm_mday,newEvent.getStartDate().tm_mon,newEvent.getStartDate().tm_year, currentContent);
	}
	writeToCurrentFile();

	return returnToLogicVector; 
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
	vector<Event> returnToLogicVector;

	if(eventID == INVALID){ //event is not a user display Index
		eventID = eventToBeDeleted.getID(); //set relevant eventID 
	}
	//Normal Case
	indexOfEventID = search.searchForIndexWithEventID(eventID,currentContent);
	if(indexOfEventID > INVALID){ 
		eventToBeDeleted = currentContent[indexOfEventID];
		currentContent.erase(currentContent.begin() + indexOfEventID);
		returnToLogicVector = eventOrganiser.showDay(eventToBeDeleted.getStartDate().tm_mday,eventToBeDeleted.getStartDate().tm_mon,eventToBeDeleted.getStartDate().tm_year, currentContent);
	}else{ //Floating Case
		indexOfEventID = search.searchForIndexWithEventID(eventID,currentFloatingContent);
		if(indexOfEventID > INVALID){
			eventToBeDeleted = currentFloatingContent[indexOfEventID];
			currentFloatingContent.erase(currentFloatingContent.begin() + indexOfEventID);
			returnToLogicVector = eventOrganiser.showAllFloatingEvent(currentFloatingContent);
		}
	}
	
	writeToCurrentFile();
	return returnToLogicVector;

	//saving in archive for Undo
	//archiveObject.setCommandType("delete");
	//archiveObject.setArchiveEvent(eventToBeDeleted);
	//archiveContent.push_back(archiveObject);
}

//edit method
vector<Event> EventStorage::editEvent(int eventID, Event eventToBeEdited, Event editedEvent){
	
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
		returnToLogicVector = eventOrganiser.showDay(eventToBeEdited.getStartDate().tm_mday,eventToBeEdited.getStartDate().tm_mon,eventToBeEdited.getStartDate().tm_year, currentContent);
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
				returnToLogicVector = eventOrganiser.showAllFloatingEvent(currentFloatingContent);
			}
		}
	}
	
	writeToCurrentFile();
	return returnToLogicVector;

	//store in event archive
}

//getters for testing
vector<Event> EventStorage::getAllNormalEvents(){
	return eventOrganiser.showAllNormalEvent(currentContent);
}
vector<Event> EventStorage::getAllFloatingEvents(){
	return eventOrganiser.showAllFloatingEvent(currentFloatingContent);
}
