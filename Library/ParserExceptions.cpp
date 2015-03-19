#include "ParserExceptions.h"

const std::string ParserExceptions::ERROR_MISSING_INPUT = "PS000";
const std::string ParserExceptions::ERROR_NO_NAME = "PS001";
const std::string ParserExceptions::ERROR_TOO_MANY_DATES = "PS002";
const std::string ParserExceptions::ERROR_TOO_MANY_TIMES = "PS003";
const std::string ParserExceptions::ERROR_MISSING_DAY = "PS004";
const std::string ParserExceptions::ERROR_UNUSED_INTEGERS = "PS005";
const std::string ParserExceptions::ERROR_MISSING_HOUR_MIN = "PS006";
const std::string ParserExceptions::ERROR_TOO_MANY_DEL = "PS007";
const std::string ParserExceptions::ERROR_MISSING_INDEX = "PS008";
const std::string ParserExceptions::ERROR_INSUFFICIENT_INFO = "PS009";

ParserExceptions::ParserExceptions(std::string errorCode){
	if(errorCode == ERROR_MISSING_INPUT){
		feedback = "Error: Missing input.";
	}
	if(errorCode == ERROR_NO_NAME){
		feedback = "Error: No event name has been input for Add event, please type ';' after an event name.";
	}
	if(errorCode == ERROR_TOO_MANY_DATES){
		feedback = "Error: Detected more than two date inputs. Maximum of 2 date inputs, start date to end date.";
	}
	if(errorCode == ERROR_TOO_MANY_TIMES){
		feedback = "Error: Detected more than two time inputs. Maximum of 2 time inputs, start time to end time.";
	}
	if(errorCode == ERROR_MISSING_DAY){
		feedback = "Error: No day input found before month, please input day followed by month.";
	}
	if(errorCode == ERROR_UNUSED_INTEGERS){
		feedback = "Error: Wrong formatting/Too many information, not all information has been successfully recorded.";
	}
	if(errorCode == ERROR_MISSING_HOUR_MIN){
		feedback = "Error: No hour/minute input before am/pm, please input hour/minute followed by am/pm.";
	}
	if(errorCode == ERROR_TOO_MANY_DEL){
		feedback = "Error: Too many input detected. Please key in index only, or event name only ending with ';'.";
	}
	if(errorCode == ERROR_MISSING_INDEX){
		feedback = "Error: No event index or event name has been found. Please type ';' after the event name.";
	}
	if(errorCode == ERROR_INSUFFICIENT_INFO){
		feedback = "Error: Not enough information has been input for command to be executed successfully.";
	}
}

std::string ParserExceptions::getfeedback(){
	return feedback;
}


