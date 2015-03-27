#pragma once

#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;


class Event {
private:
	string name;
	tm startDateTime;
	tm endDateTime;
	bool isFloating;
	bool isDeadline;
	bool isCompleted;
	int importanceLevel;
	string feedback;
	int ID; //based on system time


	//unused
	vector<string> tags;
	string description;

public:
	//constructors
	Event();
	/*
	Event(string name);
	Event(string eventName, int day, int month, int year);
	Event(string eventName, int day, int month, int year, int startTime);
	Event(string eventName, int day, int month, int year, int startTime, int endTime);
	*/


	//getters
	string getName();
	struct tm getStartDate();
	struct tm getEndDate();
	bool getIsFloating();
	bool getIsDeadline();
	bool getIsCompleted();
	int getImportanceLevel();
	vector<string> getTags();
	string getDescription();
	string getFeedback();
	int getID();
	

	//setters
	void setName(string nameToSet);
	void setStartDate(int day, int month, int year);
	void setEndDate(int day, int month, int year);
	void setStartTime(int hour, int minute);
	void setEndTime(int hour, int minute);
	void setStartWeekday(int weekday);
	void setIsFloating(bool floating);
	void setIsDeadline(bool deadline);
	void setIsCompleted(bool completed);
	void setImportanceLevel(int importance);
	void setFeedback(string feedbackToUser);
	void setID(int number);


	//unused
	void setTags(vector<string> userTags);
	void setDescription(string desc);
	

};

#endif