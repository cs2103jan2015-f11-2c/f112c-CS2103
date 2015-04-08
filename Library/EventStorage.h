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
public:
	
	//Returns a new storage instance if one does not exist. 
	//else, it simply returns a reference to created storage. 
	static EventStorage& storage(){
        static EventStorage store;   // Guaranteed to be destroyed.		
        return store;				 // Instantiated on first use.
	}

	//getters
	vector<Event> getNormalContent();
	vector<Event> getFloatingContent();
	bool getIsRead();
	int getLastID();

	//setters
	void setNormalContent(vector<Event> newNormalContent);
	void setFloatingContent(vector<Event> newFloatingContent);
	void setLastID(int ID);

private:

	//These are external storages
	static const string currentFile;
	static const string backupFile;

	//These are internal storages
	vector<Event> normalContent;
	vector<Event> floatingContent;

	//These are indicator attributes
	bool isRead;
	int lastID;

	Conversion conversion;
	EventLog logger;

	//Constructor, Destructor
	EventStorage(void); 
	~EventStorage(void);
	EventStorage(EventStorage const&);              // copy constructor is private
    void operator=(EventStorage const&);			 // assignment operator is private

	//Import / Export Methods only called by itself. Singleton Pattern
	void startUpFiles();
	void checkFileExist(); 
	void writeToFile(string fileName);
	void readToContent(string fileName);
	
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

};
#endif
