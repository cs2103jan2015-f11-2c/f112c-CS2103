//@author A0113860M

#include "EventSearch.h"

const int EventSearch::NOT_FOUND = -1;
const int EventSearch::MAX_LEVEL = 3;
const int EventSearch::MIN_LEVEL = 1;
const string EventSearch::ERROR_1 =  "Level greater than 3";

EventSearch::EventSearch()
{
}

EventSearch::~EventSearch()
{
}

//Main methods
//checking method 1 --- search event with matching string name and returns sorted with marker
vector<Event> EventSearch::searchCurrentNameOccurrence(string eventName){

	vector<Event> floatingCurrent = organiser.allFloatingCurrent();
	vector<Event> normalCurrent = organiser.allNormalCurrent();

	vector<Event> toLogic = searchNameOccurrence(eventName, normalCurrent, floatingCurrent);
	return toLogic;
}

vector<Event> EventSearch::searchCurrentNameExact(string eventName){
	
	vector<Event> floatingCurrent =  organiser.allFloatingCurrent();
	vector<Event> normalCurrent = organiser.allNormalCurrent();

	vector<Event> toLogic = searchNameExact(eventName, normalCurrent, floatingCurrent);
	return toLogic;
}

//========================================================================================
//checking method 2 --- search completed with matching string name and returns sorted with marker
vector<Event> EventSearch::searchCompletedNameOccurrence(string eventName){
	
	vector<Event> floatingCompleted = organiser.allFloatingCompleted();
	vector<Event> normalCompleted = organiser.allNormalCompleted();

	vector<Event> toLogic = searchNameOccurrence(eventName, normalCompleted, floatingCompleted);
	return toLogic;
}

vector<Event> EventSearch::searchCompletedNameExact(string eventName){

	vector<Event> floatingCompleted = organiser.allFloatingCompleted();
	vector<Event> normalCompleted = organiser.allNormalCompleted();

	vector<Event> toLogic = searchNameExact(eventName, normalCompleted, floatingCompleted);
	return toLogic;
}

//========================================================================================
//method 3 --- search level of importance
vector<Event> EventSearch::searchLevelImportance(int level){
	logger.log(EventLog::SEARCH + EventLog::SEARCH_LEVEL_IMPORTANCE, level);
	
	vector<Event> floatingEvents =  organiser.allFloatingCurrent();
	vector<Event> normalEvents = organiser.allNormalCurrent();
	
	floatingEvents = searchEventWithImportance(level, floatingEvents);
	normalEvents = searchEventWithImportance(level, normalEvents);

	return combineResults(floatingEvents, normalEvents);
}

//search method finds all important events
vector<Event> EventSearch::searchAllImportance(){
	logger.log(EventLog::SEARCH + EventLog::SEARCH_ALL_IMPORTANCE);
	vector<Event> returnVector;
	
	vector<Event> floatingEvents =  organiser.allFloatingCurrent();
	vector<Event> normalEvents = organiser.allNormalCurrent();

	floatingEvents = searchEventWithAllImportance(floatingEvents);
	normalEvents = searchEventWithAllImportance(normalEvents);	

	return combineResults(floatingEvents, normalEvents);
}

//========================================================================================
//method 4 --- search event with eventID
Event EventSearch::searchEventWithID(int eventID){
	logger.log(EventLog::SEARCH + EventLog::SEARCH_EVENT_WITH_ID, eventID);

	vector<Event> normalEvents = organiser.allNormalCurrent();
	Event noResults;
	noResults.setID(NOT_FOUND);

	for(auto i = 0; i < normalEvents.size(); i++){
		if(normalEvents[i].getID() == eventID){
			logger.log(EventLog::SEARCH_EVENT_WITH_ID + EventLog::EXIT, i);
			return normalEvents[i];
		}
	} 
	return noResults;
}

Event EventSearch::searchCompletedEventWithID(int eventID){
	logger.log(EventLog::SEARCH + EventLog::SEARCH_COMPLETED_EVENT_WITH_ID, eventID);

	vector<Event> normalCompleted = organiser.allNormalCompleted();
	Event noResults;
	noResults.setID(NOT_FOUND);

	for(auto i = 0; i < normalCompleted.size(); i++){
		if(normalCompleted[i].getID() == eventID){
			logger.log(EventLog::SEARCH_COMPLETED_EVENT_WITH_ID + EventLog::EXIT, i);
			return normalCompleted[i];
		}
	} 
	return noResults;
}

//========================================================================================
//find index in internal storages with ID (DEL / EDIT SUPPORT)
int EventSearch::searchIndexWithID(int eventID, vector<Event> eventVectorToSearch){
	logger.log(EventLog::SEARCH + EventLog::SEARCH_INDEX_WITH_ID, eventID);
	for(auto i = 0; i < eventVectorToSearch.size(); i++){
		if(eventVectorToSearch[i].getID() == eventID){
			logger.log(EventLog::SEARCH_INDEX_WITH_ID + EventLog::EXIT, i);
			return i;
		}
	} 
	return NOT_FOUND;
}

//========================================================================================
//support methods
//Support for method 1 --- finds string name match
vector<Event> EventSearch::searchNameOccurrence(string eventName, vector<Event> normal, vector<Event> floating){
	logger.log(EventLog::SEARCH + EventLog::SEARCH_NAME_OCCURRENCE + eventName);
	
	//search through names
	floating = searchEventWithName(eventName, floating);
	normal = searchEventWithName(eventName, normal);

	floating = combineResults(floating, normal);

	logger.log(EventLog::SEARCH + EventLog::SEARCH_NAME_OCCURRENCE + EventLog::EXIT, floating.size());
	return floating;
}

vector<Event> EventSearch::searchEventWithName(string eventName, vector<Event> eventVectorToSearch){

	vector<Event> returnVector;

	for(auto i = 0; i < eventVectorToSearch.size(); i++){
		int position = eventVectorToSearch[i].getName().find(eventName);
		if(position > NOT_FOUND){
			returnVector.push_back(eventVectorToSearch[i]);
		}
	}
	return returnVector;
}

//Support for method 2 --- find exact string name match
vector<Event> EventSearch::searchNameExact(string eventName, vector<Event> normal, vector<Event> floating){
	logger.log(EventLog::SEARCH + EventLog::SEARCH_NAME_EXACT + eventName);	

	floating = searchExactString(eventName, floating);
	normal = searchExactString(eventName, normal);

	floating = combineResults(floating, normal);

	logger.log(EventLog::SEARCH + EventLog::SEARCH_NAME_EXACT + EventLog::EXIT, floating.size());
	return floating;
}

vector<Event> EventSearch::searchExactString(string eventName, vector<Event> eventVectorToSearch){
	vector<Event> returnVector;

	for(auto i = 0; i < eventVectorToSearch.size(); i++){
		if(eventName == eventVectorToSearch[i].getName()){
			returnVector.push_back(eventVectorToSearch[i]);
		}
	}
	return returnVector;
}

//Support for method 3--- finds importance match
vector<Event> EventSearch::searchEventWithImportance(int level, vector<Event> vectorToSearch){

	vector<Event> returnVector;
	try{
		if(level > 3){
			if(level > MAX_LEVEL){
				level = MAX_LEVEL;
			} 
			if( level < MIN_LEVEL){
				level = MIN_LEVEL;
			}
			string exception = ERROR_1;
			throw exception;
		}
	} catch(string e){
		logger.log(EventLog::ERROR + e);
	}

	for(auto i = 0; i < vectorToSearch.size(); i++){
		if(level == vectorToSearch[i].getImportanceLevel()){
			returnVector.push_back(vectorToSearch[i]);
		}
	}
	return returnVector;
}

//finds all events with importance level > 0
vector<Event> EventSearch::searchEventWithAllImportance(vector<Event> vectorToSearch){

	vector<Event> returnVector;

	for(auto i = 0; i < vectorToSearch.size(); i++){
		if(vectorToSearch[i].getImportanceLevel() >= MIN_LEVEL){
			returnVector.push_back(vectorToSearch[i]);
		}
	}
	return returnVector;
}

//Support method
vector<Event> EventSearch::combineResults(vector<Event> floatingEvents, vector<Event> normalEvents){
	normalEvents = organiser.showEvents(normalEvents);
	floatingEvents.insert(floatingEvents.end(), normalEvents.begin(), normalEvents.end() );
	return floatingEvents;
}