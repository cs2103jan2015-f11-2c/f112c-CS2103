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

std::vector<std::string> InputStringSplit::fragmentAddString(std::string input){
	std::string::size_type strCutIndex;
	std::vector<std::string> fragmentedWords;
	bool endOfString = false;

	strCutIndex = input.find_first_of("@");
	fragmentedWords.push_back(input.substr(0,strCutIndex));
	strCutIndex = input.find_first_not_of(" -.@",strCutIndex);
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

std::vector<std::string> InputStringSplit::fragmentEditString(std::string input){
	std::string::size_type strCutIndex;
	std::vector<std::string> fragmentedWords;
	bool endOfString = false;
	
	strCutIndex = input.find_first_of(" ");
	fragmentedWords.push_back("USED");
	strCutIndex = input.find_first_not_of(" -.",strCutIndex);
	input = input.substr(strCutIndex); 
	if(strCutIndex == std::string::npos){
		endOfString = true;
	}
	
	strCutIndex = input.find_first_of("@");
	if(strCutIndex != std::string::npos){
		fragmentedWords.push_back(input.substr(0,strCutIndex));
		strCutIndex = input.find_first_not_of(" -.@",strCutIndex);
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