//@author A0111089L
#include "Event.h"


//constructors
Event::Event() {
	name = "";
	startDateTime.tm_mday = 0;
	startDateTime.tm_mon = 0;
	startDateTime.tm_year = 0;
	startDateTime.tm_hour = 0;
	startDateTime.tm_min = 0;
	startDateTime.tm_sec = 0;
	endDateTime.tm_mday = 0;
	endDateTime.tm_mon = 0;
	endDateTime.tm_year = 0;
	endDateTime.tm_hour = 0;
	endDateTime.tm_min = 0;
	endDateTime.tm_sec = 0;
	isFloating = false;
	isDeadline = false;
	isCompleted = false;
	importanceLevel = 0;
	feedback = "";
	ID = time(0);
}

Event::Event(string eventName) : name(eventName) {
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
}


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

vector<tm> Event::getAllTM() {
	vector<tm> tmVec;
	tmVec.push_back(startDateTime);
	tmVec.push_back(endDateTime);
	return tmVec;
}

bool Event::getIsFloating() {
	return isFloating;
}

bool Event::getIsDeadline() {
	return isDeadline;
}

bool Event::getIsCompleted() {
	return isCompleted;
}

int Event::getImportanceLevel() {
	return importanceLevel;
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

void Event::setStartEndDate(vector<tm> tmVec) {
	startDateTime = tmVec[0];
	endDateTime = tmVec[1];
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

void Event::setStartWeekday(int weekday){
	startDateTime.tm_wday = weekday;
}

void Event::setEndWeekday(int weekday){
	endDateTime.tm_wday = weekday;
}

void Event::setIsFloating(bool floating) {
	isFloating = floating;
}

void Event::setIsDeadline(bool deadline) {
	isDeadline = deadline;
}

void Event::setIsCompleted(bool completed) {
	isCompleted = completed;
}

void Event::setImportanceLevel(int importance) {
	if(importance > 3) {
		importance = 3;
	}
	if (importance < 0) {
		importance = 0;
	}
	importanceLevel = importance;
}

void Event::setTags(vector<string> userTags){
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
