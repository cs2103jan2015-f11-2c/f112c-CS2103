#include "EventSearch.h"

const int EventSearch::NOT_FOUND = -1;
const int EventSearch::MAX_LEVEL = 3;
const int EventSearch::MIN_LEVEL = 1;


EventSearch::EventSearch()
{
}

EventSearch::~EventSearch()
{
}

//checking methods
//checking method 1 --- search event with matching string name and returns sorted with marker
vector<Event> EventSearch::searchNormalNameOccurrence(string eventName) {
	//get events from internal storages
	vector<Event> floatingCurrent = organiser.allFloatingCurrent();
	vector<Event> normalCurrent = organiser.allNormalCurrent();

	vector<Event> toLogic = searchNameOccurrence(eventName, normalCurrent, floatingCurrent);
	return toLogic;
}

//checking method 1 --- search completed with matching string name and returns sorted with marker
vector<Event> EventSearch::searchCompletedNameOccurrence(string eventName) {
	
	//get events from internal storages
	vector<Event> floatingCompleted = organiser.allFloatingCompleted();
	vector<Event> normalCompleted = organiser.allNormalCompleted();

	vector<Event> toLogic = searchNameOccurrence(eventName, normalCompleted, floatingCompleted);
	return toLogic;
}

//Support method --- finds string name match
vector<Event> EventSearch::searchNameOccurrence(string eventName, vector<Event> normal, vector<Event> floating) {
	logger.logStoragePosition("searchNameOccurrence");
	
	//search through names
	floating = searchEventWithName(eventName, floating);
	normal = searchEventWithName(eventName, normal);

	floating = combineResults(floating, normal);

	logger.logStoragePosition("leaving searchNameOccurrence");
	return floating;
}

//Support method --- finds string name match
vector<Event> EventSearch::searchEventWithName(string eventName, vector<Event> eventVectorToSearch) {
	logger.logStorageStringData("searching for name occurrence", eventName);
	vector<Event> returnVector;

	for (auto i = 0; i < eventVectorToSearch.size(); i++) {
		int position = eventVectorToSearch[i].getName().find(eventName);
		logger.logStorageIntData("searching vector... found at: ",position);
		if (position > NOT_FOUND) {
			logger.logStoragePosition("pushed");
			returnVector.push_back(eventVectorToSearch[i]);
		}
	}
	return returnVector;
}

//checking method 2 --- search event with exact string name and returns sorted with marker
vector<Event> EventSearch::searchNormalNameExact(string eventName) {
	
	//get events from internal storages
	vector<Event> floatingCurrent =  organiser.allFloatingCurrent();
	vector<Event> normalCurrent = organiser.allNormalCurrent();

	vector<Event> toLogic = searchNameExact(eventName, normalCurrent, floatingCurrent);
	return toLogic;
}

//checking method 2 --- search normal with exact string name and returns sorted with marker
vector<Event> EventSearch::searchCompletedNameExact(string eventName) {

	//get events from internal storages
	vector<Event> floatingCompleted = organiser.allFloatingCompleted();
	vector<Event> normalCompleted = organiser.allNormalCompleted();

	vector<Event> toLogic = searchNameExact(eventName, normalCompleted, floatingCompleted);
	return toLogic;
}

//Support method --- find exact string name match
vector<Event> EventSearch::searchNameExact(string eventName, vector<Event> normal, vector<Event> floating) {
	logger.logStoragePosition("searchNameExact");
	

	floating = searchExactString(eventName, floating);
	normal = searchExactString(eventName, normal);

	floating = combineResults(floating, normal);

	logger.logStoragePosition("leaving checkExactString");
	return floating;
}

vector<Event> EventSearch::searchExactString(string eventName, vector<Event> eventVectorToSearch) {
	logger.logStorageStringData("searching For Exact EventName", eventName);
	vector<Event> returnVector;

	for (auto i = 0; i < eventVectorToSearch.size(); i++) {
		if (eventName == eventVectorToSearch[i].getName()) {
			logger.logStorageIntData("searching.. exact::",i);
			returnVector.push_back(eventVectorToSearch[i]);
		}
	}
	return returnVector;
}


//search level of importance
vector<Event> EventSearch::searchLevelImportance(int level) {
	logger.logStorageIntData("searching for this level of importance" ,level);
	
	vector<Event> floatingEvents =  organiser.allFloatingCurrent();
	vector<Event> normalEvents = organiser.allNormalCurrent();
	//try{
	floatingEvents = searchEventWithImportance(level, floatingEvents);
	normalEvents = searchEventWithImportance(level, normalEvents);
	//} catch(exception&) {
	// if level more than 3, = 3
	//}
	return combineResults(floatingEvents, normalEvents);
}

//Support method --- finds importance match
vector<Event> EventSearch::searchEventWithImportance(int level, vector<Event> vectorToSearch) {

	vector<Event> returnVector;
	/*if (level > 3) {
		string exception = "ERROR: Level greater than 3";
		throw exception;
	}*/
	if (level > MAX_LEVEL) {
		level = MAX_LEVEL;
	} 
	if ( level < MIN_LEVEL) {
		level = MIN_LEVEL;
	}

	for (auto i = 0; i < vectorToSearch.size(); i++) {
		if (level == vectorToSearch[i].getImportanceLevel()) {
			returnVector.push_back(vectorToSearch[i]);
		}
	}
	return returnVector;
}

//search method finds all important events
vector<Event> EventSearch::searchAllImportance() {
	logger.logStoragePosition("searchALLImportance");
	vector<Event> returnVector;
	
	vector<Event> floatingEvents =  organiser.allFloatingCurrent();
	vector<Event> normalEvents = organiser.allNormalCurrent();

	floatingEvents = searchEventWithAllImportance(floatingEvents);
	normalEvents = searchEventWithAllImportance(normalEvents);	

	return combineResults(floatingEvents, normalEvents);
}

//Support method --- finds all events with importance level > 0
vector<Event> EventSearch::searchEventWithAllImportance(vector<Event> vectorToSearch) {

	vector<Event> returnVector;

	for (auto i = 0; i < vectorToSearch.size(); i++) {
		if (vectorToSearch[i].getImportanceLevel() >= MIN_LEVEL) {
			returnVector.push_back(vectorToSearch[i]);
		}
	}
	return returnVector;
}

//support method
vector<Event> EventSearch::combineResults(vector<Event> floatingEvents, vector<Event> normalEvents) {
	normalEvents = organiser.showEvents(normalEvents);
	floatingEvents.insert( floatingEvents.end(), normalEvents.begin(), normalEvents.end() );
	return floatingEvents;
}

//find index in internal storages with ID (DEL / EDIT SUPPORT)
int EventSearch::searchIndexWithID(int eventID, vector<Event> eventVectorToSearch) {
	logger.logStorageIntData("searching For this EventID",eventID);
	for (auto i = 0; i < eventVectorToSearch.size(); i++) {
		if (eventVectorToSearch[i].getID() == eventID) {
			logger.logStorageIntData("searching current content... index:",i);
			return i;
		}
	} 
	return NOT_FOUND;
}




//search all vector and all component of events save into events of vector results
vector<Event> EventSearch::searchAllComponentsOfEvent(string informationToSearch, vector<Event> contentToSearch) {
	vector<Event> searchResults;
	bool isFound=false;

	for (int i = 0; i < contentToSearch.size(); i++) {
		if (contentToSearch[i].getName().find(informationToSearch) != std::string::npos)
			isFound = true;
		if (contentToSearch[i].getStartDate().tm_year == atoi(informationToSearch.c_str()))
			isFound = true;
		if (contentToSearch[i].getStartDate().tm_mon == atoi(informationToSearch.c_str()))
			isFound = true;
		if (contentToSearch[i].getStartDate().tm_mday == atoi(informationToSearch.c_str()))
			isFound = true;
		if (contentToSearch[i].getStartDate().tm_hour == atoi(informationToSearch.c_str()))
			isFound = true;
		if (contentToSearch[i].getStartDate().tm_min == atoi(informationToSearch.c_str())) //necessary??
			isFound = true;
		if (contentToSearch[i].getEndDate().tm_year == atoi(informationToSearch.c_str()))
			isFound = true;
		if (contentToSearch[i].getEndDate().tm_mon == atoi(informationToSearch.c_str()))
			isFound = true;
		if (contentToSearch[i].getEndDate().tm_mday == atoi(informationToSearch.c_str()))
			isFound = true;
		if (contentToSearch[i].getEndDate().tm_hour == atoi(informationToSearch.c_str()))
			isFound = true;
		if (contentToSearch[i].getEndDate().tm_min == atoi(informationToSearch.c_str()))
			isFound = true;

			if (isFound) {
			searchResults.push_back(contentToSearch[i]);
			}
		isFound=false;
	}
	return searchResults;
}

