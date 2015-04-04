#include "UIHelp.h"


UIHelp::UIHelp(void)
{
}


UIHelp::~UIHelp(void)
{
}


// static variables that cannot initialise in "UIHelp.h"
const std::string UIHelp::HELP_GUIDE_WELCOME_MESSAGE = "Welcome to MapleSyrup. Following are the commands: \n";

const std::string UIHelp::HELP_GUIDE_ADD[UIHelp::NUM_ADD] = { "There are a total of 9 ways to add an event:\n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n"
																	};

const std::string UIHelp::HELP_GUIDE_DELETE[UIHelp::NUM_DELETE] = { "Through index: Use either the 'show' or 'search' command to display the event you would like to delete.\n",
																 "Delete by entering the number beside it.\n",
																 "e.g. 'delete 2'  to delete 2.CS2103 \n",
																 "Through event name: \n",
																 "e.g. 'delete 2'  to delete 2.CS2103 \n",
																 "TBC \n"
															   };
																 
const std::string UIHelp::HELP_GUIDE_EDIT[UIHelp::NUM_EDIT] = {"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n"
																	};

const std::string UIHelp::HELP_GUIDE_DONE[UIHelp::NUM_DONE]= {"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																	};



const std::string UIHelp::HELP_GUIDE_SEARCH[UIHelp::NUM_SEARCH]= {"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n"
																	};

const std::string UIHelp::HELP_GUIDE_SHOW[UIHelp::NUM_SHOW] = {"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n"
																	};
const std::string UIHelp::HELP_GUIDE_UNDO = "TBC \n";

const std::string UIHelp::HELP_GUIDE_REDO = "TBC \n";

const std::string UIHelp::HELP_GUIDE_EXIT = "TBC \n";

const std::string UIHelp::HELP_GUIDE_COMMANDS[UIHelp::NUM_COMMANDS] = {"1.\tAdd",
																		"2.\tDelete",
																		"3.\tEdit",
																		"4.\tDone",
																		"5.\tSearch",
																		"6.\tShow",
																		"7.\tUndo",
																		"8.\tRedo",
																		"9.\tExit",
																		"10.\tHelp",
																		"11.\tCommands",
																		"12.\tShortcuts",
																		"13.\tCalendar",
																		"14.\tBack",
																		"15.\tNext",
																	};

const std::string UIHelp::HELP_GUIDE_SHORTCUTS [UIHelp::NUM_SHORTCUTS] = {"1.\tCtrl + D ------ display calendar",
																		  "2.\tCtrl + F ------ search mode/bar",
																		  "3.\tCtrl + Z ------ undo",
																	      "4.\tCtrl + X ------ redo",
																		  "5.\tCtrl + C ------ copy",
																		  "6.\tCtrl + V ------ paste",
																		  "7.\tEscape Key ---- Zoom to main display",
																		  "8.\tLeft arrow ---- display back (only after pressing Escape Key)",
																		  "9.\tRight arrow ----- display next (only after pressing Escape Key)",
																		  "10.\tCtrl + Shift ----- Focus to command Box",
																	};

//Functions	
std::string UIHelp::getHelpWelcomeMessage(){
	return HELP_GUIDE_WELCOME_MESSAGE;
}

std::string UIHelp::getHelpAdd(){
	std::string out = "";

	for (int i=0; i<NUM_ADD;i++){
		out += HELP_GUIDE_ADD[i];
	}

	return out;
}

std::string UIHelp::getHelpDelete(){
	std::string out = "";

	for (int i=0; i<NUM_DELETE;i++){
		out += HELP_GUIDE_DELETE[i];
	}

	return out;
}

std::string UIHelp::getHelpEdit(){
	std::string out = "";

	for (int i=0; i<NUM_EDIT;i++){
		out += HELP_GUIDE_EDIT[i];
	}

	return out;
}

std::string UIHelp::getHelpDone(){
	std::string out = "";

	for (int i=0; i<NUM_DONE;i++){
		out += HELP_GUIDE_DONE[i];
	}

	return out;
}

std::string UIHelp::getHelpSearch(){
	std::string out = "";

	for (int i=0; i<NUM_SEARCH;i++){
		out += HELP_GUIDE_SEARCH[i];
	}

	return out;
}

std::string UIHelp::getHelpShow(){
	std::string out = "";

	for (int i=0; i<NUM_SHOW;i++){
		out += HELP_GUIDE_SHOW[i];
	}

	return out;
}
	
std::string UIHelp::getHelpUndo(){
	return HELP_GUIDE_UNDO;
}
	
std::string UIHelp::getHelpRedo(){
	return HELP_GUIDE_REDO ;
}
	
std::string UIHelp::getHelpExit(){
	return HELP_GUIDE_EXIT;
}

LogicUpdater::EVENT_STRING UIHelp::convertToEventString(std::string stdString){
	LogicUpdater::EVENT_STRING temp;

	temp.dateString = "";
	temp.eventString = stdString;
	temp.importanceLevel = 0;
	temp.isCompleted = false;
	temp.isMarker = false;
	temp.isClash = false;
	temp.isNew = false;

	return temp;
}

std::vector<LogicUpdater::EVENT_STRING> UIHelp::getHelpIntroduction(){
	std::vector<LogicUpdater::EVENT_STRING> vectOfHelp;

	std::string tempHelpString; 
	LogicUpdater::EVENT_STRING helpString;

	//Welcome Message
	tempHelpString = getHelpWelcomeMessage();
	helpString = convertToEventString(tempHelpString);
	vectOfHelp.push_back(helpString);

	//Add
	tempHelpString = getHelpAdd();
	helpString = convertToEventString(tempHelpString);
	vectOfHelp.push_back(helpString);

	//Welcome Delete
	tempHelpString = getHelpDelete();
	helpString = convertToEventString(tempHelpString);
	vectOfHelp.push_back(helpString);

	//Edit
	tempHelpString = getHelpEdit();
	helpString = convertToEventString(tempHelpString);
	vectOfHelp.push_back(helpString);

	//Done
	tempHelpString = getHelpDone();
	helpString = convertToEventString(tempHelpString);
	vectOfHelp.push_back(helpString);

	//Search
	tempHelpString = getHelpSearch();
	helpString = convertToEventString(tempHelpString);
	vectOfHelp.push_back(helpString);

	//Show
	tempHelpString = getHelpShow();
	helpString = convertToEventString(tempHelpString);
	vectOfHelp.push_back(helpString);

	//Undo
	tempHelpString = getHelpUndo();
	helpString = convertToEventString(tempHelpString);
	vectOfHelp.push_back(helpString);

	//Redo
	tempHelpString = getHelpRedo();
	helpString = convertToEventString(tempHelpString);
	vectOfHelp.push_back(helpString);

	//Exit
	tempHelpString = getHelpExit();
	helpString = convertToEventString(tempHelpString);
	vectOfHelp.push_back(helpString);

	assert(vectOfHelp.size() == 10);

	return vectOfHelp;
}

std::vector<LogicUpdater::EVENT_STRING> UIHelp::getHelpCommands(){
	std::vector<LogicUpdater::EVENT_STRING> vectOfComds;

	for (int i=0; i< UIHelp::NUM_COMMANDS; i++){
		LogicUpdater::EVENT_STRING temp;
		temp = convertToEventString(HELP_GUIDE_COMMANDS[i]);
		vectOfComds.push_back(temp);
	}

	assert(vectOfComds.size() == UIHelp::NUM_COMMANDS);

	return vectOfComds;
}
std::vector<LogicUpdater::EVENT_STRING> UIHelp::getHelpShortcuts(){
	std::vector<LogicUpdater::EVENT_STRING> vectOfComds;

	for (int i=0; i< UIHelp::NUM_SHORTCUTS; i++){
		LogicUpdater::EVENT_STRING temp;
		temp = convertToEventString(HELP_GUIDE_SHORTCUTS[i]);
		vectOfComds.push_back(temp);
	}

	assert(vectOfComds.size() == NUM_SHORTCUTS);

	return vectOfComds;
}
