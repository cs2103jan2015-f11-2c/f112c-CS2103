/*EventStorage {
vector allEvents

void retrieve() {open file stream to collect data from storage txt file}
void addEvent(Event)
..... and all other forms of add
void deleteEvent(int ID) {search(ID) and erase}
void showEvents() {create a vector and push in events that are found starting from floating}
.... and all other forms of show
void editEvent(int ID, Event) {search(ID) and use this event to call editEvent(Event)} 
auto::iterator search(int ID)
}
*/
#pragma once

#ifndef EVENTSTORAGE_H
#define EVENTSTORAGE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Event.h"
#include "EventArchive.h"
#include "Parser.h"

class EventStorage{
private:
	std::vector<Event> currentContent;
	std::vector<EventArchive> archiveContent;
	std::vector<Event> searchResults;
	std::vector<Event> undoVector;
	std::vector<Event> redoVector;
	std::vector<Event> returnToLogicVector;
	EventArchive archiveObject; 
	static const std::string currentFile;	


public:
	//Constructor, Destructor
	EventStorage(void); //will read the currentFile into the currentContent vector 
	~EventStorage(void);

	//Methods
	void writeToCurrentFile(); //Write as One event One String One line of text.
	vector<Event> addEvent(Event newEvent);
	void deleteEvent(Event newEvent); 
	void showEvent();
	void EditEvent(int ID, Event newEvent);
	vector<Event> searchAllComponentsOfEvent(string informationToSearch); //search currentcontent
	vector<Event> searchEventID(int eventID);
	void searchEventname();
	string tmToString(Event current);

};


#endif