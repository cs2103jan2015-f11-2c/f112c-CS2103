#include "EventSearch.h"

const int EventSearch::NOT_FOUND = -1 ;

EventSearch::EventSearch()
{
}

EventSearch::~EventSearch()
{
}

//checking methods
//checking method 1 --- search event with matching string name and returns sorted with marker
vector<Event> EventSearch::searchNameOccurrence(string eventName){
	logger.logStoragePosition("searchNameOccurrence");
	
	//get events from internal storages
	vector<Event> floatingEvents = EventStorage::storage().getFloatingContent();
	vector<Event> normalEvents = EventStorage::storage().getNormalContent();

	//search through names
	floatingEvents = searchEventWithName(eventName, floatingEvents);
	normalEvents = searchEventWithName(eventName, normalEvents);

	normalEvents = organiser.showEvents(normalEvents);
	floatingEvents.insert( floatingEvents.end(), normalEvents.begin(), normalEvents.end() );

	logger.logStoragePosition("leaving searchNameOccurrence");
	return floatingEvents;
}

//Support method --- finds string name match
vector<Event> EventSearch::searchEventWithName(string eventName, vector<Event> eventVectorToSearch){
	logger.logStorageStringData("searching for name occurrence", eventName);
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

//checking method 2 --- search event with exact string name and returns sorted with marker
vector<Event> EventSearch::searchNameExact(string eventName){
	logger.logStoragePosition("searchNameExact");
	
	vector<Event> floatingEvents =  EventStorage::storage().getFloatingContent();
	vector<Event> normalEvents = EventStorage::storage().getNormalContent();

	floatingEvents = searchExactString(eventName, floatingEvents);
	normalEvents = searchExactString(eventName, normalEvents);

	normalEvents = organiser.showEvents(normalEvents);
	floatingEvents.insert( floatingEvents.end(), normalEvents.begin(), normalEvents.end() );
	
	logger.logStoragePosition("leaving checkExactString");
	return floatingEvents;
}

//Support method --- find exact string name match
vector<Event> EventSearch::searchExactString(string eventName, vector<Event> eventVectorToSearch){
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


//find index in internal storages with ID (DEL / EDIT SUPPORT)
int EventSearch::searchIndexWithID(int eventID, vector<Event> eventVectorToSearch){
	logger.logStorageIntData("searching For this EventID",eventID);
	for(auto i=0;i<eventVectorToSearch.size();i++){
		if(eventVectorToSearch[i].getID() == eventID){
			logger.logStorageIntData("searching current content... index:",i);
			return i;
		}
	} 
	return NOT_FOUND;
}

//search all vector and all component of events save into events of vector results
vector<Event> EventSearch::searchAllComponentsOfEvent(string informationToSearch, vector<Event> contentToSearch){
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

