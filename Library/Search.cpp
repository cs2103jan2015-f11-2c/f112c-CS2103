#include "Search.h"

Search::Search()
{
}


Search::~Search(void)
{
}

int Search::searchForIndexWithEventID(int eventID, vector<Event> eventVectorToSearch){
	
	for(int i=0;i<eventVectorToSearch.size();i++){
		if(eventVectorToSearch[i].getID() == eventID){
			return i;
		}
	}
	return -1; //notFound
}
vector<int> Search::searchForIdWithEventName(string eventName, vector<Event> eventVectorToSearch){

	vector<int> eventIdVector;

	for(int i=0;i<eventVectorToSearch.size();i++){
		if(eventVectorToSearch[i].getName() == eventName){
			eventIdVector.push_back(eventVectorToSearch[i].getID());
		}
	}
	return eventIdVector;
}

