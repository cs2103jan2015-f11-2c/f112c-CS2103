//@author A0111379H

#include "InputStringSplit.h"

const std::string InputStringSplit::EXTRACT_FIRST_WORD = "extractFirstWord";
const std::string InputStringSplit::EXTRACT_DETAILS = "extractDetails";
const std::string InputStringSplit::EXTRACT_DEL_DONE_EVENT_NAME = "extractDelDoneEventName";
const std::string InputStringSplit::EXTRACT_EDIT_EVENT_NAME = "extractEditEventName";
const std::string InputStringSplit::REMOVE_EDIT_EVENT_NAME = "removeEditEventName";
const std::string InputStringSplit::FRAGMENT_STRING = "fragmentString";
const std::string InputStringSplit::FRAGMENT_SHOW_STRING = "fragmentShowString";

const std::string InputStringSplit::CONVERT_NORMAL_TO_FLOAT = "to>>>float";

InputStringSplit::InputStringSplit(){
}

//Finds the first word and extracts it out. Throws exception if no input is found. Returns the extracted string.
std::string InputStringSplit::extractFirstWord(std::string input){
	logger.logParserEnterFunc(EXTRACT_FIRST_WORD);

	bool missingInput = true;
	for (unsigned int i = 0; i < input.size() && missingInput; i++){
		if(isalnum(input[i])){
			missingInput = false;
		}
	}
	if(missingInput){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	
	std::string::size_type strCutIndex;
	std::string tempStr;
	
	strCutIndex = input.find_first_not_of(" ");
	if(strCutIndex == std::string::npos){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	tempStr = input.substr(strCutIndex);
	strCutIndex = tempStr.find_first_of(" ");
	tempStr = tempStr.substr(0,strCutIndex);
	for(unsigned int i = 0; i < tempStr.size(); i++){
		tempStr[i] = std::tolower(tempStr[i]);
	}
	
	if(tempStr.empty()){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	return tempStr;
}

//Remove the first word and extract out what comes AFTER the first word.
//Throws exception if no input is found after the spacing. Returns the extracted string.
std::string InputStringSplit::extractDetails(std::string input){
	logger.logParserEnterFunc(EXTRACT_DETAILS);
	assert(!input.empty());

	bool missingInput = true;
	for (unsigned int i = 0; i < input.size() && missingInput; i++){
		if(isalnum(input[i])){
			missingInput = false;
		}
	}
	if(missingInput){
		logger.logParserError(ParserExceptions::ERROR_INSUFFICIENT_INFO);
		throw ParserExceptions(ParserExceptions::ERROR_INSUFFICIENT_INFO);
	}

	std::string::size_type strCutIndex;
	strCutIndex = input.find_first_not_of(" ");
	if(strCutIndex == std::string::npos){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	std::string tempStr = input.substr(strCutIndex);
	strCutIndex = tempStr.find_first_of(" ");
	if(strCutIndex == std::string::npos){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	tempStr = tempStr.substr(strCutIndex);

	strCutIndex = tempStr.find_first_not_of(" ");
	if(strCutIndex == std::string::npos){
		logger.logParserError(ParserExceptions::ERROR_INSUFFICIENT_INFO);
		throw ParserExceptions(ParserExceptions::ERROR_INSUFFICIENT_INFO);
	}

	tempStr = tempStr.substr(strCutIndex);
	if(tempStr.empty()){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	return tempStr;
}

//Finds the event name and index by searching for ';', and extracts this info.
//Throws exception if no event name/ event index is found. Returns the extracted event name/index in string format.
std::string InputStringSplit::extractEditEventName(std::string input){
	logger.logParserEnterFunc(EXTRACT_EDIT_EVENT_NAME);
	assert(!input.empty());

	if(input.empty()){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	std::string::size_type strCutIndex;
	std::string tempStr;
	
	strCutIndex = input.find_last_of(";");
	if(strCutIndex == std::string::npos){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INDEX);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INDEX);
	}
	tempStr = input.substr(0,strCutIndex);
	strCutIndex = tempStr.find_last_not_of(" ");
	if (strCutIndex == std::string::npos){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INDEX);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INDEX);
	} else {
		tempStr = tempStr.substr(0,strCutIndex+1);
	}

	if(tempStr.empty()){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	return tempStr;
}

//Removes the event name/index from the input string.
//Returns the remaining string after removing the event name/event index.
std::string InputStringSplit::removeEditEventName(std::string input, std::string eventName){
	logger.logParserEnterFunc(REMOVE_EDIT_EVENT_NAME);
	assert(!input.empty());

	if(input.empty()){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	std::string::size_type strCutIndex;
	strCutIndex = input.find(eventName);
	strCutIndex = input.find_first_not_of(" ;",strCutIndex+eventName.size());
	std::string tempStr;
	if(strCutIndex != std::string::npos){
		tempStr = input.substr(strCutIndex);
	} else {
		tempStr = CONVERT_NORMAL_TO_FLOAT;
	}

	if(tempStr.empty()){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	return tempStr;
}

//Splits the input string into a vector of strings for add events, by finding spaces, dots and numbers and splits the string accordingly. 
//Replaces '-' with the word "to". Throws exception if there is no input. Returns a vector of strings.
std::vector<std::string> InputStringSplit::fragmentString(std::string input){
	logger.logParserEnterFunc(FRAGMENT_STRING);
	assert(!input.empty());

	if(input.empty()){
		logger.logParserError(ParserExceptions::ERROR_INSUFFICIENT_INFO);
		throw ParserExceptions(ParserExceptions::ERROR_INSUFFICIENT_INFO);
	}
	std::string::size_type strCutIndex;
	std::vector<std::string> fragmentedWords;
	std::string tempString;
	bool endOfString = false;
	bool dotFound = false;
	int dotCounter = 0;

	while(!endOfString){
		strCutIndex = input.find_first_of("- 0123456789");
		if(strCutIndex == std::string::npos){
			fragmentedWords.push_back(input.substr(0,strCutIndex));
			endOfString = true;
		} else {
			if(input.at(strCutIndex) == '-'){
				if(strCutIndex != 0){
					fragmentedWords.push_back(input.substr(0,strCutIndex));
				}
				fragmentedWords.push_back("to");
				strCutIndex = input.find_first_not_of(" -.",strCutIndex);
			} else if(input.at(strCutIndex) == ' '){
				if(strCutIndex != 0){
					fragmentedWords.push_back(input.substr(0,strCutIndex+1));
				}
				strCutIndex = input.find_first_not_of(" ",strCutIndex);
			} else {
				if(strCutIndex != 0){
					fragmentedWords.push_back(input.substr(0,strCutIndex));
					input = input.substr(strCutIndex);
					strCutIndex = 0;
				}
				strCutIndex = input.find_first_not_of("0123456789.",strCutIndex);
				if(strCutIndex != std::string::npos){
					if(input[strCutIndex] == ' '){
						fragmentedWords.push_back(input.substr(0,strCutIndex+1));
					} else {
						fragmentedWords.push_back(input.substr(0,strCutIndex));
					}
				} else {
					fragmentedWords.push_back(input.substr(0,strCutIndex));
				}
			}
			if(dotFound){
				dotCounter++;
			}
			if(dotCounter == SECOND_INSTANCE && fragmentedWords.size() >= SECOND_INSTANCE){
				fragmentedWords[fragmentedWords.size()-SECOND_INSTANCE] = 
					fragmentedWords[fragmentedWords.size()-SECOND_INSTANCE] + fragmentedWords[fragmentedWords.size()-1];
				fragmentedWords.pop_back();
				dotFound = false;
				dotCounter = 0;
			}
			if(strCutIndex == std::string::npos){
				endOfString = true;
			} else {
				input = input.substr(strCutIndex);
			}
		}
	}
	return fragmentedWords;
}