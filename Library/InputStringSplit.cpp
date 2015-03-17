#include "InputStringSplit.h"

InputStringSplit::InputStringSplit(){
}

std::string InputStringSplit::extractFirstWord(std::string input){
	std::string::size_type strCutIndex;
	strCutIndex = input.find_first_of(" ");
	return input.substr(0,strCutIndex);
}

std::string InputStringSplit::extractDetails(std::string input){
	std::string::size_type strCutIndex;
	strCutIndex = input.find_first_of(" ");
	return input.substr(input.find_first_not_of(" ;",strCutIndex));
}

std::string InputStringSplit::extractEventName(std::string input){
	std::string::size_type strCutIndex;
	strCutIndex = input.find_first_of(";");
	return input.substr(0,strCutIndex);
}

std::string InputStringSplit::removeEditEventName(std::string input, std::string eventName){
	std::string::size_type strCutIndex;
	strCutIndex = input.find(eventName);
	return input.substr(input.find_first_not_of(" ;",strCutIndex+eventName.size()));
}

std::string InputStringSplit::extractEditEventName(std::string input){
	std::string::size_type strCutIndex;
	strCutIndex = input.find_first_of(" ");
	std::string tempString = input.substr(0,strCutIndex);
	
	try {
		int index = std::stoi(tempString);
	} catch (std::invalid_argument& e){
		strCutIndex = input.find_first_of(";");
		tempString = input.substr(0,strCutIndex);
	}
	return tempString;
}

std::vector<std::string> InputStringSplit::fragmentAddString(std::string input){
	std::string::size_type strCutIndex;
	std::vector<std::string> fragmentedWords;
	std::string tempString;
	bool endOfString = false;

	strCutIndex = input.find_first_of(";");		// ; indicates end of event name
	tempString = input.substr(0,strCutIndex);
	fragmentedWords.push_back(tempString + ";");	// remove any unwanted spaces at the back of event name
	strCutIndex = input.find_first_not_of(" -.;",strCutIndex); // remove unwanted spaces after ;
	if(strCutIndex == std::string::npos){
		endOfString = true;
	}
	
	while(!endOfString){
		input = input.substr(strCutIndex);
		strCutIndex = input.find_first_of(" -.");
		fragmentedWords.push_back(input.substr(0,strCutIndex));
		strCutIndex = input.find_first_not_of(" -.",strCutIndex);
		if(strCutIndex == std::string::npos){
			endOfString = true;
		}
	}

	return fragmentedWords;
}

std::vector<std::string> InputStringSplit::fragmentEditString(std::string input){
	std::string::size_type strCutIndex;
	std::vector<std::string> fragmentedWords;
	std::string tempString;
	bool endOfString = false;
	
	strCutIndex = input.find_first_of(";");
	if(strCutIndex != std::string::npos){
		fragmentedWords.push_back(input.substr(0,strCutIndex)+";");
		strCutIndex = input.find_first_not_of(" -.;",strCutIndex);
		if(strCutIndex == std::string::npos){
			endOfString = true;
		} else {
			input = input.substr(strCutIndex);
		}
	}

	if(input.find_first_not_of(" -.") == std::string::npos){
		endOfString = true;
	}

	while(!endOfString){
		strCutIndex = input.find_first_of(" -.");
		fragmentedWords.push_back(input.substr(0,strCutIndex));
		strCutIndex = input.find_first_not_of(" -.",strCutIndex);
		if(strCutIndex == std::string::npos){
			endOfString = true;
		} else {
			input = input.substr(strCutIndex);
		}
	}
	return fragmentedWords;
}	

std::vector<std::string> InputStringSplit::fragmentShowString(std::string input){
	std::string::size_type strCutIndex;
	std::vector<std::string> fragmentedWords;
	bool endOfString = false;
	
	while(!endOfString){
		strCutIndex = input.find_first_of(" -.");
		fragmentedWords.push_back(input.substr(0,strCutIndex));
		strCutIndex = input.find_first_not_of(" -.",strCutIndex);
		if(strCutIndex == std::string::npos){
			endOfString = true;
		} else {
			input = input.substr(strCutIndex);
		}
	}

	return fragmentedWords;
}