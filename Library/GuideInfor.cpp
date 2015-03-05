#include <cctype>


#include "GuideInfor.h"


GuideInfor::GuideInfor(void)
{
}


GuideInfor::~GuideInfor(void)
{
}

// static strings that cannot initialise in "InforProcess.h"
const std::string GuideInfor::COMMAND_ADD = "add";
const std::string GuideInfor::COMMAND_DELETE = "delete";
const std::string GuideInfor::COMMAND_EDIT = "edit";
const std::string GuideInfor::COMMAND_SEARCH = "search";
const std::string GuideInfor::COMMAND_SHOW = "show";
const std::string GuideInfor::COMMAND_UNDO = "undo";
const std::string GuideInfor::COMMAND_REDO = "redo";
const std::string GuideInfor::COMMAND_EXIT = "exit";
const std::string GuideInfor::COMMAND_HELP = "help";

const std::string GuideInfor::HELP_GUIDE_INTRO = "Welcome to MapleSyrup. Following are the commands: \n";

const std::string GuideInfor::HELP_GUIDE_ADD[GuideInfor::NUM_ADD] = { "There are a total of 9 ways to add an event:\n",
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

const std::string GuideInfor::HELP_GUIDE_DELETE[GuideInfor::NUM_DELETE] = { "Through index: Use either the 'show' or 'search' command to display the event you would like to delete.\n",
																 "Delete by entering the number beside it.\n",
																 "e.g. 'delete 2'  to delete 2.CS2103 \n",
																 "Through event name: \n",
																 "e.g. 'delete 2'  to delete 2.CS2103 \n",
																 "TBC \n"
															   };
																 
const std::string GuideInfor::HELP_GUIDE_EDIT[GuideInfor::NUM_EDIT] = {"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n"
																	};

const std::string GuideInfor::HELP_GUIDE_SEARCH[GuideInfor::NUM_SEARCH]= {"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n"
																	};

const std::string GuideInfor::HELP_GUIDE_SHOW[GuideInfor::NUM_SHOW] = {"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n",
																		"TBC \n"
																	};
const std::string GuideInfor::HELP_GUIDE_UNDO = "TBC \n";
const std::string GuideInfor::HELP_GUIDE_REDO = "TBC \n";
const std::string GuideInfor::HELP_GUIDE_EXIT = "TBC \n";
const std::string GuideInfor::HELP_GUIDE_HELP = "TBC \n";




const std::string GuideInfor::SUGGESTION_ADD[GuideInfor::NUM_SUGGESTION_ADD] = {" add lunch" ,
																	  " add CS2103 exam @10feb 11am-2pm", 
																	  " add Holidays @15june-30june 9am-9am"
																	};

const std::string GuideInfor::SUGGESTION_DELETE[GuideInfor::NUM_SUGGESTION_DELETE] = {" delete 2" ,
																	  " delete CS2103 exam" 
																	};

const std::string GuideInfor::SUGGESTION_EDIT[GuideInfor::NUM_SUGGESTION_EDIT]= {" edit 4 time 4pm-6pm" ,
																	  " delete CS2103 exam" 
																	};

const std::string GuideInfor::SUGGESTION_SEARCH[GuideInfor::NUM_SUGGESTION_SEARCH] = {" search CS2103 exam" ,
																	  " search 10feb" 
																	};

const std::string GuideInfor::SUGGESTION_SHOW[GuideInfor::NUM_SUGGESTION_SHOW]= {" show 10feb" ,
																	  " show week 10feb(date where the week is in)", 
																	  " show month 3 (which month)"
																	};


//Getters

std::string GuideInfor::getCommandAdd(){
	return COMMAND_ADD;
}

std::string GuideInfor::getCommandDelete(){
	return COMMAND_DELETE;
}

std::string GuideInfor::getCommandEdit(){
	return COMMAND_EDIT;
}

std::string GuideInfor::getCommandSearch(){
	return COMMAND_SEARCH;
}

std::string GuideInfor::getCommandShow(){
	return COMMAND_SHOW;
}

std::string GuideInfor::getCommandUndo(){
	return COMMAND_UNDO;
}

std::string GuideInfor::getCommandRedo(){
	return COMMAND_REDO;
}

std::string GuideInfor::getCommandExit(){
	return COMMAND_EXIT;
}

std::string GuideInfor::getCommandHelp(){
	return COMMAND_HELP;
}



std::string GuideInfor::getHelpIntro(){
	return HELP_GUIDE_INTRO;
}

std::string GuideInfor::getHelpAdd(){
	std::string out = "";

	for (int i=0; i<NUM_ADD;i++){
		out += HELP_GUIDE_ADD[i];
	}

	return out;
}

std::string GuideInfor::getHelpDelete(){
	std::string out = "";

	for (int i=0; i<NUM_DELETE;i++){
		out += HELP_GUIDE_DELETE[i];
	}

	return out;
}

std::string GuideInfor::getHelpEdit(){
	std::string out = "";

	for (int i=0; i<NUM_EDIT;i++){
		out += HELP_GUIDE_EDIT[i];
	}

	return out;
}
std::string GuideInfor::getHelpSearch(){
	std::string out = "";

	for (int i=0; i<NUM_SEARCH;i++){
		out += HELP_GUIDE_SEARCH[i];
	}

	return out;
}

std::string GuideInfor::getHelpShow(){
	std::string out = "";

	for (int i=0; i<NUM_SHOW;i++){
		out += HELP_GUIDE_SHOW[i];
	}

	return out;
}
	
std::string GuideInfor::getHelpUndo(){
	return HELP_GUIDE_UNDO;
}
	
std::string GuideInfor::getHelpRedo(){
	return HELP_GUIDE_REDO ;
}
	
std::string GuideInfor::getHelpExit(){
	return HELP_GUIDE_EXIT;
}

std::string GuideInfor::getHelpHelp(){
	return HELP_GUIDE_HELP;
}

std::string GuideInfor::getSuggestionAdd(int index){
	return SUGGESTION_ADD[index];
}

std::string GuideInfor::getSuggestionDelete(int index){
	return SUGGESTION_DELETE[index];

}

std::string GuideInfor::getSuggestionEdit(int index){
	return SUGGESTION_EDIT[index];
	
}

std::string GuideInfor::getSuggestionSearch(int index){
	return SUGGESTION_SEARCH[index];

}

std::string GuideInfor::getSuggestionShow(int index){
	return SUGGESTION_SHOW[index];

}



const int GuideInfor::getSuggestionAddArrarySize(){
	return NUM_SUGGESTION_ADD;
}

const int GuideInfor::getSuggestionDeleteArrarySize(){
	return NUM_SUGGESTION_DELETE;
}

const int GuideInfor::getSuggestionEditArrarySize(){
	return NUM_SUGGESTION_EDIT;
}

const int GuideInfor::getSuggestionSearchArrarySize(){
	return NUM_SUGGESTION_SEARCH;
}

const int GuideInfor::getSuggestionShowArrarySize(){
	return NUM_SUGGESTION_SHOW;
}


 //functions


std::string GuideInfor::lowerCase(std::string word){
	for (int i=0;i<word.size();i++){
		 word[i] = tolower(word[i]);
	 }
	return word;
 }



