/*EventStorage {
vector allEvents

void retrieve() {open file stream to collect data from storage txt file}
void addEvent(Event)
..... and all other forms of add
void deleteEvent(int ID) {search(ID) and erase}
void showEvents() {create a vector and push in events that are found starting from floating}
.... and all other forms of show
void editEvent(int ID, Event) {search(ID) and use this event to call editEvent(Event)} 
auto::iterator search(int ID)
}
*/

#include "EventStorage.h"

	//CONSTRUCTOR, DESTRUCTOR
//read all from text file first to have past memory
EventStorage::EventStorage(void)
{
	std::ifstream readFromCurrentFile(currentFile);
	std::string textLine;

	
	while(getline(readFromCurrentFile, textLine)){
	Parser* parserPtr = new Parser(textLine);	
	currentContent.push_back(parserPtr->getEvent());
	}
	readFromCurrentFile.close();
}

EventStorage::~EventStorage(void)
{
}

//=======
//>>>>>>> HEAD
	//METHODS
//>>>>>>> origin/master
/*
void EventStorage::writeToCurrentFile(){
	std::ofstream writeFile(currentFile);
	
	for(int i=0;i<currentContent.size();i++){
		writeFile << currentContent[i].getIsFloating() << std::endl 
			<< currentContent[i].getName() << std::endl 
			<< tmToString(currentContent[i]) << std::endl
			<< currentContent[i].getDescription() << std::endl
			<< currentContent[i].getFeedback() << std::endl
			<< currentContent[i].getID() << std::endl;
		
		for(auto iter = currentContent[i].getTags.begin(); iter != currentContent[i].getTags.end(); iter++)
			writeFile << " " << *iter << std::endl;
	}
	writeFile.close();

}
*/

string EventStorage::tmToString(Event convertEvent){
	std::ostringstream oss;

	oss << convertEvent.getStartDate().tm_year << " " << convertEvent.getStartDate().tm_mon << " " << convertEvent.getStartDate().tm_mday
		<< " " << convertEvent.getStartDate().tm_hour << " " << convertEvent.getStartDate().tm_min;
	
	oss << convertEvent.getEndDate().tm_year << " " << convertEvent.getEndDate().tm_mon << " " << convertEvent.getEndDate().tm_mday
		<< " " << convertEvent.getEndDate().tm_hour << " " << convertEvent.getEndDate().tm_min;

	return oss.str();
}

vector<Event> EventStorage::addEvent(Event eventName){
	currentContent.push_back(eventName);
	writeToCurrentFile();
	eventName.setFeedback("Your event has been added"); //Change to static msg wj adding
	returnToLogicVector.push_back(eventName);
	return returnToLogicVector; 
}
/*
void EventStorage::deleteEvent(Event newEvent){
	searchEventID(newEvent.getID);

	//saving in archive for Undo
	archiveObject.setCommandType("delete");
	archiveObject.setArchiveEvent(searchResults[0]);
	archiveContent.push_back(archiveObject);


	//delete in vector
	//copy to file
	//save in archiveVector

}

//search all vector and all component of events save into events of vector results
vector<Event> EventStorage::searchAllComponentsOfEvent(string informationToSearch){
	bool isFound=false;
	searchResults.clear();

	for(int i=0;i<currentContent.size();i++){
		isFound = currentContent[i].getDescription.find(informationToSearch);
		isFound = currentContent[i].getName.find(informationToSearch);
		isFound = currentContent[i].getStartDate.find(informationToSearch);
		isFound = currentContent[i].getEndDate.find(informationToSearch);
		isFound = currentContent[i].getID.find(informationToSearch);
		isFound = currentContent[i].getTags.find(informationToSearch);
	if(isFound){
		searchResults.push_back(currentContent[i]);
	}
	isFound=false;
	}
	return searchResults;
}

//search base on event ID
vector<Event> EventStorage::searchEventID(int eventID){
	bool isFound=false;
	
	searchResults.clear();
	for(int i=0;i<currentContent.size();i++){
		isFound = currentContent[i].getID.find(eventID);
	
		if(isFound){
			searchResults.push_back(currentContent[i]);
			return searchResults;
		}
	}
	return searchResults;
}*/