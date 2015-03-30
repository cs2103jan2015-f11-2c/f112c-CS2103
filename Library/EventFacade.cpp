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

/*To EventSearch*/
vector<Event> EventFacade::findNameOccurrence(string eventName){
	logger.logStoragePosition("findNameOccurrence");
	return searcher.searchNameOccurrence(eventName);
}

vector<Event> EventFacade::findNameExact(string eventName){
	logger.logStoragePosition("findNameExact");
	return searcher.searchNameExact(eventName);
}

/*To EventOrganiser*/
vector<Event> EventFacade::showDates(Event eventWithStartEndTimes){
	logger.logStoragePosition("showDates");
	return organiser.showDatesFromNormalContent(eventWithStartEndTimes);
}

vector<Event> EventFacade::showAllFloatingEvents(){
	logger.logStoragePosition("showAllFloatingEvents");
	return organiser.showAllFloatingEvent();
}

vector<Event> EventFacade::showAllNormalEvents(){
	logger.logStoragePosition("showAllNormalEvents");
	return organiser.showAllNormalEvent();
}
	
