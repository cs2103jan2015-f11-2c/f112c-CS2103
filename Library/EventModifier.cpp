//@author A0113860M

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
//returns a vector of Events of the added date
vector<Event> EventModifier::add(Event newEvent){  
	logger.log(EventLog::MODIFIER + EventLog::ADD);
	vector<Event> toLogic;
	if(newEvent.getIsFloating()){
		addFloat(newEvent);
		toLogic = organiser.showAllFloatingCurrent();	
	} else{
		addNormal(newEvent);
		toLogic = organiser.showDatesFromNormalContent(newEvent);
	}
	return toLogic; 
}

void EventModifier::addFloat(Event newEvent){
	logger.log(EventLog::MODIFIER + EventLog::ADD + EventLog::FLOATING);
	vector<Event> tempContents;
	tempContents = organiser.allFloatingCurrent();
	tempContents.push_back(newEvent);
	organiser.saveFloating(tempContents);
}
void EventModifier::addNormal(Event newEvent){
	logger.log(EventLog::MODIFIER + EventLog::ADD + EventLog::NORMAL);
	vector<Event> tempContents;
	tempContents = organiser.allNormalCurrent();
	tempContents.push_back(newEvent);
	organiser.saveNormal(tempContents);
}

//==================================================================================================
//Delete method
vector<Event> EventModifier::del(Event deletedEvent){
	logger.log(EventLog::MODIFIER + EventLog::DELETE);
	
	int index = NOT_FOUND; 
	vector<Event> toLogic;

	if(deletedEvent.getIsFloating()){
		index = findFloatingIndex(deletedEvent.getID());	//delete floating
		assert(index > NOT_FOUND);
		toLogic = deleteFloat(index);
	} else{
		index = findNormalIndex(deletedEvent.getID());	//delete normal
		assert(index > NOT_FOUND);
		toLogic = deleteNormal(index);
	}
	return toLogic;
}

vector<Event> EventModifier::deleteNormal(int index){
	
	vector<Event> tempContents = organiser.allNormalCurrent();
	Event deletedEvent = tempContents[index];
	tempContents.erase(tempContents.begin() + index);
	organiser.saveNormal(tempContents);

	logger.log(EventLog::MODIFIER + EventLog::DELETE + EventLog::NORMAL + deletedEvent.getName());
	vector<Event> toLogic = organiser.showDatesFromNormalContent(deletedEvent);	
	return toLogic;
}

vector<Event> EventModifier::deleteFloat(int index){
	
	vector<Event> tempContents = organiser.allFloatingCurrent();
	Event deletedEvent = tempContents[index];
	tempContents.erase(tempContents.begin() + index);
	organiser.saveFloating(tempContents);

	logger.log(EventLog::MODIFIER + EventLog::DELETE + EventLog::FLOATING + deletedEvent.getName());
	vector<Event> toLogic = organiser.showAllFloatingCurrent();	
	return toLogic;
}

//==================================================================================================
//Edit method
vector<Event> EventModifier::edit(Event beforeEdit, Event afterEdit){
	logger.log(EventLog::MODIFIER + EventLog::EDIT + beforeEdit.getName());
	
	int index = NOT_FOUND; 
	vector<Event> toLogic;

	if(beforeEdit.getIsFloating()){
		if((afterEdit.getStartDate().tm_mday != DEFAULT) || (afterEdit.getStartDate().tm_hour != DEFAULT)){
			index = findFloatingIndex(beforeEdit.getID()); //edit floatingToNormal
			assert(index > NOT_FOUND);
			toLogic = editFloatingToNormal(index, afterEdit);
		} else{																			
			index = findFloatingIndex(beforeEdit.getID()); //edit floating
			assert(index > NOT_FOUND);
			toLogic = editFloating(index, afterEdit);
			}
	} else{
		if(afterEdit.getIsFloating()){
			index = findNormalIndex(beforeEdit.getID());	//edit normalToFloat
			assert(index > NOT_FOUND);
			toLogic = editNormalToFloating(index, afterEdit);
		} else{
			index = findNormalIndex(beforeEdit.getID());	//edit normal
			assert(index > NOT_FOUND);
			toLogic = editNormal(index, afterEdit);
			}
	}
	return toLogic;
}

vector<Event> EventModifier::editFloatingToNormal(int index, Event afterEdit){
	logger.log(EventLog::MODIFIER + EventLog::EDIT + EventLog::FLOAT_TO_NORMAL);

	vector<Event> tempContents = organiser.allFloatingCurrent();
	Event beforeEdit = tempContents[index];
	time_t t = time(0);
	struct tm* now = localtime(&t);

	tempContents[index].setIsFloating(false);

	if(afterEdit.getName() != ""){
		(tempContents[index]).setName(afterEdit.getName());		
	}			
	if(afterEdit.getImportanceLevel() != NOT_FOUND){
		(tempContents[index]).setImportanceLevel(afterEdit.getImportanceLevel());
	}
	if((afterEdit.getStartDate().tm_mday != DEFAULT) && (afterEdit.getStartDate().tm_hour != DEFAULT)){  //Given both day & time
		(tempContents[index]).setStartDate(afterEdit.getStartDate().tm_mday,afterEdit.getStartDate().tm_mon,afterEdit.getStartDate().tm_year);
		(tempContents[index]).setStartTime(afterEdit.getStartDate().tm_hour,afterEdit.getStartDate().tm_min);
		(tempContents[index]).setEndDate(afterEdit.getEndDate().tm_mday,afterEdit.getEndDate().tm_mon,afterEdit.getStartDate().tm_year); 
		(tempContents[index]).setEndTime(afterEdit.getEndDate().tm_hour,afterEdit.getEndDate().tm_min);
	} else if((afterEdit.getStartDate().tm_mday != DEFAULT) && (afterEdit.getStartDate().tm_hour == DEFAULT)){ //Given only have day, time = ALLDAY
		(tempContents[index]).setStartDate(afterEdit.getStartDate().tm_mday,afterEdit.getStartDate().tm_mon,afterEdit.getStartDate().tm_year);
		(tempContents[index]).setStartTime(0,0);
		(tempContents[index]).setEndDate(afterEdit.getEndDate().tm_mday,afterEdit.getEndDate().tm_mon,afterEdit.getStartDate().tm_year);
		(tempContents[index]).setEndTime(23,59);
	} else if((afterEdit.getStartDate().tm_mday == DEFAULT) && (afterEdit.getStartDate().tm_hour != DEFAULT)){ //Given only have time, day = TODAY
		(tempContents[index]).setStartDate(now->tm_mday,now->tm_mon,now->tm_year);
		(tempContents[index]).setStartTime(afterEdit.getStartDate().tm_hour,afterEdit.getStartDate().tm_min);
		(tempContents[index]).setEndDate(now->tm_mday,now->tm_mon,now->tm_year);
		(tempContents[index]).setEndTime(afterEdit.getEndDate().tm_hour,afterEdit.getEndDate().tm_min);
	}

	correctDate(&tempContents[index]);

	del(beforeEdit);  
	tempContents = add(tempContents[index]);		
	
	return tempContents;
}

vector<Event> EventModifier::editFloating(int index, Event afterEdit){ 
	logger.log(EventLog::MODIFIER + EventLog::EDIT + EventLog::FLOATING);

	vector<Event> tempContents = organiser.allFloatingCurrent();
	
	if(afterEdit.getName() != ""){
		(tempContents[index]).setName(afterEdit.getName());		
	}			
	if(afterEdit.getImportanceLevel() != NOT_FOUND){
		(tempContents[index]).setImportanceLevel(afterEdit.getImportanceLevel());
	}
	organiser.saveFloating(tempContents);
	tempContents = organiser.showAllFloatingCurrent();
	
	return tempContents;
}

vector<Event> EventModifier::editNormal(int index, Event afterEdit){
	logger.log(EventLog::MODIFIER + EventLog::EDIT + EventLog::NORMAL);

	vector<Event> tempContents = organiser.allNormalCurrent();

	if(afterEdit.getName() != ""){
		(tempContents[index]).setName(afterEdit.getName());
	}
	if(afterEdit.getStartDate().tm_mday != DEFAULT){ 
		(tempContents[index]).setStartDate(afterEdit.getStartDate().tm_mday,afterEdit.getStartDate().tm_mon,afterEdit.getStartDate().tm_year);
	}
	if(afterEdit.getEndDate().tm_mday != DEFAULT){
		(tempContents[index]).setEndDate(afterEdit.getEndDate().tm_mday,afterEdit.getEndDate().tm_mon,afterEdit.getStartDate().tm_year);
	}
	if(afterEdit.getStartDate().tm_hour != DEFAULT){
		(tempContents[index]).setStartTime(afterEdit.getStartDate().tm_hour,afterEdit.getStartDate().tm_min);
	}
	if(afterEdit.getEndDate().tm_min != DEFAULT){
		(tempContents[index]).setEndTime(afterEdit.getEndDate().tm_hour,afterEdit.getEndDate().tm_min);
	}
	if(afterEdit.getImportanceLevel() != NOT_FOUND){ 
		(tempContents[index]).setImportanceLevel(afterEdit.getImportanceLevel());
	}

	correctDate(&tempContents[index]);

	organiser.saveNormal(tempContents);
	tempContents = organiser.showDatesFromNormalContent(tempContents[index]);
	return tempContents;
}

vector<Event> EventModifier::editNormalToFloating(int index, Event afterEdit){
	logger.log(EventLog::MODIFIER + EventLog::EDIT + EventLog::NORMAL_TO_FLOAT);

	vector<Event> tempContents = organiser.allNormalCurrent();
	Event beforeEdit = tempContents[index];

	tempContents[index].setIsFloating(true);
	tempContents[index].setStartDate(0,0,0);
	tempContents[index].setStartTime(0,0);
	tempContents[index].setEndDate(0,0,0); 
	tempContents[index].setEndTime(0,0);

	if(afterEdit.getName() != ""){
		(tempContents[index]).setName(afterEdit.getName());
	}
	if(afterEdit.getImportanceLevel() != NOT_FOUND){ 
		(tempContents[index]).setImportanceLevel(afterEdit.getImportanceLevel());
	}

	del(beforeEdit);  
	tempContents = add(tempContents[index]);  

	return tempContents;
}

void EventModifier::correctDate(Event *tempEvent) {
	logger.log(EventLog::MODIFIER + EventLog::CORRECT_DATE);

	struct tm* time;
	time = &tempEvent->getStartDate();
	mktime(time);
	tempEvent->setStartDate(time->tm_mday,time->tm_mon,time->tm_year);
	tempEvent->setStartTime(time->tm_hour,time->tm_min);
	tempEvent->setStartWeekday(time->tm_wday);

	time = &tempEvent->getEndDate();
	mktime(time);
	tempEvent->setEndDate(time->tm_mday,time->tm_mon,time->tm_year);
	tempEvent->setEndTime(time->tm_hour,time->tm_min);
	tempEvent->setEndWeekday(time->tm_wday);
}

//==================================================================================================
//Complete method
vector<Event> EventModifier::complete(Event completedEvent){
	logger.log(EventLog::MODIFIER + EventLog::COMPLETE);

	int index = NOT_FOUND; 
	vector<Event> toLogic;

	if(completedEvent.getIsFloating()){
		index = findFloatingIndex(completedEvent.getID()); //complete floating
		assert(index > NOT_FOUND);
		toLogic = completeFloat(index);
	} else{
		index = findNormalIndex(completedEvent.getID()); //complete normal
		assert(index > NOT_FOUND);
		toLogic = completeNormal(index, completedEvent);
	}
	return toLogic;
}

vector<Event> EventModifier::completeNormal(int index, Event completedEvent){  
	logger.log(EventLog::MODIFIER + EventLog::COMPLETE + EventLog::NORMAL);

	vector<Event> tempContents = organiser.allNormalCurrent();
	
	//mark complete in uncompleted vector of events
	vector<Event> completedEventDate = organiser.showDatesFromNormalContent(tempContents[index]);
	completedEventDate = markCompleted(completedEvent, completedEventDate);
	
	tempContents[index].setIsCompleted(true);
	organiser.saveNormal(tempContents);

	return completedEventDate;
}

vector<Event> EventModifier::markCompleted(Event completedEvent, vector<Event> completedEventDate){

	for(auto i=0;i<completedEventDate.size();i++){
		if(completedEventDate[i].getID() == completedEvent.getID()){
			completedEventDate[i].setIsCompleted(true);
		}
	}
	return completedEventDate;
}

vector<Event> EventModifier::completeFloat(int index){
	logger.log(EventLog::MODIFIER + EventLog::COMPLETE + EventLog::FLOATING);

	vector<Event> tempContents = organiser.allFloatingCurrent();
	tempContents[index].setIsCompleted(true);
	organiser.saveFloating(tempContents);
	return tempContents;
}

//==================================================================================================
//Uncomplete Method
vector<Event> EventModifier::uncomplete(Event uncompletedEvent){
	logger.log(EventLog::MODIFIER + EventLog::UNCOMPLETE);
	
	int index = NOT_FOUND; 
	vector<Event> toLogic;

	if(uncompletedEvent.getIsFloating()){
		index = findFloatingCompletedIndex(uncompletedEvent.getID()); //uncomplete floating
		assert(index > NOT_FOUND);
		toLogic = uncompleteFloat(index);
	} else{
		index = findNormalCompletedIndex(uncompletedEvent.getID()); //uncomplete normal
		assert(index > NOT_FOUND);
		toLogic = uncompleteNormal(index);
	}
	return toLogic;
}
vector<Event> EventModifier::uncompleteNormal(int index){  
	logger.log(EventLog::MODIFIER + EventLog::UNCOMPLETE + EventLog::NORMAL);

	vector<Event> tempContents = organiser.allNormalCompleted();

	//mark uncomplete
	tempContents[index].setIsCompleted(false);
	organiser.saveNormalCompleted(tempContents);

	return organiser.showDatesFromNormalContent(tempContents[index]);
}

vector<Event> EventModifier::uncompleteFloat(int index){
	logger.log(EventLog::MODIFIER + EventLog::UNCOMPLETE + EventLog::FLOATING);

	vector<Event> tempContents = organiser.allFloatingCompleted();

	//mark uncomplete
	tempContents[index].setIsCompleted(false);
	organiser.saveFloatingCompleted(tempContents);

	return organiser.allFloatingCurrent();
}

//==================================================================================================
//support methods
int EventModifier::findNormalIndex(int eventID){
	vector<Event> tempContents = organiser.allNormalCurrent();
	int index = searcher.searchIndexWithID(eventID,tempContents);
	return index;
}

int EventModifier::findFloatingIndex(int eventID){
	vector<Event> tempContents = organiser.allFloatingCurrent();
	int index = searcher.searchIndexWithID(eventID,tempContents);
	return index;
}

int EventModifier::findNormalCompletedIndex(int eventID){
	vector<Event> tempContents = organiser.allNormalCompleted();
	int index = searcher.searchIndexWithID(eventID,tempContents);
	return index;
}

int EventModifier::findFloatingCompletedIndex(int eventID){
	vector<Event> tempContents = organiser.allFloatingCompleted();
	int index = searcher.searchIndexWithID(eventID,tempContents);
	return index;
}