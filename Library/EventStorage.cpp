#include "EventStorage.h"
	
const string EventStorage::currentFile = "mytext.txt";

//CONSTRUCTOR, DESTRUCTOR
//read all from text file first to have past memory
EventStorage::EventStorage(void)
{
	logger.logStoragePosition("creating storage object");
	readToContent();
}

EventStorage::~EventStorage(void)
{
}

//read to temp string
//check temp string with vector of label string. find first of " "
//try if no match vector label string and temp string fill in default
//set error in feedback.


//METHODS
void EventStorage::readToContent(){
	
	std::ifstream readFile(currentFile);
	std::string textLine, name, deadline, importance, tags, startYear, startMonth, startDay, startHour, startMin, 
		endYear, endMonth, endDay, endHour, endMin, id, completed, space;
	
	getline(readFile, textLine);
	while(!readFile.eof()){

		Event* tempEvent = new Event;

		if(textLine == (LABEL_ISFLOATING + "0")){					//Normal case 
			//getinfo from textfile;
			getline(readFile, name);
			//cin event times
			getline(readFile, startYear);


			getline(readFile, startMonth);
			getline(readFile, startDay);
			getline(readFile, startHour);
			getline(readFile, startMin);
			getline(readFile, endYear);
			getline(readFile, endMonth);
			getline(readFile, endDay);
			getline(readFile, endHour);
			getline(readFile, endMin);
			getline(readFile, deadline);
			getline(readFile, completed);
			getline(readFile, importance);
			getline(readFile, id);
			getline(readFile, space);

			createNormalEvent(tempEvent, name, id, deadline, importance, startHour, startMin, startDay, startMonth, startYear, endHour, endMin, endDay, endMonth, endYear, completed);

		} else if(textLine == (LABEL_ISFLOATING + "1")){				//floatingEvent
			//getinfo from textfile
			getline(readFile, name);
			getline(readFile, startYear);
			getline(readFile, startMonth);
			getline(readFile, startDay);
			getline(readFile, startHour);
			getline(readFile, startMin);
			getline(readFile, endYear);
			getline(readFile, endMonth);
			getline(readFile, endDay);
			getline(readFile, endHour);
			getline(readFile, endMin);
			getline(readFile, deadline);
			getline(readFile, completed);
			getline(readFile, importance);
			getline(readFile, id);
			getline(readFile, space);

			createFloatingEvent(tempEvent, name, id, deadline, importance, completed);
		}
		delete tempEvent;
		getline(readFile, textLine);			//takes in 0/1 for isFloating check
	}
	readFile.close();
}

void EventStorage::createNormalEvent(Event* tempEvent, string name, string id, string deadline, string importance, string startHour, string startMin, string startDay, 
								string startMonth, string startYear, string endHour, string endMin, string endDay, string endMonth, string endYear, string completed){

	tempEvent->setIsFloating(false); //stringToBool
	tempEvent->setName(name.substr(LABEL_EVENTNAME.size()));
	
	tempEvent->setIsDeadline(conversion.stringToBool(deadline.substr(LABEL_ISDEADLINE.size())));
	tempEvent->setIsCompleted(conversion.stringToBool(completed.substr(LABEL_ISCOMPLETED.size())));
	tempEvent->setImportanceLevel(atoi((importance.substr(LABEL_ID.size())).c_str()));
	tempEvent->setID(atoi((id.substr(LABEL_ID.size())).c_str()));

	tempEvent->setStartTime(atoi((startHour.substr(LABEL_STARTHOUR.size())).c_str()),atoi((startMin.substr(LABEL_STARTMIN.size())).c_str()));
	
	tempEvent->setStartDate(atoi((startDay.substr(LABEL_STARTDAY.size())).c_str()),atoi((startMonth.substr(LABEL_STARTMONTH.size())).c_str()),
		atoi((startYear.substr(LABEL_STARTYEAR.size())).c_str()));
	
	tempEvent->setEndTime(atoi((endHour.substr(LABEL_ENDHOUR.size())).c_str()),atoi((endMin.substr(LABEL_ENDMIN.size())).c_str()));
	
	tempEvent->setEndDate(atoi((endDay.substr(LABEL_ENDDAY.size())).c_str()),atoi((endMonth.substr(LABEL_ENDMONTH.size())).c_str()),
		atoi((endYear.substr(LABEL_ENDYEAR.size())).c_str()));
	
	normalContent.push_back(*tempEvent);
}

void EventStorage::createFloatingEvent(Event* tempEvent, string name, string id, string deadline, string importance, string completed){
	
	
	tempEvent->setIsFloating(true);
	tempEvent->setName(name.substr(LABEL_EVENTNAME.size()));			
	tempEvent->setIsDeadline(conversion.stringToBool(deadline.substr(LABEL_ISDEADLINE.size())));
	tempEvent->setIsCompleted(conversion.stringToBool((completed.substr(LABEL_ISCOMPLETED.size()))));
	tempEvent->setImportanceLevel(atoi((importance.substr(LABEL_ID.size())).c_str()));
	tempEvent->setID(atoi((id.substr(LABEL_ID.size())).c_str()));

	floatingContent.push_back(*tempEvent);
}

void EventStorage::writeToCurrentFile(){
	std::ofstream writeFile(currentFile);
	
	for(auto i=0;i<normalContent.size();i++){
		writeFile 
			<< LABEL_ISFLOATING << conversion.boolToString(normalContent[i].getIsFloating()) << std::endl 
			<< LABEL_EVENTNAME << normalContent[i].getName() << std::endl 
			<< conversion.tmToString(normalContent[i]) << std::endl
			<< LABEL_ISDEADLINE << conversion.boolToString(normalContent[i].getIsDeadline()) << std::endl
			<< LABEL_ISCOMPLETED << conversion.boolToString(normalContent[i].getIsCompleted()) << std::endl
			<< LABEL_IMPORTANCE << normalContent[i].getImportanceLevel() << std::endl
			<< LABEL_ID << normalContent[i].getID() << std::endl << std::endl;
	}	
	for(auto i=0;i<floatingContent.size();i++){
		writeFile 
			<< LABEL_ISFLOATING << conversion.boolToString(floatingContent[i].getIsFloating()) << std::endl 
			<< LABEL_EVENTNAME << floatingContent[i].getName() << std::endl 
			<< conversion.tmToString(floatingContent[i]) << std::endl
			<< LABEL_ISDEADLINE << conversion.boolToString(floatingContent[i].getIsDeadline()) << std::endl
			<< LABEL_ISCOMPLETED << conversion.boolToString(floatingContent[i].getIsCompleted()) << std::endl
			<< LABEL_IMPORTANCE << floatingContent[i].getImportanceLevel() << std::endl
			<< LABEL_ID << floatingContent[i].getID() << std::endl << std::endl;	
	}
	writeFile.close();
}
/*
void EventStorage::export(std::ofstream& writeFile){
	writeFile 
		<< LABEL_ISFLOATING << conversion.boolToString(normalContent[i].getIsFloating()) << std::endl 
		<< LABEL_EVENTNAME << normalContent[i].getName() << std::endl 
		<< conversion.tmToString(normalContent[i]) << std::endl
		<< LABEL_ISDEADLINE << conversion.boolToString(normalContent[i].getIsDeadline()) << std::endl
		<< LABEL_ISCOMPLETED << conversion.boolToString(normalContent[i].getIsCompleted()) << std::endl
		<< LABEL_IMPORTANCE << normalContent[i].getImportanceLevel() << std::endl
		<< LABEL_ID << normalContent[i].getID() << std::endl << std::endl;
}
*/
//getters
vector<Event> EventStorage::getNormalContent(){
	logger.logStorageIntData("getNormalContent",normalContent.size());
	return normalContent;
}

vector<Event> EventStorage::getFloatingContent(){
	logger.logStorageIntData("getfloatingContent",floatingContent.size());
	return floatingContent;
}

//setters
void EventStorage::setNormalContent(vector<Event> newNormalContent){
	normalContent = newNormalContent;
	writeToCurrentFile();
}
void EventStorage::setFloatingContent(vector<Event> newFloatingContent){
	floatingContent = newFloatingContent;
	writeToCurrentFile();
}

