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

class EventStorage{
private:

	//These are external storages
	static const string currentFile;
	static const string completedFile;

	//These are internal storages
	vector<Event> normalContent;
	vector<Event> floatingContent;

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
	void writeToCurrentFile();	//called when setters are called
	void readToContent();	//called once. upon opening of program ---------------to be refacted

	void exportNormal(std::ostream& out);
	void exportFloating(std::ostream& out);

	void createFloatingEvent(Event* tempEvent, string name, string id, string deadline, string importance, string completed);
	void createNormalEvent(Event* tempEvent, string name, string id, string deadline, string importance, string startHour, string startMin, string startDay, 
								string startMonth, string startYear, string endHour, string endMin, string endDay, string endMonth, string endYear, string completed);
	//getters
	vector<Event> getNormalContent();
	vector<Event> getFloatingContent();

	//setters
	void setNormalContent(vector<Event> newNormalContent);
	void setFloatingContent(vector<Event> newFloatingContent);

};
#endif


/*
class GlobalClass
{	
	int m_value;
    static EventStorage *s_instance;
    GlobalClass(int v = 0)
    {
        m_value = v;
    }

  public:
    int get_value()
    {
        return m_value;
    }
    void set_value(int v)
    {
        m_value = v;
    }
    static GlobalClass *instance()
    {
        if (!s_instance)
          s_instance = new GlobalClass;
        return s_instance;
    }
};

// Allocating and initializing GlobalClass's
// static data member.  The pointer is being
// allocated - not the object inself.
GlobalClass *GlobalClass::s_instance = 0;

void foo(void)
{
  GlobalClass::instance()->set_value(1);
  cout << "foo: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}

void bar(void)
{
  GlobalClass::instance()->set_value(2);
  cout << "bar: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}

int main()
{
  cout << "main: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
  foo();
  bar();
}


class S
{
    public:
        static S& getInstance()
        {
            static S    instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        }
    private:
        S() {};                   // Constructor? (the {} brackets) are needed here.

        // C++ 03
        // ========
        // Dont forget to declare these two. You want to make sure they
        // are unacceptable otherwise you may accidentally get copies of
        // your singleton appearing.
        S(S const&);              // Don't Implement
        void operator=(S const&); // Don't implement

        // C++ 11
        // =======
        // We can use the better technique of deleting the methods
        // we don't want.
        S(S const&)               = delete;
        void operator=(S const&)  = delete;

};

class S
{
    public:
        static S& getInstance()
        {
            static S    instance;
            return instance;
        }
    private:
        S() {}
        S(S const&);              // Don't Implement.
        void operator=(S const&); // Don't implement
 };*/