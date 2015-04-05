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
vector<Event> EventModifier::add(Event newEvent) {  
	logger.logStoragePosition(ADD);
	vector<Event> toLogic;
	if (newEvent.getIsFloating()) {
		addfloat(newEvent);
		toLogic = organiser.showAllFloatingCurrent();	
	} else {
		addNormal(newEvent);
		toLogic = organiser.showDatesFromNormalContent(newEvent);
	}
	return toLogic; 
}

//Add support methods
void EventModifier::addfloat(Event newEvent) {
	vector<Event> tempContents;
	tempContents = organiser.allFloatingCurrent();
	tempContents.push_back(newEvent);
	organiser.saveFloating(tempContents);
}
void EventModifier::addNormal(Event newEvent) {
	vector<Event> tempContents;
	tempContents = organiser.allNormalCurrent();
	tempContents.push_back(newEvent);
	organiser.saveNormal(tempContents);
}

//delete method
vector<Event> EventModifier::del(int eventID, Event eventToBeDeleted) {
	logger.logStoragePosition(DELETE);
	
	int index = NOT_FOUND; 
	vector<Event> toLogic;

	//extract ID if event is not in display
	if (eventID == NOT_FOUND) { 
		eventID = eventToBeDeleted.getID(); //set relevant eventID 
	}

	assert(eventID != NOT_FOUND);

	index = findNormalIndex(eventID);
	logger.logStorageIntData("The index from current content is: ",index);
	
	if (index > NOT_FOUND) {  	//Normal Case
		toLogic = deleteNormal(index);
	} else {						
		index = findFloatingIndex(eventID);
		if (index > NOT_FOUND) {  //Floating Case
			toLogic = deletefloat(index);
		}
	}
	logger.logStoragePosition("Leaving deleteEvent");
	return toLogic;
}

//support methods
int EventModifier::findNormalIndex(int eventID) {
	vector<Event> tempContents = organiser.allNormalCurrent();
	int index = searcher.searchIndexWithID(eventID,tempContents);
	return index;
}

int EventModifier::findFloatingIndex(int eventID) {
	vector<Event> tempContents = organiser.allFloatingCurrent();
	int index = searcher.searchIndexWithID(eventID,tempContents);
	return index;
}

//delete support methods
vector<Event> EventModifier::deleteNormal(int index) {
	
	vector<Event> tempContents = organiser.allNormalCurrent();
	Event deletedEvent = tempContents[index];
	tempContents.erase(tempContents.begin() + index);
	organiser.saveNormal(tempContents);

	logger.logStorageStringData("deletedNormal",deletedEvent.getName());
	vector<Event> toLogic = organiser.showDatesFromNormalContent(deletedEvent);	
	return toLogic;
}


vector<Event> EventModifier::deletefloat(int index) {
	
	vector<Event> tempContents = organiser.allFloatingCurrent();
	Event deletedEvent = tempContents[index];
	tempContents.erase(tempContents.begin() + index);
	organiser.saveFloating(tempContents);

	logger.logStorageStringData("deletedFloating",deletedEvent.getName());
	vector<Event> toLogic = organiser.showAllFloatingCurrent();	
	return toLogic;
}

//edit method
vector<Event> EventModifier::edit(int eventID, Event eventToBeEdited, Event editedEvent) {
	logger.logStoragePosition(EDIT);
	
	int index = NOT_FOUND; 
	vector<Event> toLogic;

	//extract ID if event is not in display	
	if (eventID == NOT_FOUND) { 
		eventID = eventToBeEdited.getID();  
	}

	assert(eventID != NOT_FOUND);
	
	index = findNormalIndex(eventID);
	if (index > NOT_FOUND) {		//Normal Case
		toLogic = editNormal(index, editedEvent);
	} else { 
		index = findFloatingIndex(eventID);
		if (index > NOT_FOUND) {  //Floating Case
			toLogic = editFloating(index, editedEvent);
		}
	}
	logger.logStoragePosition("Leaving editEvent");
	return toLogic;
}

//edit support functions
vector<Event> EventModifier::editNormal(int index, Event editedEvent) {
	
	vector<Event> tempContents = organiser.allNormalCurrent();

	if (editedEvent.getName() != "") {
		(tempContents[index]).setName(editedEvent.getName());
	}
	if (editedEvent.getStartDate().tm_mday != DEFAULT) { 
		(tempContents[index]).setStartDate(editedEvent.getStartDate().tm_mday,editedEvent.getStartDate().tm_mon,editedEvent.getStartDate().tm_year);
	}
	if (editedEvent.getEndDate().tm_mday != DEFAULT) {
		(tempContents[index]).setEndDate(editedEvent.getEndDate().tm_mday,editedEvent.getEndDate().tm_mon,editedEvent.getStartDate().tm_year);
	}
	if (editedEvent.getStartDate().tm_hour != DEFAULT) {
		(tempContents[index]).setStartTime(editedEvent.getStartDate().tm_hour,editedEvent.getStartDate().tm_min);
	}
	if (editedEvent.getEndDate().tm_min != DEFAULT) {
		(tempContents[index]).setEndTime(editedEvent.getEndDate().tm_hour,editedEvent.getEndDate().tm_min);
	}
	if (editedEvent.getImportanceLevel() != NOT_FOUND) { 
		(tempContents[index]).setImportanceLevel(editedEvent.getImportanceLevel());
	}
	
	organiser.saveNormal(tempContents);
	logger.logStorageStringData("editedNormal",tempContents[index].getName());

	tempContents = organiser.showDatesFromNormalContent(tempContents[index]);
	return tempContents;
}

vector<Event> EventModifier::editFloating(int index, Event editedEvent) { //check if float to float or float to normal
	
	vector<Event> toLogic, tempContents = organiser.allFloatingCurrent();
	
	if (editedEvent.getName() != "") {
		(tempContents[index]).setName(editedEvent.getName());		
	}			
	if (editedEvent.getEndDate().tm_mday != DEFAULT) {
		(tempContents[index]).setEndDate(editedEvent.getEndDate().tm_mday,editedEvent.getEndDate().tm_mon,editedEvent.getStartDate().tm_year);
	}
	if (editedEvent.getStartDate().tm_hour != DEFAULT) {
		(tempContents[index]).setStartTime(editedEvent.getStartDate().tm_hour,editedEvent.getStartDate().tm_min);
		(tempContents[index]).setIsFloating(false);			//set time only?
	}
	if (editedEvent.getEndDate().tm_min != DEFAULT) {
		(tempContents[index]).setEndTime(editedEvent.getEndDate().tm_hour,editedEvent.getEndDate().tm_min);
	} 
	if (editedEvent.getImportanceLevel() != NOT_FOUND) {
		(tempContents[index]).setImportanceLevel(editedEvent.getImportanceLevel());
	}
	if (editedEvent.getStartDate().tm_mday != DEFAULT) { //change to normal event
		(tempContents[index]).setStartDate(editedEvent.getStartDate().tm_mday,editedEvent.getStartDate().tm_mon,editedEvent.getStartDate().tm_year);
		(tempContents[index]).setIsFloating(false);

		del(NOT_FOUND,tempContents[index]);  //delete from floatingContent
		toLogic = add(tempContents[index]);  //add to normalContent		
	} else {
		organiser.saveFloating(tempContents);
		logger.logStorageStringData("editedFloating",tempContents[index].getName());
		toLogic = organiser.showAllFloatingCurrent();
	}
	return toLogic;
}

vector<Event> EventModifier::complete(int eventID, Event completedEvent) {
	logger.logStoragePosition(COMPLETE);
	
	int index = NOT_FOUND; 
	vector<Event> toLogic;

	//extract ID if event is not in display
	if (eventID == NOT_FOUND) { 
		eventID = completedEvent.getID(); //set relevant eventID 
	}

	assert(eventID != NOT_FOUND);

	index = findNormalIndex(eventID);
	logger.logStorageIntData("The index from current content is: ",index);
	
	if (index > NOT_FOUND) {  	//Normal Case
		toLogic = completeNormal(index, eventID);
	} else {						
		index = findFloatingIndex(eventID);
		if (index > NOT_FOUND) {  //Floating Case
			toLogic = completeFloat(index);
		}
	}
	logger.logStoragePosition("Leaving completeEvent");
	return toLogic;
}

//complete support methods
vector<Event> EventModifier::completeNormal(int index, int eventID) {  //mark and push into completedcontent. pushback into delete vector to return to logic
	//mark complete
	vector<Event> tempContents = organiser.allNormalCurrent();

	vector<Event> completedEventDates = organiser.showDatesFromNormalContent(tempContents[index]);
	completedEventDates = markCompleted(eventID, completedEventDates);
	
	tempContents[index].setIsCompleted(true);
	organiser.saveNormal(tempContents);

	return completedEventDates;
}

vector<Event> EventModifier::markCompleted(int eventID, vector<Event> completedEventDates) {

	for (auto i = 0; i < completedEventDates.size(); i++) {
		if (completedEventDates[i].getID() == eventID) {
			completedEventDates[i].setIsCompleted(true);
		}
	}
	return completedEventDates;
}

vector<Event> EventModifier::completeFloat(int index) {
	//mark complete
	vector<Event> tempContents = organiser.allFloatingCurrent();
	tempContents[index].setIsCompleted(true);
	organiser.saveFloating(tempContents);
	return tempContents;
}

vector<Event> EventModifier::uncomplete(int eventID, Event UncompletedEvent) {
	logger.logStoragePosition(COMPLETE);
	
	int index = NOT_FOUND; 
	vector<Event> toLogic;

	//extract ID if event is not in display
	if (eventID == NOT_FOUND) { 
		eventID = UncompletedEvent.getID(); //set relevant eventID 
	}

	assert(eventID != NOT_FOUND);

	index = findNormalCompletedIndex(eventID);
	logger.logStorageIntData("The index from current content is: ",index);
	
	if (index > NOT_FOUND) {  	//Normal Case
		toLogic = uncompleteNormal(index, eventID);
	} else {						
		index = findFloatingCompletedIndex(eventID);
		if (index > NOT_FOUND) {  //Floating Case
			toLogic = uncompleteFloat(index);
		}
	}
	logger.logStoragePosition("Leaving uncompleteEvent");
	return toLogic;
}

vector<Event> EventModifier::uncompleteNormal(int index, int eventID) {  //mark and push into completedcontent. pushback into delete vector to return to logic
	//mark complete
	vector<Event> tempContents = organiser.allNormalCompleted();

	tempContents[index].setIsCompleted(false);
	organiser.saveNormalCompleted(tempContents);

	return organiser.showDatesFromNormalContent(tempContents[index]);
}

vector<Event> EventModifier::uncompleteFloat(int index) {
	//mark complete
	vector<Event> tempContents = organiser.allFloatingCompleted();
	tempContents[index].setIsCompleted(false);
	organiser.saveFloatingCompleted(tempContents);
	return organiser.allFloatingCurrent();
}

	//support methods
int EventModifier::findNormalCompletedIndex(int eventID) {
	vector<Event> tempContents = organiser.allNormalCompleted();
	int index = searcher.searchIndexWithID(eventID,tempContents);
	return index;
}

int EventModifier::findFloatingCompletedIndex(int eventID) {
	vector<Event> tempContents = organiser.allFloatingCompleted();
	int index = searcher.searchIndexWithID(eventID,tempContents);
	return index;
}