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
const std::string ParserExceptions::ERROR_UNKNOWN_COMMAND = "PS010";
const std::string ParserExceptions::ERROR_UNKNOWN_DATE = "PS011";
const std::string ParserExceptions::ERROR_UNKNOWN_HOUR = "PS012";
const std::string ParserExceptions::ERROR_UNKNOWN_MINUTE = "PS013";
const std::string ParserExceptions::ERROR_START_AFTER_END = "PS014";

ParserExceptions::ParserExceptions(std::string errorCode){
	exceptionCode = errorCode;
}

std::string ParserExceptions::getExceptionCode(){
	return exceptionCode;
}


