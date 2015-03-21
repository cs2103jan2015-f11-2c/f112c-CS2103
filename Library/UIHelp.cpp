#include "UIHelp.h"


UIHelp::UIHelp(void)
{
}


UIHelp::~UIHelp(void)
{
}

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

const std::string UIHelp::HELP_GUIDE_COMMANDS[UIHelp::NUM_COMMANDS] = {"1. Add",
																		"2. Delete",
																		"3. Edit",
																		"4. Done",
																		"5. Search",
																		"6. Show",
																		"7. Undo",
																		"8. Redo",
																		"9. Exit",
																		"10. Help",
																		"11. Commands",
																	};


std::vector<Display::EVENT_STRING> UIHelp::getHelpIntroduction(){
	std::vector<Display::EVENT_STRING> vectOfHelp;

	std::string tempHelpString; 
	Display::EVENT_STRING helpString;

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

std::vector<Display::EVENT_STRING> UIHelp::getHelpCommands(){
	std::vector<Display::EVENT_STRING> vectOfComds;

	for (int i=0; i< UIHelp::NUM_COMMANDS; i++){
		Display::EVENT_STRING temp;
		temp = convertToEventString(HELP_GUIDE_COMMANDS[i]);
		vectOfComds.push_back(temp);
	}

	assert(vectOfComds.size() == 11);

	return vectOfComds;
}

Display::EVENT_STRING UIHelp::convertToEventString(std::string stdString){
	Display::EVENT_STRING temp;

	temp.eventString = stdString;
	temp.isClash = false;
	temp.isNew = false;

	return temp;
}


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

	
