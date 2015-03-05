
#include "Event.h"


//constructors
Event::Event() {
	ID = time(0);
	startDateTime.tm_sec = 0;
	endDateTime.tm_sec = 0;
}


//useless constructors
/*Event::Event(string eventName) : name(eventName) {
}

Event::Event(string eventName, int day, int month, int year) : name(eventName) {
	startDateTime.tm_sec = 0;
	startDateTime.tm_min = 0;
	startDateTime.tm_hour = 0;
	startDateTime.tm_mday = day;
	startDateTime.tm_mon = month;
	startDateTime.tm_year = year;
	mktime(&startDateTime);
	
	endDateTime = startDateTime;
	endDateTime.tm_mday++;
	mktime(&endDateTime);
}

Event::Event(string eventName, int day, int month, int year, int startTime) : name(eventName) {
	startDateTime.tm_sec = 0;
	startDateTime.tm_min = 0;
	startDateTime.tm_hour = startTime;
	startDateTime.tm_mday = day;
	startDateTime.tm_mon = month;
	startDateTime.tm_year = year;
	mktime(&startDateTime);
	
	endDateTime = startDateTime;
	endDateTime.tm_hour++;
	mktime(&endDateTime);
}

Event::Event(string eventName, int day, int month, int year, int startTime, int endTime) : name(eventName) {
	startDateTime.tm_sec = 0;
	startDateTime.tm_min = 0;
	startDateTime.tm_hour = startTime;
	startDateTime.tm_mday = day;
	startDateTime.tm_mon = month;
	startDateTime.tm_year = year;
	mktime(&startDateTime);
	
	endDateTime = startDateTime;
	endDateTime.tm_hour = endTime;
	mktime(&endDateTime);
}*/


//getters
string Event::getName() {
	return name;
}

struct tm Event::getStartDate() {
	return startDateTime;
}

struct tm Event::getEndDate() {
	return endDateTime;
}

bool Event::getIsFloating() {
	return isFloating;
}

vector<string> Event::getTags() {
	return tags;
}

string Event::getDescription() {
	return description;
}

string Event::getFeedback() {
	return feedback;
}

int Event::getID() {
	return ID;
}


//setters
void Event::setName(string nameToSet) {
	name = nameToSet;
}

void Event::setStartDate(int day, int month, int year) {
	startDateTime.tm_mday = day;
	startDateTime.tm_mon = month;
	startDateTime.tm_year = year;
}

void Event::setEndDate(int day, int month, int year) {
	endDateTime.tm_mday = day;
	endDateTime.tm_mon = month;
	endDateTime.tm_year = year;
}

void Event::setStartTime(int hour, int minute) {
	startDateTime.tm_hour = hour;
	startDateTime.tm_min = minute;
}

void Event::setEndTime(int hour, int minute) {
	endDateTime.tm_hour = hour;
	endDateTime.tm_min = minute;
}

void Event::setIsFloating(bool floating) {
	isFloating = floating;
}

void Event::setTags(vector<string> userTags) {
	tags = userTags;
}

void Event::setDescription(string desc) {
	description = desc;
}

void Event::setFeedback(string feedbackToUser) {
	feedback = feedbackToUser;
}

void Event::setID(int number) {
	ID = number;
}

void Event::editEvent(int startTime, int endTime) {
	startDateTime.tm_hour = startTime;
	endDateTime.tm_hour = endTime;
}
