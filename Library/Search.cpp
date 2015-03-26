#include "Search.h"
const int Search::NOT_FOUND = -1 ;


Search::Search()
{
}


Search::~Search(void)
{
}

int Search::searchIndexWithID(int eventID, vector<Event> eventVectorToSearch){
	logger.logStorageIntData("searching For this EventID",eventID);
	for(auto i=0;i<eventVectorToSearch.size();i++){
		if(eventVectorToSearch[i].getID() == eventID){
			logger.logStorageIntData("searching current content... index:",i);
			return i;
		}
	} 
	return NOT_FOUND;
}
vector<Event> Search::searchEventWithName(string eventName, vector<Event> eventVectorToSearch){
	logger.logStorageStringData("searching For similar EventName", eventName);
	vector<Event> returnVector;

	for(auto i=0;i<eventVectorToSearch.size();i++){
		int position = eventVectorToSearch[i].getName().find(eventName);
		logger.logStorageIntData("searching vector... found at: ",position);
		if(position > NOT_FOUND){
			logger.logStoragePosition("pushed");
			returnVector.push_back(eventVectorToSearch[i]);
		}
	}
	return returnVector;
}

vector<Event> Search::searchExactName(string eventName, vector<Event> eventVectorToSearch){
	logger.logStorageStringData("searching For Exact EventName", eventName);
	vector<Event> returnVector;

	for(auto i=0;i<eventVectorToSearch.size();i++){
		if(eventName == eventVectorToSearch[i].getName()){
			logger.logStorageIntData("searching.. exact::",i);
			returnVector.push_back(eventVectorToSearch[i]);
		}
	}
	return returnVector;
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