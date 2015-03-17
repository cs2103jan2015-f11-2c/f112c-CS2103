#include "Search.h"


Search::Search()
{
}


Search::~Search(void)
{
}

int Search::searchForIndexWithEventID(int eventID, vector<Event> eventVectorToSearch){
	
	for(auto i=0;i<eventVectorToSearch.size();i++){
		if(eventVectorToSearch[i].getID() == eventID){
			return i;
		}
	}
	return -1; //notFound
}
vector<Event> Search::searchForEventWithEventName(string eventName, vector<Event> eventVectorToSearch){

	vector<Event> eventVector;

	for(auto i=0;i<eventVectorToSearch.size();i++){
		if(eventVectorToSearch[i].getName() == eventName){
			eventVector.push_back(eventVectorToSearch[i]);
		}
	}
	return eventVector;
}

//search all vector and all component of events save into events of vector results
vector<Event> Search::searchAllComponentsOfEvent(string informationToSearch, vector<Event> contentToSearch){
	vector<Event> searchResults;
	bool isFound=false;

	for(int i=0;i<contentToSearch.size();i++){
		if(contentToSearch[i].getName().find(informationToSearch) != std::string::npos)
			isFound = true;
		if(contentToSearch[i].getStartDate().tm_year == atoi(informationToSearch.c_str()))
			isFound = true;
		if(contentToSearch[i].getStartDate().tm_mon == atoi(informationToSearch.c_str()))
			isFound = true;
		if(contentToSearch[i].getStartDate().tm_mday == atoi(informationToSearch.c_str()))
			isFound = true;
		if(contentToSearch[i].getStartDate().tm_hour == atoi(informationToSearch.c_str()))
			isFound = true;
		if(contentToSearch[i].getStartDate().tm_min == atoi(informationToSearch.c_str())) //necessary??
			isFound = true;
		if(contentToSearch[i].getEndDate().tm_year == atoi(informationToSearch.c_str()))
			isFound = true;
		if(contentToSearch[i].getEndDate().tm_mon == atoi(informationToSearch.c_str()))
			isFound = true;
		if(contentToSearch[i].getEndDate().tm_mday == atoi(informationToSearch.c_str()))
			isFound = true;
		if(contentToSearch[i].getEndDate().tm_hour == atoi(informationToSearch.c_str()))
			isFound = true;
		if(contentToSearch[i].getEndDate().tm_min == atoi(informationToSearch.c_str()))
			isFound = true;

			if(isFound){
			searchResults.push_back(contentToSearch[i]);
			}
		isFound=false;
	}
	return searchResults;
}

/*
vector<int> Search::searchForIdWithEventName(string eventName, vector<Event> eventVectorToSearch){

	vector<int> eventIdVector;

	for(auto i=0;i<eventVectorToSearch.size();i++){
		if(eventVectorToSearch[i].getName() == eventName){
			eventIdVector.push_back(eventVectorToSearch[i].getID());
		}
	}
	return eventIdVector;
}*/