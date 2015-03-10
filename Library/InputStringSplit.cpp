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
	return input.substr(strCutIndex+1);
}

std::string InputStringSplit::extractEventName(std::string input){
	std::string::size_type strCutIndex;
	strCutIndex = input.find_first_of(";");
	return input.substr(0,strCutIndex+1);
}

std::vector<std::string> InputStringSplit::fragmentAddString(std::string input){
	std::string::size_type strCutIndex;
	std::vector<std::string> fragmentedWords;
	std::string tempString;
	bool endOfString = false;

	strCutIndex = input.find_first_of(";");		// ; indicates end of event name
	tempString = input.substr(0,strCutIndex);
	tempString = tempString + ";";
	fragmentedWords.push_back(tempString);	// remove any unwanted spaces at the back of event name
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

/* NOT NEEDED
std::vector<std::string> InputStringSplit::fragmentDeleteString(std::string input){
	std::string::size_type strCutIndex;
	std::vector<std::string> fragmentedWords;
	bool endOfString = false;

	while(!endOfString){
		strCutIndex = input.find_first_of(" -.");
		fragmentedWords.push_back(input.substr(0,strCutIndex));
		strCutIndex = input.find_first_not_of(" -.",strCutIndex);
		if(strCutIndex == std::string::npos){
			endOfString = true;
		}
		else {
			input = input.substr(strCutIndex);
		}
	}

	return fragmentedWords;
}
*/
std::vector<std::string> InputStringSplit::fragmentEditString(std::string input){
	std::string::size_type strCutIndex;
	std::vector<std::string> fragmentedWords;
	std::string tempString;
	bool endOfString = false;
	
	strCutIndex = input.find_first_of(";");
	while(strCutIndex != std::string::npos){
		tempString = input.substr(0,strCutIndex);
		strCutIndex = tempString.find_last_not_of(" ");
		fragmentedWords.push_back(tempString.substr(0,strCutIndex)+";");
		strCutIndex = input.find_first_not_of(" -.;",strCutIndex);
		input = input.substr(0,strCutIndex);
		strCutIndex = input.find_first_of(";");
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
		}
		else {
			input = input.substr(strCutIndex);
		}
	}
	return fragmentedWords;
}	