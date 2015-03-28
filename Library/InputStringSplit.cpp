#include "InputStringSplit.h"

const std::string InputStringSplit::EXTRACT_FIRST_WORD = "extractFirstWord";
const std::string InputStringSplit::EXTRACT_DETAILS = "extractDetails";
const std::string InputStringSplit::EXTRACT_DEL_EVENT_NAME = "extractDelEventName";
const std::string InputStringSplit::EXTRACT_EDIT_EVENT_NAME = "extractEditEventName";
const std::string InputStringSplit::REMOVE_EDIT_EVENT_NAME = "removeEditEventName";
const std::string InputStringSplit::FRAGMENT_ADD_STRING = "fragmentAddString";
const std::string InputStringSplit::FRAGMENT_EDIT_STRING = "fragmentEditString";
const std::string InputStringSplit::FRAGMENT_SHOW_STRING = "fragmentShowString";

InputStringSplit::InputStringSplit(){
}

//Finds the first instance of a spacing and extract out what comes BEFORE the spacing.
//Throws exception if no input is found. Returns the extracted string.
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
	strCutIndex = input.find_first_of(" ");
	std::string tempStr = input.substr(0,strCutIndex);
	//assert string not empty
	return tempStr;
}

//Finds the first instance of a spacing and extract out what comes AFTER the spacing.
//Throws exception if no input is found after the spacing. Returns the extracted string.
std::string InputStringSplit::extractDetails(std::string input){
	logger.logParserEnterFunc(EXTRACT_DETAILS);

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
	strCutIndex = input.find_first_of(" ");
	if(strCutIndex == std::string::npos){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	strCutIndex = input.find_first_not_of(" ;",strCutIndex);
	if(strCutIndex == std::string::npos){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}

	std::string tempStr = input.substr(strCutIndex);
	//assert string not empty
	return tempStr;
}

//Finds the event name by searching for ';', or the event index if event name is not found, and extracts this info.
//Throws exception if no event name/ event index is found or if too many information is provided. Returns the extracted event name/index in string format.
std::string InputStringSplit::extractDelEventName(std::string input){
	logger.logParserEnterFunc(EXTRACT_DEL_EVENT_NAME);

	if(input.empty()){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	std::string::size_type strCutIndex;
	std::string tempStr;
	strCutIndex = input.find_last_of(";");
	if(strCutIndex == std::string::npos){
		strCutIndex = input.find_first_of(" ");
		if(strCutIndex != std::string::npos){
			logger.logParserError(ParserExceptions::ERROR_TOO_MANY_DEL);
			throw ParserExceptions(ParserExceptions::ERROR_TOO_MANY_DEL);
		}
		try	{
			auto tempStoi = std::stoi(input.substr(0,strCutIndex));
		} catch (std::invalid_argument& e){
			logger.logParserError(ParserExceptions::ERROR_MISSING_INDEX);
			throw ParserExceptions(ParserExceptions::ERROR_MISSING_INDEX);
		}
	}
	tempStr = input.substr(0,strCutIndex);
	//assert string not empty
	return tempStr;
}

//Finds the event name by searching for ';', or the event index if event name is not found, and extracts this info.
//Throws exception if no event name/ event index is found. Returns the extracted event name/index in string format.
std::string InputStringSplit::extractEditEventName(std::string input){
	logger.logParserEnterFunc(EXTRACT_EDIT_EVENT_NAME);

	if(input.empty()){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	std::string::size_type strCutIndex;
	strCutIndex = input.find_first_of(" ");
	std::string tempString = input.substr(0,strCutIndex);
	
	try {
		int index = std::stoi(tempString);
	} catch (std::invalid_argument& e){
		strCutIndex = input.find_first_of(";");
		if(strCutIndex == std::string::npos){
			logger.logParserError(ParserExceptions::ERROR_MISSING_INDEX);
			throw ParserExceptions(ParserExceptions::ERROR_MISSING_INDEX);
		}
		tempString = input.substr(0,strCutIndex);
	}
	//assert not empty string
	return tempString;
}

//Removes the event name/index from the input string. Throws exception if input is empty, or if there is no additional information after the event name/index
//Returns the remaining string after removing the event name/event index.
std::string InputStringSplit::removeEditEventName(std::string input, std::string eventName){
	logger.logParserEnterFunc(REMOVE_EDIT_EVENT_NAME);

	if(input.empty()){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	std::string::size_type strCutIndex;
	strCutIndex = input.find(eventName);
	if(strCutIndex == std::string::npos){
		logger.logParserError(ParserExceptions::ERROR_INSUFFICIENT_INFO);
		throw ParserExceptions(ParserExceptions::ERROR_INSUFFICIENT_INFO);
	}
	strCutIndex = input.find_first_not_of(" ;",strCutIndex+eventName.size());
	if(strCutIndex == std::string::npos){
		logger.logParserError(ParserExceptions::ERROR_INSUFFICIENT_INFO);
		throw ParserExceptions(ParserExceptions::ERROR_INSUFFICIENT_INFO);
	}
	std::string tempStr = input.substr(strCutIndex);
	//assert not empty string
	return tempStr;
}

//Splits the input string into a vector of strings for add events, first by taking out the event name, and then separating the remaining string by finding delimiters 
//( .-) and removing them. Replaces '-' with the word "to". Throws exception if there is no input, or no event name. Returns a vector of strings.
std::vector<std::string> InputStringSplit::fragmentAddString(std::string input){
	logger.logParserEnterFunc(FRAGMENT_ADD_STRING);

	if(input.empty()){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	std::string::size_type strCutIndex;
	std::vector<std::string> fragmentedWords;
	std::string tempString;
	bool endOfString = false;

	strCutIndex = input.find_last_of(";");		// ; indicates end of event name
	if(strCutIndex == std::string::npos){
		logger.logParserError(ParserExceptions::ERROR_NO_NAME);
		throw ParserExceptions(ParserExceptions::ERROR_NO_NAME);
	}
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
		if(strCutIndex != std::string::npos){
			if(input.at(strCutIndex) == '-'){
				fragmentedWords.push_back("to");
			}
		}
		strCutIndex = input.find_first_not_of(" -.",strCutIndex);
		if(strCutIndex == std::string::npos){
			endOfString = true;
		}
	}
	//assert vector not empty
	return fragmentedWords;
}

//Splits the input string into a vector of strings for edit events, first by checking if there is an event name, and then separating the remaining string by 
//finding delimiters ( .-) and removing them. Replaces '-' with the word "to". Throws exception if there is no input, or insufficient info. Returns a vector of strings.
std::vector<std::string> InputStringSplit::fragmentEditString(std::string input){
	logger.logParserEnterFunc(FRAGMENT_EDIT_STRING);

	if(input.empty()){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	std::string::size_type strCutIndex;
	std::vector<std::string> fragmentedWords;
	std::string tempString;
	bool endOfString = false;
	
	if(input.find_first_not_of(" -.") == std::string::npos){
		logger.logParserError(ParserExceptions::ERROR_INSUFFICIENT_INFO);
		throw ParserExceptions(ParserExceptions::ERROR_INSUFFICIENT_INFO);
	}

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
		if(strCutIndex != std::string::npos){
			if(input.at(strCutIndex) == '-'){
				fragmentedWords.push_back("to");
			}
		}
		strCutIndex = input.find_first_not_of(" -.",strCutIndex);
		if(strCutIndex == std::string::npos){
			endOfString = true;
		} else {
			input = input.substr(strCutIndex);
		}
	}
	//assert vector not empty
	return fragmentedWords;
}	

//Splits the input string into a vector of strings for show events, first by checking if there is an event name, and then separating the remaining string by 
//finding delimiters ( .-) and removing them. Replaces '-' with the word "to". Throws exception if there is no input, or insufficient info. Returns a vector of strings.
std::vector<std::string> InputStringSplit::fragmentShowString(std::string input){
	logger.logParserEnterFunc(FRAGMENT_SHOW_STRING);

	if(input.empty()){
		logger.logParserError(ParserExceptions::ERROR_MISSING_INPUT);
		throw ParserExceptions(ParserExceptions::ERROR_MISSING_INPUT);
	}
	std::string::size_type strCutIndex;
	std::vector<std::string> fragmentedWords;
	bool endOfString = false;

	if(input.find_first_not_of(" -.") == std::string::npos){
		logger.logParserError(ParserExceptions::ERROR_INSUFFICIENT_INFO);
		throw ParserExceptions(ParserExceptions::ERROR_INSUFFICIENT_INFO);
	}

	while(!endOfString){
		strCutIndex = input.find_first_of(" -.");
		fragmentedWords.push_back(input.substr(0,strCutIndex));
		if(strCutIndex != std::string::npos){
			if(input.at(strCutIndex) == '-'){
				fragmentedWords.push_back("to");
			}
		}
		strCutIndex = input.find_first_not_of(" -.",strCutIndex);
		if(strCutIndex == std::string::npos){
			endOfString = true;
		} else {
			input = input.substr(strCutIndex);
		}
	}
	//assert vector not empty
	return fragmentedWords;
}