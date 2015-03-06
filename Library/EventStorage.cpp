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

const std::string EventStorage::currentFile = "mytext.txt";

EventStorage::EventStorage(void)
{
	readToCurrentContent();
}

EventStorage::~EventStorage(void)
{
}

//=======
//>>>>>>> HEAD
	//METHODS
//>>>>>>> origin/master
void EventStorage::readToCurrentContent(){
	
	std::ifstream readFile(currentFile);
	std::string textLine, name, description, feedback, tags, startDateYear, startDateMonth, startDateDay, startDateHour, startDateMin, endDateYear, endDateMonth, endDateDay, endDateHour, endDateMin, id;

	getline(readFile, textLine);
	while(readFile.eof()){

		Event* tempEvent = new Event;

		if(textLine == "0"){					//Normal case
			//getinfo from textfile;
			getline(readFile, name);
			//cin event times
			getline(readFile, startDateYear);
			getline(readFile, startDateMonth);
			getline(readFile, startDateDay);
			getline(readFile, startDateHour);
			getline(readFile, startDateMin);
			getline(readFile, endDateYear);
			getline(readFile, endDateMonth);
			getline(readFile, endDateDay);
			getline(readFile, endDateHour);
			getline(readFile, endDateMin);
		
			getline(readFile, description);
			getline(readFile, feedback);
			getline(readFile, id);
			getline(readFile, tags);
			//createFile
			tempEvent->setIsFloating("0");
			tempEvent->setName(name);
			tempEvent->setDescription(description);
			tempEvent->setFeedback(feedback);
			tempEvent->setID(atoi(id.c_str()));
			tempEvent->setStartTime(atoi(startDateHour.c_str()),atoi(startDateMin.c_str()));
			tempEvent->setStartDate(atoi(startDateDay.c_str()),atoi(startDateMonth.c_str()),atoi(startDateYear.c_str()));
			tempEvent->setEndTime(atoi(endDateHour.c_str()),atoi(endDateMin.c_str()));
			tempEvent->setEndDate(atoi(endDateDay.c_str()),atoi(endDateMonth.c_str()),atoi(endDateYear.c_str()));
			//split tags
			//tempEvent->setTags();
		}
		else if(textLine == "1"){				//floatingEvent
			//getinfo from textfile
			getline(readFile, name);
			getline(readFile, description);
			getline(readFile, feedback);
			getline(readFile, id);
			getline(readFile, tags);
			//createFile
			tempEvent->setIsFloating("0");
			tempEvent->setName(name);
			tempEvent->setDescription(description);
			tempEvent->setFeedback(feedback);
			tempEvent->setID(atoi(id.c_str()));
			//split tags
			//tempEvent->setTags();
		}
		currentContent.push_back(*tempEvent);
		delete tempEvent;
	}
	readFile.close();
}

void EventStorage::writeToCurrentFile(){
	std::ofstream writeFile(currentFile);
	
	for(int i=0;i<currentContent.size();i++){
		writeFile 
			<< boolToString(currentContent[i].getIsFloating()) << std::endl 
			<< currentContent[i].getName() << std::endl 
			<< tmToString(currentContent[i]) << std::endl
			<< currentContent[i].getDescription() << std::endl
			<< currentContent[i].getFeedback() << std::endl
			<< currentContent[i].getID() << std::endl;
		
		//for(auto iter = (currentContent[i].getTags()).begin(); iter != (currentContent[i].getTags()).end(); iter++)
		//	writeFile << " " << *iter << std::endl;
	}	
	writeFile.close();
}

string EventStorage::boolToString(bool isFloatingBool){
	if(isFloatingBool){
		return "1";
	}
	else{
		return "0";
	}
}

string EventStorage::tmToString(Event convertEvent){
	std::ostringstream oss;

	oss << convertEvent.getStartDate().tm_year << std::endl << convertEvent.getStartDate().tm_mon << std::endl << convertEvent.getStartDate().tm_mday
		<< std::endl << convertEvent.getStartDate().tm_hour << std::endl << convertEvent.getStartDate().tm_min << std::endl;
	
	oss << convertEvent.getEndDate().tm_year << std::endl << convertEvent.getEndDate().tm_mon << std::endl << convertEvent.getEndDate().tm_mday
		<< std::endl << convertEvent.getEndDate().tm_hour << std::endl << convertEvent.getEndDate().tm_min;

	return oss.str();
}

vector<Event> EventStorage::addEvent(Event eventName){
	currentContent.push_back(eventName);
	writeToCurrentFile();
	eventName.setFeedback("Your event has been added"); //Change to static msg wj adding
	returnToLogicVector.push_back(eventName);
	return returnToLogicVector; 
}
Event EventStorage::userInputIndexToEvent(int userIndex)
{
	return searchResults[userIndex-1];
}
void EventStorage::deleteEvent(int userIndex){
	
	Event eventToBeDeleted;
	int indexOfEventID;
	
	eventToBeDeleted = userInputIndexToEvent(userIndex);

	//saving in archive for Undo
	archiveObject.setCommandType("delete");
	archiveObject.setArchiveEvent(eventToBeDeleted);
	archiveContent.push_back(archiveObject);

	//find event in currentContent and delete
	indexOfEventID = searchCurrentContentWithEventID(eventToBeDeleted.getID());
	currentContent.erase(currentContent.begin() + indexOfEventID);

	writeToCurrentFile();
}

//search all vector and all component of events save into events of vector results
vector<Event> EventStorage::searchAllComponentsOfEvent(string informationToSearch){
	bool isFound=false;
	searchResults.clear();

	for(int i=0;i<currentContent.size();i++){
		isFound = currentContent[i].getDescription().find(informationToSearch);
		isFound = currentContent[i].getName().find(informationToSearch);
		//search for tags not yet included			
		if(currentContent[i].getID() == atoi(informationToSearch.c_str())){
			isFound = true;
		}

		if(currentContent[i].getStartDate().tm_year == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getStartDate().tm_mon == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getStartDate().tm_mday == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getStartDate().tm_hour == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getStartDate().tm_min == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getEndDate().tm_year == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getEndDate().tm_mon == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getEndDate().tm_mday == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getEndDate().tm_hour == atoi(informationToSearch.c_str()))
			isFound = true;
		if(currentContent[i].getEndDate().tm_min == atoi(informationToSearch.c_str()))
			isFound = true;

	if(isFound){
		searchResults.push_back(currentContent[i]);
	}
	isFound=false;
	}
	return searchResults;
}

//search base on event ID
int EventStorage::searchCurrentContentWithEventID(int eventID){
	bool isFound=false;
	
	searchResults.clear();
	for(int i=0;i<currentContent.size();i++){
		if(currentContent[i].getID() == eventID){
			isFound = true;
			return i;
		}
	}
	return -1;
}

vector<Event> EventStorage::showAllEvent(){
	sortEventVectorByDate();
	return currentContent;
}

void EventStorage::sortEventVectorByDate(){

	time_t timeSmaller, timeBigger;
	Event tempEvent;
	for(int i=0;i<currentContent.size()-1;i++){
		for(int j=i+1;j<currentContent.size();i++){
			timeSmaller = mktime(&currentContent[i].getStartDate());
			timeBigger = mktime(&currentContent[j].getStartDate());
			if(difftime(timeBigger,timeSmaller)>0){
				tempEvent = currentContent[j];
				currentContent[j] = currentContent[i];
				currentContent[i] = tempEvent;
			}
		}
	}
}