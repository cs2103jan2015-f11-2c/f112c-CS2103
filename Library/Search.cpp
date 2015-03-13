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