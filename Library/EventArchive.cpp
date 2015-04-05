#include "EventArchive.h"

//Constructors and Destructors
EventArchive::EventArchive()
{
}

EventArchive::~EventArchive(void)
{
}

//setters

void EventArchive::setCommandType(string commandTypeToSet){
	commandType = commandTypeToSet;
}

void EventArchive::setArchiveEvent(Event newEventToSet){
	archiveEvent = newEventToSet;
}
