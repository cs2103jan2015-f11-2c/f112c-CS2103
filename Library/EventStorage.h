#pragma once

#ifndef EVENTSTORAGE_H
#define EVENTSTORAGE_H

#include <fstream>
#include <string>
#include <sstream>
#include "Event.h"
#include "Conversion.h"
#include "EventLog.h"

//for documentation and readability
const string LABEL_EVENTNAME = "Name: " ;
const string LABEL_ISFLOATING = "Is Floating: ";
const string LABEL_ID = "ID: ";
const string LABEL_FEEDBACK = "Feedback: ";
const string LABEL_IMPORTANCE = "Importance: ";
const string LABEL_ISCOMPLETED = "Is Completed: ";
const string LABEL_ISDEADLINE = "Is Deadline: ";
const string BLANK = "Blank Space";

class EventStorage{
private:

	//These are external storages
	static const string currentFile;
	static const string backupFile;

	//These are internal storages
	vector<Event> normalContent;
	vector<Event> floatingContent;
	bool isRead;
	int lastID;

	Conversion conversion;
	EventLog logger;

	//Constructor, Destructor
	EventStorage(void); //will read the currentFile into the normalContent vector 
	~EventStorage(void);
	EventStorage(EventStorage const&);              // copy constructor is private
    void operator=(EventStorage const&);			 // assignment operator is private

public:
	static EventStorage& storage(){
		//if(storage == NULL)
			//storage = new EventStorage();
		//static EventStorage storage;

        static EventStorage store; // Guaranteed to be destroyed.		
        return store;				 // Instantiated on first use.
	}

	//Methods
	void startUpFiles();
	void checkFileExist(); //creates file if does not exist
	void writeToFile(string fileName);	//called when setters are called
	void readToContent(string fileName);	//called once. upon opening of program ---------------to be refacted
	
	void importNormal(std::istream& in, Event* tempEvent);
	void importName(std::istream& in, Event* tempEvent);
	void importDate(std::istream& in, Event* tempEvent);
	void importDeadLine(std::istream& in, Event* tempEvent);
	void importCompleted(std::istream& in, Event* tempEvent);
	void importImportance(std::istream& in, Event* tempEvent);
	void importID(std::istream& in, Event* tempEvent);
	void importSpace(std::istream& in);
	void importFloat(std::istream& in, Event* tempEvent);
	void importFloatDate(std::istream& in);

	void exportNormal(std::ostream& out);
	void exportFloating(std::ostream& out);

	//void createFloatingEvent(Event* tempEvent, string name, string id, string deadline, string importance, string completed);
	//void createNormalEvent(Event* tempEvent, string name, string id, string deadline, string importance, string startHour, string startMin, string startDay, 
					//			string startMonth, string startYear, string endHour, string endMin, string endDay, string endMonth, string endYear, string completed);
	//getters
	vector<Event> getNormalContent();
	vector<Event> getFloatingContent();
	bool getIsRead();
	int getLastID();

	//setters
	void setNormalContent(vector<Event> newNormalContent);
	void setFloatingContent(vector<Event> newFloatingContent);
	void setLastID(int ID);

};
#endif
