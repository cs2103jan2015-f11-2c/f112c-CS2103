//@author A0111230J

#include "UIHelp.h"


UIHelp::UIHelp(void)
{
}


UIHelp::~UIHelp(void)
{
}


// static variables that cannot initialise in "UIHelp.h"
const std::string UIHelp::HELP_GUIDE_WELCOME_MESSAGE = "Welcome to MapleSyrup! This introductory guide will provide you \nwith examples to Add, Delete, Edit & Show !\n";

const std::string UIHelp::HELP_GUIDE_ADD[UIHelp::NUM_ADD] = {"ADD : ", 
																"1.add drink maplesyrup (Ongoing Event)",															 
															    "2.add drink maplesyrup 1 jan 3pm - 4pm (Single Day Event)",															  
																"3.add drink maplesyrup 1 jan 1am - 31 dec 11pm (Multiple Day Event)",																		
																"4.add drink maplesyrup by 31 dec 11pm (Deadline Events)\n",																	
															};

const std::string UIHelp::HELP_GUIDE_DELETE[UIHelp::NUM_DELETE] = { "DELETE : ", 
																 "1.del drink maplesyrup (by name)",
																 "2.del 1 (by index)\n",
															   };
																 
const std::string UIHelp::HELP_GUIDE_EDIT[UIHelp::NUM_EDIT] = {"EDIT : ",
																		"1.edit drink maplesyrup; buy maplesyrup (Normal)",
																		"2.edit drink maplesyrup; (Normal to Ongoing Event)",
																		"3.edit drink maplesyrup; 5may 7-8pm (Ongoing to Normal Event)\n",
																	};

const std::string UIHelp::HELP_GUIDE_END = "For more details, please refer to the MapleSyrup guide provided!\nHappy Mapling!";

const std::string UIHelp::HELP_GUIDE_SHOW[UIHelp::NUM_SHOW] = {"SHOW : ",
																		"1.show 24apr (Single Day)",
																		"2.show 22-23apr (Multiple Days)",
																		"3.show apr-may (Month)",
																		"4.show all (All)\n",
																	};

const std::string UIHelp::HELP_GUIDE_COMMANDS[UIHelp::NUM_COMMANDS] = {"1.\tadd",
																		"2.\tdelete/del",
																		"3.\tedit",
																		"4.\tdone/completed",
																		"5.\tundone/uncompleted",
																		"6.\tsearch",
																		"7.\tshow",
																		"8.\tundo",
																		"9.\tredo",
																		"10.\texit",
																		"11.\thelp",
																		"12.\tcommands",
																		"13.\tshortcuts",
																		"14.\tcalendar",
																		"15.\tback",
																		"16.\tnext",
																	};

const std::string UIHelp::HELP_GUIDE_SHORTCUTS [UIHelp::NUM_SHORTCUTS] = {"1.\tCtrl + D ------ display calendar",
																		  "2.\tCtrl + F ------ search mode/bar",
																		  "3.\tCtrl + Z ------ undo",
																	      "4.\tCtrl + X ------ redo",
																		  "5.\tCtrl + C ------ copy",
																		  "6.\tCtrl + V ------ paste",
																		  "7.\tEscape Key ---- zoom to main/on-going events displays",
																		  "8.\tLeft arrow ---- display back",
																		  "9.\tRight arrow ----- display next",
																		  "10.\tCtrl + Shift ----- focus to command Box",
																	};

//Functions	

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
	helpString = convertToEventString(HELP_GUIDE_WELCOME_MESSAGE);
	vectOfHelp.push_back(helpString);

	//Add
	for (int i=0; i<UIHelp::NUM_ADD; i++){
		tempHelpString = HELP_GUIDE_ADD[i];
		helpString = convertToEventString(tempHelpString);
		if(i!=0){
			helpString.isMarker = true;
		}
		vectOfHelp.push_back(helpString);
	}

	//Delete
	for (int i=0; i<UIHelp::NUM_DELETE; i++){
		tempHelpString = HELP_GUIDE_DELETE[i];
		helpString = convertToEventString(tempHelpString);
		if(i!=0){
			helpString.isMarker = true;
		}
		vectOfHelp.push_back(helpString);
	}

	//Edit
	for (int i=0; i<UIHelp::NUM_EDIT; i++){
		tempHelpString = HELP_GUIDE_EDIT[i];
		helpString = convertToEventString(tempHelpString);
		if(i!=0){
			helpString.isMarker = true;
		}
		vectOfHelp.push_back(helpString);
	}

	//Show
	for (int i=0; i<UIHelp::NUM_SHOW; i++){
		tempHelpString = HELP_GUIDE_SHOW[i];
		helpString = convertToEventString(tempHelpString);
		if(i!=0){
			helpString.isMarker = true;
		}
		vectOfHelp.push_back(helpString);
	}

	//End Message
	helpString = convertToEventString(HELP_GUIDE_END);
	vectOfHelp.push_back(helpString);

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
