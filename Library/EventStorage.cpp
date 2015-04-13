//@author A0113860M

#include "EventStorage.h"
	
const string EventStorage::currentFile = "myCurrent.txt";
const string EventStorage::backupFile = "myBackup.txt";

//CONSTRUCTOR, DESTRUCTOR
EventStorage::EventStorage(void)
{
	isRead = true;
	lastID = 0;
	startUpFiles();
}

EventStorage::~EventStorage(void)
{
}

//Methods
//Reads from text file upon start up.
//If read successful, copy to backupFile (set: isRead = true)
//If read fails, load backupFile and copy backup to currentFile (set: isRead = false)
void EventStorage::startUpFiles(){
	logger.log(EventLog::STORAGE + EventLog::START_UP);
	checkFileExist();
	readToContent(currentFile);
	if(isRead){
		writeToFile(backupFile); 
	} else{
		normalContent.clear();	
		floatingContent.clear();
		readToContent(backupFile);
		writeToFile(currentFile);
	}
}

void EventStorage::checkFileExist(){
	std::ofstream outCurrent(currentFile, std::ios::app);
	outCurrent.close();
	std::ofstream outBackup(backupFile, std::ios::app);
	outBackup.close();
}

void EventStorage::writeToFile(string fileName){
	std::ofstream out(fileName);
	
	exportNormal(out);
	exportFloating(out);

	out.close();
}

void EventStorage::readToContent(string fileName){
	
	std::ifstream in(fileName);
	std::string textLine;

	getline(in, textLine);
	while(!in.eof()){
		Event* tempEvent = new Event;

		if(textLine == (LABEL_ISFLOATING + "0")){	//Normal case 
			try{
				tempEvent->setIsFloating(false); 
				importNormal(in, tempEvent);
			} catch(const string &e){
				isRead = false;
				logger.log(EventLog::READING_ERROR + e);
			}
		} else if(textLine == (LABEL_ISFLOATING + "1")){  //floatingEvent
			try{
				tempEvent->setIsFloating(true); 
				importFloat(in, tempEvent);
			} catch(const string &e){
				isRead = false;
				logger.log(EventLog::READING_ERROR + e);
			}
		}
		delete tempEvent;
		getline(in, textLine);			//takes in 0/1 for isFloating check
	}
	in.close();
}

//==================================================================================================
//Support Methods
void EventStorage::importNormal(std::istream& in, Event* tempEvent){
	importName(in, tempEvent);
	importDate(in, tempEvent);
	importDeadLine(in, tempEvent);
	importCompleted(in, tempEvent);
	importImportance(in, tempEvent);
	importID(in, tempEvent);
	importSpace(in);
	normalContent.push_back(*tempEvent);
}

void EventStorage::importFloat(std::istream& in, Event* tempEvent){
	importName(in, tempEvent);
	importFloatDate(in);
	importDeadLine(in, tempEvent);
	importCompleted(in, tempEvent);
	importImportance(in, tempEvent);
	importID(in, tempEvent);
	importSpace(in);
	floatingContent.push_back(*tempEvent);
}

void EventStorage::importFloatDate(std::istream& in){
	std::string startYear, startMonth, startDay, startHour, startMin, endYear, endMonth, endDay, endHour, endMin;
	
	getline(in, startYear);
	getline(in, startMonth);
	getline(in, startDay);
	getline(in, startHour);
	getline(in, startMin);
	getline(in, endYear);
	getline(in, endMonth);
	getline(in, endDay);
	getline(in, endHour);
	getline(in, endMin);

	if(startYear.substr(0, LABEL_STARTYEAR.size()) != LABEL_STARTYEAR){
		throw LABEL_STARTYEAR;
	} else if(startMonth.substr(0, LABEL_STARTMONTH.size()) != LABEL_STARTMONTH){
		throw LABEL_STARTMONTH;
	} else if(startDay.substr(0, LABEL_STARTDAY.size()) != LABEL_STARTDAY){
		throw LABEL_STARTDAY;
	} 
	if(startHour.substr(0, LABEL_STARTHOUR.size()) != LABEL_STARTHOUR){
		throw LABEL_STARTHOUR;
	} else if(startMin.substr(0, LABEL_STARTMIN.size()) != LABEL_STARTMIN){
		throw LABEL_STARTMIN;
	}
	if(endYear.substr(0, LABEL_ENDYEAR.size()) != LABEL_ENDYEAR){
		throw LABEL_ENDYEAR;
	} else if(endMonth.substr(0, LABEL_ENDMONTH.size()) != LABEL_ENDMONTH){
		throw LABEL_ENDMONTH;
	} else if(endDay.substr(0, LABEL_ENDDAY.size()) != LABEL_ENDDAY){
		throw LABEL_ENDDAY;
	}	
	if(endHour.substr(0, LABEL_ENDHOUR.size()) != LABEL_ENDHOUR){
		throw LABEL_ENDHOUR;
	} else if(endMin.substr(0, LABEL_ENDMIN.size()) != LABEL_ENDMIN){
		throw LABEL_ENDMIN;
	}
}

void EventStorage::importName(std::istream& in, Event* tempEvent){
	string name;
	getline(in, name);
	if(name.substr(0, LABEL_EVENTNAME.size()) == LABEL_EVENTNAME){
		tempEvent->setName(name.substr(LABEL_EVENTNAME.size()));
	} else{
		throw LABEL_EVENTNAME;
	}
}

void EventStorage::importDate(std::istream& in, Event* tempEvent){
	std::string startYear, startMonth, startDay, startHour, startMin, endYear, endMonth, endDay, endHour, endMin;
	
	getline(in, startYear);
	getline(in, startMonth);
	getline(in, startDay);
	getline(in, startHour);
	getline(in, startMin);
	getline(in, endYear);
	getline(in, endMonth);
	getline(in, endDay);
	getline(in, endHour);
	getline(in, endMin);

	if(startYear.substr(0, LABEL_STARTYEAR.size()) != LABEL_STARTYEAR){
		throw LABEL_STARTYEAR;
	} else if(startMonth.substr(0, LABEL_STARTMONTH.size()) != LABEL_STARTMONTH){
		throw LABEL_STARTMONTH;
	} else if(startDay.substr(0, LABEL_STARTDAY.size()) != LABEL_STARTDAY){
		throw LABEL_STARTDAY;
	} else{
		tempEvent->setStartDate(atoi((startDay.substr(LABEL_STARTDAY.size())).c_str()),
			atoi((startMonth.substr(LABEL_STARTMONTH.size())).c_str()), atoi((startYear.substr(LABEL_STARTYEAR.size())).c_str()));
	}
	
	if(startHour.substr(0, LABEL_STARTHOUR.size()) != LABEL_STARTHOUR){
		throw LABEL_STARTHOUR;
	} else if(startMin.substr(0, LABEL_STARTMIN.size()) != LABEL_STARTMIN){
		throw LABEL_STARTMIN;
	} else{
		tempEvent->setStartTime(atoi((startHour.substr(LABEL_STARTHOUR.size())).c_str()), atoi((startMin.substr(LABEL_STARTMIN.size())).c_str()));
	} 

	if(endYear.substr(0, LABEL_ENDYEAR.size()) != LABEL_ENDYEAR){
		throw LABEL_ENDYEAR;
	} else if(endMonth.substr(0, LABEL_ENDMONTH.size()) != LABEL_ENDMONTH){
		throw LABEL_ENDMONTH;
	} else if(endDay.substr(0, LABEL_ENDDAY.size()) != LABEL_ENDDAY){
		throw LABEL_ENDDAY;
	} else{
		tempEvent->setEndDate(atoi((endDay.substr(LABEL_ENDDAY.size())).c_str()),
			atoi((endMonth.substr(LABEL_ENDMONTH.size())).c_str()), atoi((endYear.substr(LABEL_ENDYEAR.size())).c_str()));
	}
	if(endHour.substr(0, LABEL_ENDHOUR.size()) != LABEL_ENDHOUR){
		throw LABEL_ENDHOUR;
	} else if(endMin.substr(0, LABEL_ENDMIN.size()) != LABEL_ENDMIN){
		throw LABEL_ENDMIN;
	} else{
		tempEvent->setEndTime(atoi((endHour.substr(LABEL_ENDHOUR.size())).c_str()), atoi((endMin.substr(LABEL_ENDMIN.size())).c_str()));
	}
}

void EventStorage::importDeadLine(std::istream& in, Event* tempEvent){
	string deadline;
	getline(in, deadline);
	if(deadline.substr(0, LABEL_ISDEADLINE.size()) == LABEL_ISDEADLINE){
		tempEvent->setIsDeadline(conversion.stringToBool(deadline.substr(LABEL_ISDEADLINE.size())));
	} else{
		throw LABEL_ISDEADLINE;
	}
}

void EventStorage::importCompleted(std::istream& in, Event* tempEvent){
	string completed;
	getline(in, completed);
	if(completed.substr(0, LABEL_ISCOMPLETED.size()) == LABEL_ISCOMPLETED){
		tempEvent->setIsCompleted(conversion.stringToBool(completed.substr(LABEL_ISCOMPLETED.size())));
	} else{
		throw LABEL_ISCOMPLETED;
	}
}
	
void EventStorage::importImportance(std::istream& in, Event* tempEvent){
	string importance;
	getline(in, importance);
	if(importance.substr(0, LABEL_IMPORTANCE.size()) == LABEL_IMPORTANCE){
		tempEvent->setImportanceLevel(atoi((importance.substr(LABEL_IMPORTANCE.size())).c_str()));
	} else{
		throw LABEL_IMPORTANCE;
	}
}

void EventStorage::importID(std::istream& in, Event* tempEvent){
	string id;
	getline(in, id);
	if(id.substr(0, LABEL_ID.size()) == LABEL_ID){
		int ID = (atoi((id.substr(LABEL_ID.size())).c_str()));
		setLastID(ID);
		tempEvent->setID(ID);
	} else{
		throw LABEL_ID;
	}
}

void EventStorage::importSpace(std::istream& in){
	string space;
	getline(in, space);
	if(space != ""){
		throw BLANK;
	}
}

void EventStorage::setLastID(int ID){
	if(ID > lastID){
		lastID = ID;
	}
}

int EventStorage::getLastID(){
	return lastID;
}

void EventStorage::exportNormal(std::ostream& out){
	for(auto i = 0; i < normalContent.size(); i++){
		out 
			<< LABEL_ISFLOATING << conversion.boolToString(normalContent[i].getIsFloating()) << std::endl 
			<< LABEL_EVENTNAME << normalContent[i].getName() << std::endl 
			<< conversion.tmToString(normalContent[i]) << std::endl
			<< LABEL_ISDEADLINE << conversion.boolToString(normalContent[i].getIsDeadline()) << std::endl
			<< LABEL_ISCOMPLETED << conversion.boolToString(normalContent[i].getIsCompleted()) << std::endl
			<< LABEL_IMPORTANCE << normalContent[i].getImportanceLevel() << std::endl
			<< LABEL_ID << normalContent[i].getID() << std::endl << std::endl;
	}
}

void EventStorage::exportFloating(std::ostream& out){
	for(auto i = 0; i < floatingContent.size(); i++){
		out 
			<< LABEL_ISFLOATING << conversion.boolToString(floatingContent[i].getIsFloating()) << std::endl 
			<< LABEL_EVENTNAME << floatingContent[i].getName() << std::endl 
			<< conversion.tmToString(floatingContent[i]) << std::endl
			<< LABEL_ISDEADLINE << conversion.boolToString(floatingContent[i].getIsDeadline()) << std::endl
			<< LABEL_ISCOMPLETED << conversion.boolToString(floatingContent[i].getIsCompleted()) << std::endl
			<< LABEL_IMPORTANCE << floatingContent[i].getImportanceLevel() << std::endl
			<< LABEL_ID << floatingContent[i].getID() << std::endl << std::endl;	
	}
}

//getters
vector<Event> EventStorage::getNormalContent(){
	logger.log(EventLog::STORAGE + EventLog::GET_NORMAL_CONTENT, normalContent.size());
	return normalContent;
}

vector<Event> EventStorage::getFloatingContent(){
	logger.log(EventLog::STORAGE + EventLog::GET_NORMAL_CONTENT, floatingContent.size());
	return floatingContent;
}

//setters
void EventStorage::setNormalContent(vector<Event> newNormalContent){
	normalContent = newNormalContent;
	writeToFile(currentFile);
}
void EventStorage::setFloatingContent(vector<Event> newFloatingContent){
	floatingContent = newFloatingContent;
	writeToFile(currentFile);
}

bool EventStorage::getIsRead(){
	return isRead;
}