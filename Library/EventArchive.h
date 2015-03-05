#pragma once

#ifndef EVENTARCHIVE_H_
#define EVENTSTORAGE_H_

#include <iostream>
#include "Event.h"

class EventArchive
{
private:
	std::string commandType;
	Event archiveEvent;
public:
	//Constructors and Destructors
	EventArchive(void);
	~EventArchive(void);

	//setters
	void setCommandType(string commandTypeToSet);
	void setArchiveEvent(Event archiveEvent);

};

#endif