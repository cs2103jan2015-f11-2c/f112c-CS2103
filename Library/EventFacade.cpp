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
	logger.log(EventLog::FACADE + EventLog::ADD);
	return modifier.add(newEvent); 
}

vector<Event> EventFacade::deleteEvent(Event deletedEvent){
	logger.log(EventLog::FACADE + EventLog::DELETE);
	return modifier.del(deletedEvent); 
}

vector<Event> EventFacade::editEvent(Event beforeEdit, Event afterEdit){
	logger.log(EventLog::FACADE + EventLog::EDIT);
	return modifier.edit(beforeEdit, afterEdit);
}

vector<Event> EventFacade::completeEvent(Event completedEvent){
	logger.log(EventLog::FACADE + EventLog::COMPLETE);
	return modifier.complete(completedEvent);
}

vector<Event> EventFacade::uncompleteEvent(Event uncompletedEvent){
	logger.log(EventLog::FACADE + EventLog::UNCOMPLETE);
	return modifier.uncomplete(uncompletedEvent);
}

/*To EventSearch*/
vector<Event> EventFacade::findNameOccurrence(string eventName){
	logger.log(EventLog::FACADE + EventLog::SEARCH_NAME_OCCURRENCE);
	return searcher.searchCurrentNameOccurrence(eventName);
}

vector<Event> EventFacade::findNameExact(string eventName){
	logger.log(EventLog::FACADE + EventLog::SEARCH_NAME_EXACT);
	return searcher.searchCurrentNameExact(eventName);
}

vector<Event> EventFacade::findCompletedNameOccurrence(string eventName){
	logger.log(EventLog::FACADE + EventLog::COMPLETE + EventLog::SEARCH_NAME_OCCURRENCE);
	return searcher.searchCompletedNameOccurrence(eventName);
}

vector<Event> EventFacade::findCompletedNameExact(string eventName){
	logger.log(EventLog::FACADE + EventLog::COMPLETE + EventLog::SEARCH_NAME_EXACT);
	return searcher.searchCompletedNameExact(eventName);
}

vector<Event> EventFacade::findLevelImportance(int level){
	logger.log(EventLog::FACADE + EventLog::SEARCH_LEVEL_IMPORTANCE);
	return searcher.searchLevelImportance(level);
}

vector<Event> EventFacade::findAllImportance(){
	logger.log(EventLog::FACADE + EventLog::SEARCH_ALL_IMPORTANCE);
	return searcher.searchAllImportance();
}

Event EventFacade::findEventWithID(int eventID){
	logger.log(EventLog::FACADE + EventLog::SEARCH_EVENT_WITH_ID);
	return searcher.searchEventWithID;
}

/*To EventOrganiser*/
vector<Event> EventFacade::showDates(Event eventWithStartEndTimes){
	logger.log(EventLog::FACADE + EventLog::SHOW_DATES);
	return organiser.showDatesFromNormalContent(eventWithStartEndTimes);
}

vector<Event> EventFacade::showAllNormalEvents(){
	logger.log(EventLog::FACADE + EventLog::SHOW_ALL_FLOATING_CURRENT);
	return organiser.showAllNormalCurrent();
}

vector<Event> EventFacade::showAllFloatingEvents(){
	logger.log(EventLog::FACADE + EventLog::SHOW_ALL_FLOATING_CURRENT);
	return organiser.showAllFloatingCurrent();
}

vector<Event> EventFacade::showAllNormalCompleted(){
	logger.log(EventLog::FACADE + EventLog::SHOW_ALL_NORMAL_COMPLETED);
	return organiser.showAllNormalCompleted();
}

vector<Event> EventFacade::showAllFloatingCompleted(){
	logger.log(EventLog::FACADE + EventLog::SHOW_ALL_FLOATING_COMPLETED);
	return organiser.showAllFloatingCompleted();
}

/*To EventStorage*/
bool EventFacade::dataRead(){
	logger.log(EventLog::FACADE + EventLog::DATA_READ);
	return EventStorage::storage().getIsRead();
}

int EventFacade::getDataID(){
	logger.log(EventLog::FACADE + EventLog::DATA_ID);
	return EventStorage::storage().getLastID();
}