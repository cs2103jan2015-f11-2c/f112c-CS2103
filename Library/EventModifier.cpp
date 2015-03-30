#include "EventModifier.h"

const int EventModifier::NOT_FOUND = -1 ;
const int EventModifier::DEFAULT = 100;

//CONSTRUCTOR, DESTRUCTOR

EventModifier::EventModifier(void)
{
}

EventModifier::~EventModifier(void)
{
}

//Add method
//Precondition takes in an event
//returns a vector of Events of the added date
vector<Event> EventModifier::add(Event newEvent){  
	logger.logStoragePosition(ADD);
	vector<Event> toLogic;
	if(newEvent.getIsFloating()){
		addfloat(newEvent);
		toLogic = organiser.showAllFloatingEvent();	
	} else{
		addNormal(newEvent);
		toLogic = organiser.showDatesFromNormalContent(newEvent);
	}
	return toLogic; 
}

//Add support methods
void EventModifier::addfloat(Event newEvent){
	vector<Event> tempContents;
	tempContents = EventStorage::storage().getFloatingContent();
	tempContents.push_back(newEvent);
	EventStorage::storage().setFloatingContent(tempContents);
}
void EventModifier::addNormal(Event newEvent){
	vector<Event> tempContents;
	tempContents = EventStorage::storage().getNormalContent();
	tempContents.push_back(newEvent);
	EventStorage::storage().setNormalContent(tempContents);
}

//delete method
vector<Event> EventModifier::del(int eventID, Event eventToBeDeleted){
	logger.logStoragePosition(DELETE);
	
	int index = NOT_FOUND; 
	vector<Event> toLogic;

	//extract ID if event is not in display
	if(eventID == NOT_FOUND){ 
		eventID = eventToBeDeleted.getID(); //set relevant eventID 
	}

	assert(eventID != NOT_FOUND);

	index = findNormalIndex(eventID);
	logger.logStorageIntData("The index from current content is: ",index);
	
	if(index > NOT_FOUND){  	//Normal Case
		toLogic = deleteNormal(index);
	} else{						
		index = findFloatingIndex(eventID);
		if(index > NOT_FOUND){  //Floating Case
			toLogic = deletefloat(index);
		}
	}
	logger.logStoragePosition("Leaving deleteEvent");
	return toLogic;
}

//support methods
int EventModifier::findNormalIndex(int eventID){
	vector<Event> tempContents = EventStorage::storage().getNormalContent();
	int index = searcher.searchIndexWithID(eventID,tempContents);
	return index;
}

int EventModifier::findFloatingIndex(int eventID){
	vector<Event> tempContents = EventStorage::storage().getFloatingContent();
	int index = searcher.searchIndexWithID(eventID,tempContents);
	return index;
}

//delete support methods
vector<Event> EventModifier::deleteNormal(int index){
	
	vector<Event> tempContents = EventStorage::storage().getNormalContent();
	Event deletedEvent = tempContents[index];
	tempContents.erase(tempContents.begin() + index);
	EventStorage::storage().setNormalContent(tempContents);

	logger.logStorageStringData("deletedNormal",deletedEvent.getName());
	vector<Event> toLogic = organiser.showDatesFromNormalContent(deletedEvent);	
	return toLogic;
}


vector<Event> EventModifier::deletefloat(int index){
	
	vector<Event> tempContents = EventStorage::storage().getFloatingContent();
	Event deletedEvent = tempContents[index];
	tempContents.erase(tempContents.begin() + index);
	EventStorage::storage().setFloatingContent(tempContents);

	logger.logStorageStringData("deletedFloating",deletedEvent.getName());
	vector<Event> toLogic = organiser.showAllFloatingEvent();	
	return toLogic;
}

//edit method
vector<Event> EventModifier::edit(int eventID, Event eventToBeEdited, Event editedEvent){
	logger.logStoragePosition(EDIT);
	
	int index = NOT_FOUND; 
	vector<Event> toLogic;

	//extract ID if event is not in display	
	if(eventID == NOT_FOUND){ 
		eventID = eventToBeEdited.getID();  
	}

	assert(eventID != NOT_FOUND);
	
	index = findNormalIndex(eventID);
	if(index > NOT_FOUND){		//Normal Case
		toLogic = editNormal(index, editedEvent);
	} else{ 
		index = findFloatingIndex(eventID);
		if(index > NOT_FOUND){  //Floating Case
			toLogic = editFloating(index, editedEvent);
		}
	}
	logger.logStoragePosition("Leaving editEvent");
	return toLogic;
}

//edit support functions
vector<Event> EventModifier::editNormal(int index, Event editedEvent){
	
	vector<Event> tempContents = EventStorage::storage().getNormalContent();

	if(editedEvent.getName() != ""){
		(tempContents[index]).setName(editedEvent.getName());
	}
	if(editedEvent.getStartDate().tm_mday != DEFAULT){ 
		(tempContents[index]).setStartDate(editedEvent.getStartDate().tm_mday,editedEvent.getStartDate().tm_mon,editedEvent.getStartDate().tm_year);
	}
	if(editedEvent.getEndDate().tm_mday != DEFAULT){
		(tempContents[index]).setEndDate(editedEvent.getEndDate().tm_mday,editedEvent.getEndDate().tm_mon,editedEvent.getStartDate().tm_year);
	}
	if(editedEvent.getStartDate().tm_hour != DEFAULT){
		(tempContents[index]).setStartTime(editedEvent.getStartDate().tm_hour,editedEvent.getStartDate().tm_min);
	}
	if(editedEvent.getEndDate().tm_min != DEFAULT){
		(tempContents[index]).setEndTime(editedEvent.getEndDate().tm_hour,editedEvent.getEndDate().tm_min);
	}
	if(editedEvent.getImportanceLevel() != DEFAULT){ //check with che
		(tempContents[index]).setImportanceLevel(editedEvent.getImportanceLevel());
	}
	
	EventStorage::storage().setNormalContent(tempContents);
	logger.logStorageStringData("editedNormal",tempContents[index].getName());

	tempContents = organiser.showDatesFromNormalContent(tempContents[index]);
	return tempContents;
}

vector<Event> EventModifier::editFloating(int index, Event editedEvent){ //check if float to float or float to normal
	
	vector<Event> toLogic, tempContents = EventStorage::storage().getFloatingContent();
	
	if(editedEvent.getName() != ""){
		(tempContents[index]).setName(editedEvent.getName());		
	}			
	if(editedEvent.getEndDate().tm_mday != DEFAULT){
		(tempContents[index]).setEndDate(editedEvent.getEndDate().tm_mday,editedEvent.getEndDate().tm_mon,editedEvent.getStartDate().tm_year);
	}
	if(editedEvent.getStartDate().tm_hour != DEFAULT){
		(tempContents[index]).setStartTime(editedEvent.getStartDate().tm_hour,editedEvent.getStartDate().tm_min);
		(tempContents[index]).setIsFloating(false);			//set time only?
	}
	if(editedEvent.getEndDate().tm_min != DEFAULT){
		(tempContents[index]).setEndTime(editedEvent.getEndDate().tm_hour,editedEvent.getEndDate().tm_min);
	}
	if(editedEvent.getDescription() != ""){
		(tempContents[index]).setDescription(editedEvent.getDescription());
	} 
	if(editedEvent.getStartDate().tm_mday != DEFAULT){ //change to normal event
		(tempContents[index]).setStartDate(editedEvent.getStartDate().tm_mday,editedEvent.getStartDate().tm_mon,editedEvent.getStartDate().tm_year);
		(tempContents[index]).setIsFloating(false);

		del(NOT_FOUND,tempContents[index]);  //delete from floatingContent
		toLogic = add(tempContents[index]);  //add to normalContent		
	} else{
		EventStorage::storage().setFloatingContent(tempContents);
		logger.logStorageStringData("editedFloating",tempContents[index].getName());
		toLogic = organiser.showAllFloatingEvent();
	}
	return toLogic;
}