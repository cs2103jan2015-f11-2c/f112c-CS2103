#include "EventFacade.h"


EventFacade::EventFacade(void)
{
	EventStorage::storage();
}

EventFacade::~EventFacade(void)
{
}

/*To EventModifer*/
vector<Event> EventFacade::addEvent(Event newEvent){
	logger.logStoragePosition("addEvent");
	return modifier.add(newEvent); 
}

vector<Event> EventFacade::deleteEvent(int eventID, Event eventToBeDeleted){
	logger.logStoragePosition("deleteEvent");
	return modifier.del(eventID, eventToBeDeleted); 
}

vector<Event> EventFacade::editEvent(int eventID, Event eventToBeEdited, Event editedEvent){
	logger.logStoragePosition("EditEvent");
	return modifier.edit(eventID, eventToBeEdited, editedEvent);
}

vector<Event> EventFacade::completeEvent(int eventID, Event completedEvent){
	logger.logStoragePosition("completeEvent");
	return modifier.complete(eventID, completedEvent);
}

/*To EventSearch*/
vector<Event> EventFacade::findNameOccurrence(string eventName){
	logger.logStoragePosition("findNameOccurrence");
	return searcher.searchNameOccurrence(eventName);
}

vector<Event> EventFacade::findNameExact(string eventName){
	logger.logStoragePosition("findNameExact");
	return searcher.searchNameExact(eventName);
}

vector<Event> EventFacade::findLevelImportance(int level){
	logger.logStoragePosition("findLevelImportance");
	return searcher.searchLevelImportance(level);
}

vector<Event> EventFacade::findAllImportance(){
	logger.logStoragePosition("findALLImportance");
	return searcher.searchAllImportance();
}

/*To EventOrganiser*/
vector<Event> EventFacade::showDates(Event eventWithStartEndTimes){
	logger.logStoragePosition("showDates");
	return organiser.showDatesFromNormalContent(eventWithStartEndTimes);
}

vector<Event> EventFacade::showAllNormalEvents(){
	logger.logStoragePosition("showAllNormalEvents");
	return organiser.showAllNormalCurrent();
}

vector<Event> EventFacade::showAllFloatingEvents(){
	logger.logStoragePosition("showAllFloatingEvents");
	return organiser.showAllFloatingCurrent();
}

vector<Event> EventFacade::showAllNormalCompleted(){
	logger.logStoragePosition("showAllNormalCompleted");
	return organiser.allNormalCompleted();
}

vector<Event> EventFacade::showAllFloatingCompleted(){
	logger.logStoragePosition("showAllFloatingCompleted");
	return organiser.allFloatingCompleted();
}